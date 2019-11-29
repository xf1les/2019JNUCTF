from Crypto.Util.number import inverse, long_to_bytes

a   = 0xdb626d86f5dc6cf4ec8c4ca4f4b9dab3
b   = 0xb2dab99e8973e463ab58a4403d35675f
n   = 0xd5aef35973977bd35331490990b6b54b80d44bdb621f861848f4377c54cf6649
val = 79170490870873300481412741527444043988034242063298009080761756461786076517810

r = inverse(a, n) # a ^ (-1)

times = 2 ** 30 + 1
while times > 0:
    val = (r * (val - b)) % n
    times -= 1

print long_to_bytes(val)
