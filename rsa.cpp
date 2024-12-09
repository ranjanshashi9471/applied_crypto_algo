#include "rsa.hpp"

ZZ_p RSA::generateA(const ZZ &phi)
{
    ZZ_p::init(phi);
    ZZ_p A = random_ZZ_p();
    while (GCD(rep(A), phi) != 1)
    {
        A = random_ZZ_p();
    }
    return A;
}

ZZ RSA::rsaEncrypt(const int &msg, const ZZ &n, const ZZ &B)
{
    ZZ tmp = PowerMod(ZZ(msg), B, n);
    cout << "Encrypted Text is " << tmp << endl;
    return tmp;
}

int RSA::rsaDecrypt(const ZZ &encrypted, const ZZ &n, const ZZ &A)
{
    ZZ tmp = PowerMod(encrypted, A, n);
    cout << "Decrypted Msg is " << tmp << endl;
    return to_int(tmp);
}
