// g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
#include "crypto_main.hpp"

int main()
{
        ZZ p = conv<ZZ>("1009)");
        ZZ_p::init(p);
        ZZ_p g = conv<ZZ_p>("999");
        ZZ x = conv<ZZ>("500");
        ZZ_p h = power(g, x);

        bruteattack_dlp(p, g, h);

        p = conv<ZZ>("137");
        ZZ_p::init(p);
        person alice(conv<ZZ_p>("15"));
        person bob(conv<ZZ_p>("125"));
        diffie_hellman d2(conv<ZZ_p>("3"));
        d2.start_key_exchange(&alice, &bob);

        bruteattack_dlp(p, d2.g, d2.A);
        bruteattack_dlp(p, d2.g, d2.B);

        // d2.eve();

        // el_gamal e1(conv<ZZ>("467"));

        return 0;
}