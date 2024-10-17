#include "elgamal.hpp"

el_gamal::el_gamal(const ZZ &large_prime, const ZZ_p &generator)
{
    this->p = large_prime;
    this->g = generator;
}

void el_gamal::set_pubKey(const ZZ_p &secretKey)
{
    this->h = power(this->g, rep(secretKey));
}

cipherText el_gamal::encrypt(const ZZ &msg)
{
    cipherText c;
    ZZ y = RandomBnd(this->p);
    ZZ_p shared = power(h, y);
    c.c1 = power(g, y);
    c.c2 = conv<ZZ_p>(msg * conv<ZZ>(shared));
    cout << "Encrypted msg is ::" << c.c1 << "  " << c.c2 << endl;
    return c;
}

ZZ el_gamal::decrypt(const ZZ_p &x, const cipherText &c)
{
    ZZ_p msg;
    ZZ_p C1x = power(c.c1, rep(x));
    C1x = 1 / C1x;
    msg = (c.c2) * C1x;
    cout << "Decrypted msg is ::" << msg << endl;
    return (conv<ZZ>(msg));
}

signature el_gamal::digitalSign(const ZZ &msg, const ZZ_p &x)
{
    signature s1;
    ZZ_p y;
    while (1)
    {
        y = random_ZZ_p();
        if (GCD(rep(y), this->p - 1) == 1)
            break;
    }
    ZZ_p gamma = power(this->g, rep(y));
    ZZ_p::init(this->p - 1);
    ZZ_p yInv = inv(y);
    ZZ_p arg1 = x * gamma;
    arg1 = conv<ZZ_p>(msg - conv<ZZ>(arg1));
    ZZ_p delta = (arg1 * yInv);
    s1.gamma = (gamma);
    s1.delta = (delta);
    ZZ_p::init(p);
    return s1;
}

bool el_gamal::verify_digitalSign(const signature &s1, const ZZ &msg)
{
    ZZ_p a1 = power((this->h), conv<ZZ>(s1.gamma));
    ZZ_p a2 = power(s1.gamma, conv<ZZ>(s1.delta));
    ZZ_p res = a1 * a2;
    ZZ_p rhs = power(this->g, conv<ZZ>(msg));
    if (res == rhs)
    {
        cout << "Signature Verified\n";
        return 1;
    }
    else
    {
        cout << "Signature Forged\n";
        return 0;
    }
}
