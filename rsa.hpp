#include "appl_crypto.hpp"

typedef struct abCombined
{
    ZZ a;
    ZZ b;
    abCombined() : a(0), b(0) {}
    abCombined(ZZ a, ZZ b) : a(a), b(b) {}
} abCombined;

class RSA
{
public:
    ZZ_p generateA(const ZZ &phi);
    ZZ rsaEncrypt(const int &msg, const ZZ &n, const ZZ &B);
    int rsaDecrypt(const ZZ &encrypted, const ZZ &n, const ZZ &A);
};