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

        // diffiehell
        p = conv<ZZ>("137");
        ZZ_p::init(p);

        dl_person alice(conv<ZZ_p>("15"));
        dl_person bob(conv<ZZ_p>("125"));

        ZZ_p A = alice.set_publickey(conv<ZZ_p>("3"));
        ZZ_p B = bob.set_publickey(conv<ZZ_p>("3"));

        alice.set_comshared(B);
        bob.set_comshared(A);

        bruteattack_dlp(p, conv<ZZ_p>("3"), A);
        bruteattack_dlp(p, conv<ZZ_p>("3"), B);

        // Elgamal
        p = conv<ZZ>("467");
        ZZ_p::init(p);
        el_gamal e1(p, conv<ZZ_p>("2"));
        // e1.start_elgamal_encDec(conv<ZZ_p>("5"), conv<ZZ>("9"));
        e1.start_elgamal_digiSign(conv<ZZ_p>("127"), conv<ZZ>("100"));

        return 0;
}