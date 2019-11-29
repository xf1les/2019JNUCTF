from Crypto.Util.number import bytes_to_long
from FLAG import flag

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

seed = bytes_to_long(flag)
lcg = LCG(seed)

times = 2 ** 30
while times > 0:
    lcg.rand()
    times -= 1
    #i -= 1

print lcg # 0xaf08e8ece96f637d3719fa1c4f0a9f88b3d330615108dd36f430c159308395b2
