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
public:
    ZZ p;
    ZZ_p g, h;
    signature s1;
    cipherText cipher;

    el_gamal(ZZ large_prime, ZZ_p generator);
    void set_pubKey(ZZ_p secKey);

    cipherText encrypt(ZZ msg);
    ZZ decrypt(ZZ_p secKey, cipherText c);

    signature digitalSign(ZZ msg, ZZ_p y);
    bool verify_digitalSign(signature s, ZZ msg);
};