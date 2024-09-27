#include "appl_crypto.hpp"

typedef struct signature
{
    ZZ_p gamma;
    ZZ_p delta;
} signature;

typedef struct cipherText
{
    ZZ_p c1;
    ZZ_p c2;
} cipherText;

class el_gamal
{
private:
    void encrypt_elgamal(ZZ msg, ZZ y);
    ZZ decrypt_elgamal(ZZ_p x);

    void digitalSign_elgamal(ZZ msg, ZZ_p y);
    void verify_digitalSign_elgamal(ZZ msg);

public:
    ZZ p;
    ZZ_p g, h;
    signature s1;
    cipherText cipher;

    el_gamal(ZZ large_prime, ZZ_p generator);
    void start_elgamal_encDec(ZZ_p secKey, ZZ msg);
    void start_elgamal_digiSign(ZZ_p secKey, ZZ msg);
    void gen_pubKey(ZZ_p secKey);
};