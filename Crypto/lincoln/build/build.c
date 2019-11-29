#include <gmp.h>

int main()
{
    mpz_t a, b, n, state;

    mpz_init(a);
    mpz_init(b);
    mpz_init(n);
    mpz_init(state);

    mpz_set_str(a, "db626d86f5dc6cf4ec8c4ca4f4b9dab3", 16);
    mpz_set_str(b, "b2dab99e8973e463ab58a4403d35675f", 16);
    mpz_set_str(n, "d5aef35973977bd35331490990b6b54b80d44bdb621f861848f4377c54cf6649", 16);
    mpz_set_str(state, "666c61677b3534315f4c43475f69535f415f6261445f70526e675f3136377d", 16);

    long long times = 1073741824;
    for(; times >= 0; --times)
    {
        mpz_mul(state, state, a);
        mpz_add(state, state, b);
        mpz_mod(state, state, n);
    }
    gmp_printf("%Zd\n", state);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(n);
    mpz_clear(state);

}
