import random
import sys

random.seed(905647)

flag = "flag{905_jUst_D1Ve_1Nt0_MIPS_647}"

def make_code():
    t = \
"""
int check(const char* buf, int len)
{
    if(len < %d) return 0;

    char c;
""" %(len(flag))
    
    for i in range(len(flag)):
        r = random.randint(0, 255)
        c = ord(flag[i]) ^ r
        t += \
"""
    c = buf[%d] ^ %s;
    if(c != '%s') return 0;
""" %(i, hex(r), hex(c).replace('0x', '\\x'))

    t += \
"""
    return 1;
}
"""
    return t

code = make_code()
with open(sys.argv[1], "w") as fp:
    fp.write(code)
