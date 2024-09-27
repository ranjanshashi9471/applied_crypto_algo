#include "elgamal.hpp"

el_gamal::el_gamal(ZZ large_prime, ZZ_p generator)
{
    this->p = large_prime;
    this->g = generator;
}

void el_gamal::start_elgamal_encDec(ZZ_p secretKey, ZZ msg)
{
    gen_pubKey(secretKey);
    ZZ y = RandomBnd(this->p);
    encrypt_elgamal(msg, y);
    ZZ msg1 = decrypt_elgamal(secretKey);
    cout << "Decypted message is ::" << msg1 << endl;
}

void el_gamal::gen_pubKey(ZZ_p secretKey)
{
    this->h = power(this->g, rep(secretKey));
}

void el_gamal::encrypt_elgamal(ZZ msg, ZZ y)
{
    ZZ_p shared = power(h, y);
    (this->cipher).c1 = power(g, y);
    (this->cipher).c2 = conv<ZZ_p>(msg * conv<ZZ>(shared));
    cout << "Encrypted msg is ::" << (this->cipher).c1 << "  " << (this->cipher).c2 << endl;
}

ZZ el_gamal::decrypt_elgamal(ZZ_p x)
{
    ZZ_p msg;
    ZZ_p C1x = power((this->cipher).c1, rep(x));
    C1x = 1 / C1x;
    msg = ((this->cipher).c2) * C1x;
    return (conv<ZZ>(msg));
}

void el_gamal::start_elgamal_digiSign(ZZ_p secKey, ZZ msg)
{
    gen_pubKey(secKey);
    digitalSign_elgamal(msg, secKey);
    verify_digitalSign_elgamal(msg);
}

void el_gamal::digitalSign_elgamal(ZZ msg, ZZ_p x)
{
    ZZ_p y;

    while (1)
    {
        y = random_ZZ_p();
        if (GCD(rep(y), this->p - 1) == 1)
        {
            break;
        }
    }
    ZZ_p gamma = power(this->g, rep(y));
    ZZ_p::init(this->p - 1);
    ZZ_p yInv = inv(y);
    ZZ_p arg1 = x * gamma;
    arg1 = conv<ZZ_p>(msg - conv<ZZ>(arg1));
    ZZ_p delta = (arg1 * yInv);
    (this->s1).gamma = (gamma);
    (this->s1).delta = (delta);
    ZZ_p::init(p);
}

void el_gamal::verify_digitalSign_elgamal(ZZ msg)
{
    ZZ_p a1 = power((this->h), conv<ZZ>((this->s1).gamma));
    ZZ_p a2 = power((this->s1).gamma, conv<ZZ>((this->s1).delta));
    ZZ_p res = a1 * a2;
    ZZ_p rhs = power(this->g, conv<ZZ>(msg));
    if (res == rhs)
        cout << "Signature Verified\n";
    else
        cout << "Signature Forged\n";
}