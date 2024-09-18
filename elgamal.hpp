#include "appl_crypto.hpp"
class el_gamal
{
private:
    unsigned char *char_to_ascii(string in, unsigned int len);
    unsigned char *ascii_to_char(unsigned char *in, unsigned int len);
    void encrypt_elgamal(int msg, ZZ y);
    ZZ decrypt_elgamal(ZZ x);
    void digitalSign_elgamal(int msg, ZZ y);
    void verify_digitalSign_elgamal(ZZ msg);

public:
    ZZ p, gamma, delta;
    ZZ_p g, h, C1, C2;
    el_gamal(ZZ large_prime);
    ZZ alice_gen_pubKey();
    void bob();
    void alice(ZZ x);
};