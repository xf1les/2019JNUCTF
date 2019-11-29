#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

const char* GIFT = "GIMME GIMME SHELL /bin/sh";

struct syscall_param
{
	long sysno;
	long arg0;
	long arg1;
	long arg2;
};

int syscall_safe(long sysno, long arg0, long arg1, long arg2)
{

    __asm__ ("xor %r10d, %r10d;");
    register long max_size __asm__ ("r8") = 0x1000;

    if(sysno < 0 || sysno > 332) {
        sysno = SYS_exit;
    } else if(sysno == 0 || sysno == 1) {

        if(!arg1 || arg2 > max_size / 0x10)
            sysno = SYS_exit;
    }
        
    /*
    switch(sysno) 
    {
        case SYS_open:
        case SYS_execve: {
        case SYS_fork:
        case SYS_vfork:
        case SYS_clone: 
        case SYS_mmap:
        case SYS_mprotect: 
                sysno = SYS_exit;
            }
            break;
        case SYS_read:
        case SYS_write: {
                if(!(arg0 == 0 || arg0 == 1) || !arg1 || !(arg2 && arg2 <= max_size / 0x10))
                    sysno = SYS_exit;
            }
            break;
    }
    */

    int retval;
    __asm__ ("syscall;" :"=a"(retval) : "a"(sysno), "D"(arg0), "S"(arg1), "d"(arg2):);

    return retval;
}

void syscall_wrapper(struct syscall_param* param)
{
    syscall_safe(param->sysno, param->arg0, param->arg1, param->arg2);
}

static __always_inline void m_read(char* buf, size_t count)
{
    syscall_safe(SYS_read, 0, buf, count);
}

static __always_inline void m_print(char* msg)
{
    syscall_safe(SYS_write, 1, msg, strlen(msg));
}

void encrypt()
{

    m_print("WIP\n");
}

void decrypt()
{
    struct __attribute__ ((packed)) {
        char buf[0x100-0x10]; // Stack overflow
        struct syscall_param do_write;
        struct syscall_param do_read;
    } locals;

    memset(locals.buf, 0, 0x100);

    // write(1, buf, len)
    locals.do_write.sysno  = SYS_write; // Stack overflow target
    locals.do_write.arg0   = 1;         // Stack overflow target
    locals.do_write.arg1   = locals.buf;
    // read(0, buf, 0x100)
    locals.do_read.sysno   = SYS_read;
    locals.do_read.arg0    = 0;
    locals.do_read.arg1    = locals.buf;
    locals.do_read.arg2    = 0x100;

    m_print("context:");
    syscall_wrapper(&(locals.do_read));

    int len = strlen(locals.buf);
    if(len > 0x100) 
        len = 0x100;
    for(int i = 0; i < len; ++i)
        locals.buf[i] = ((locals.buf[i] - 0x23) * 0xa7) % 0x100;
    locals.buf[len-1] = '\0';
    locals.do_write.arg2 = strlen(locals.buf);

    syscall_wrapper(&(locals.do_write)); // trigger vulnerability
}

int get_choice()
{
    char buf[0x20];
    memset(buf, 0, 0x20);
    m_read((long)buf, 0x20);

    return atoi(buf);
}

void menu()
{
    m_print("0.encrypt\n");
    m_print("1.decrypt\n");
    m_print("2.exit\n");
    m_print(">\n");
}

int main() 
{

    while(1)
    {
        menu();

        int choice = get_choice();
        switch(choice)
        {
            case 0:
                encrypt();
                break;
            case 1:
                decrypt();
                break;
            case 2:
                syscall_safe(SYS_exit, 0, 0, 0);
        };
    }
}
