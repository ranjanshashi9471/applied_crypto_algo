#include "rsa.hpp"

ZZ_p RSA::generateA(const ZZ &phi)
{
    // ZZ_p::init(phi);
    ZZ_p A = random_ZZ_p();
    while (GCD(rep(A), phi) != 1)
    {
        A = random_ZZ_p();
    }
    return A;
}

ZZ RSA::rsaEncrypt(const int &msg, const ZZ &n, const ZZ &B)
{
    cout << "Encryption starts msg is" << msg << endl;
    ZZ_p::init(n);
    ZZ tmp;
    power(tmp, msg, to_long(B));
    cout << "Msg^B is " << tmp << endl;
    ZZ_p tmp1 = to_ZZ_p(tmp);
    cout << "Encrypted Text is " << tmp1 << endl;
    return tmp;
}

int RSA::rsaDecrypt(const ZZ &encrypted, const ZZ &n, const ZZ &A)
{
    cout << "Decryption Starts" << endl;
    ZZ_p::init(n);
    ZZ tmp;
    power(tmp, encrypted, to_long(A));
    // cout << "Encrypt^A is " << tmp << endl;
    ZZ_p tmp1 = to_ZZ_p(tmp);
    cout << "Decrypted Msg is " << (char)to_int(rep(tmp1)) << endl;
    return to_int(rep(tmp1));
}

ZZ RSA::rsaDigiSign(const int &msg, const ZZ &A, const ZZ &n)
{
    cout << "Digital Signature begins" << endl;
    ZZ s = PowerMod(ZZ(msg), A, n);
    cout << "Digital Signature is " << s << endl;
    return s;
}

bool RSA::verifyDigiSign(const int &msg, const ZZ &B, const ZZ &n, const ZZ &sign)
{
    cout << "Digital Signature begins" << endl;
    ZZ s = PowerMod(sign, B, n);
    cout << "Message is " << s << endl;
    return s == msg;
}