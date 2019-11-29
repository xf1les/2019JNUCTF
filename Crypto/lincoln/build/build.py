from Crypto.Util.number import bytes_to_long, inverse

class LCG:
    a = 0xdb626d86f5dc6cf4ec8c4ca4f4b9dab3
    b = 0xb2dab99e8973e463ab58a4403d35675f
    n = 0xd5aef35973977bd35331490990b6b54b80d44bdb621f861848f4377c54cf6649

    def __init__(self, init_seed):
        assert init_seed < self.n
        self.state = init_seed

    def rand(self):
        self.state = (self.a * self.state + self.b) % self.n
        return self.state

    def __str__(self):
        return str(self.rand())

def lcg_solve(val, times):
    r = inverse(LCG.a, LCG.n)
    for _ in range(times):
        val = (r * (val - LCG.b)) % LCG.n
    return val

flag = bytes_to_long("flag{541_LCG_iS_A_baD_pRng_167}")

lcg = LCG(flag)

i = 2 ** 30
while i >= 0:
    lcg.rand()
    i -= 1

print lcg
