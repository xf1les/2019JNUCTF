
int check(const char* buf, int len)
{
    if(len < 33) return 0;

    char c;

    c = buf[0] ^ 0x7f;
    if(c != '\x19') return 0;

    c = buf[1] ^ 0x1c;
    if(c != '\x70') return 0;

    c = buf[2] ^ 0xe1;
    if(c != '\x80') return 0;

    c = buf[3] ^ 0x24;
    if(c != '\x43') return 0;

    c = buf[4] ^ 0xa;
    if(c != '\x71') return 0;

    c = buf[5] ^ 0x9b;
    if(c != '\xa2') return 0;

    c = buf[6] ^ 0x18;
    if(c != '\x28') return 0;

    c = buf[7] ^ 0x27;
    if(c != '\x12') return 0;

    c = buf[8] ^ 0x6f;
    if(c != '\x30') return 0;

    c = buf[9] ^ 0x7a;
    if(c != '\x10') return 0;

    c = buf[10] ^ 0x6e;
    if(c != '\x3b') return 0;

    c = buf[11] ^ 0x2b;
    if(c != '\x58') return 0;

    c = buf[12] ^ 0x60;
    if(c != '\x14') return 0;

    c = buf[13] ^ 0x32;
    if(c != '\x6d') return 0;

    c = buf[14] ^ 0x6b;
    if(c != '\x2f') return 0;

    c = buf[15] ^ 0x80;
    if(c != '\xb1') return 0;

    c = buf[16] ^ 0x8d;
    if(c != '\xdb') return 0;

    c = buf[17] ^ 0x86;
    if(c != '\xe3') return 0;

    c = buf[18] ^ 0x89;
    if(c != '\xd6') return 0;

    c = buf[19] ^ 0x27;
    if(c != '\x16') return 0;

    c = buf[20] ^ 0x9b;
    if(c != '\xd5') return 0;

    c = buf[21] ^ 0x56;
    if(c != '\x22') return 0;

    c = buf[22] ^ 0x8;
    if(c != '\x38') return 0;

    c = buf[23] ^ 0x45;
    if(c != '\x1a') return 0;

    c = buf[24] ^ 0x88;
    if(c != '\xc5') return 0;

    c = buf[25] ^ 0x39;
    if(c != '\x70') return 0;

    c = buf[26] ^ 0x5;
    if(c != '\x55') return 0;

    c = buf[27] ^ 0xf2;
    if(c != '\xa1') return 0;

    c = buf[28] ^ 0xec;
    if(c != '\xb3') return 0;

    c = buf[29] ^ 0xf7;
    if(c != '\xc1') return 0;

    c = buf[30] ^ 0xc4;
    if(c != '\xf0') return 0;

    c = buf[31] ^ 0xb4;
    if(c != '\x83') return 0;

    c = buf[32] ^ 0xad;
    if(c != '\xd0') return 0;

    return 1;
}
