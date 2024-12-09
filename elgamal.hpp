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
    el_gamal(const ZZ &large_prime, const ZZ_p &generator);
    void set_pubKey(const ZZ_p &secKey);
    cipherText encrypt(const ZZ &msg);
    ZZ decrypt(const ZZ_p &secKey, const cipherText &c);
    signature digitalSign(const ZZ &msg, const ZZ_p &y);
    bool verify_digitalSign(const signature &s, const ZZ &msg);
};