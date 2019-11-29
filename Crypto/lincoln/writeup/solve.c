#include <gmp.h>

/*

    安装依赖：sudo apt install libgmp-dev (Ubuntu/Debian)
    编译方法：gcc solve.c -lgmp -o solve

*/

int main()
{
    mpz_t a, b, n, r, res;

    mpz_init(a);
    mpz_init(b);
    mpz_init(n);
    mpz_init(r);
    mpz_init(res);

    mpz_set_str(a, "db626d86f5dc6cf4ec8c4ca4f4b9dab3", 16);
    mpz_set_str(b, "b2dab99e8973e463ab58a4403d35675f", 16);
    mpz_set_str(n, "d5aef35973977bd35331490990b6b54b80d44bdb621f861848f4377c54cf6649", 16);
    mpz_set_str(res, "af08e8ece96f637d3719fa1c4f0a9f88b3d330615108dd36f430c159308395b2", 16);
    mpz_invert(r, a, n);

    long long times = 1073741825; /* 2 ^ 30 + 1 */
    for(; times > 0; --times)
    {
        mpz_sub(res, res, b);
        mpz_mul(res, res, r);
        mpz_mod(res, res, n);
    }
    gmp_printf("%Zd\n", res);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(n);
    mpz_clear(r);
    mpz_clear(res);

}
