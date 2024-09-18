#include "elgamal.hpp"

el_gamal::el_gamal(ZZ large_prime)
{
    ZZ_p::init(large_prime);
    this->p = large_prime;
    cout << "enter the generator of group\n";
    cin >> this->g;
    ZZ x1 = alice_gen_pubKey();
    bob();
    alice(x1);
}

ZZ el_gamal::alice_gen_pubKey()
{
    ZZ x;
    cout << "Enter secret key of alice" << endl;
    cin >> x;
    this->h = power(this->g, x);
    return x;
}

void el_gamal::bob()
{
    ZZ bsecKey;
    cout << "Enter Secret key of bob." << endl;
    cin >> bsecKey;
    int msg;
    cout << "Enter a number\n";
    cin >> msg;
    encrypt_elgamal(msg, bsecKey);
    digitalSign_elgamal(msg, bsecKey);
}

void el_gamal::alice(ZZ asecretKey)
{
    ZZ msg = decrypt_elgamal(asecretKey);
    verify_digitalSign_elgamal(msg);
}

void el_gamal::encrypt_elgamal(int msg, ZZ y)
{
    C1 = power(g, y);
    C2 = msg * power(h, y);
    cout << "encrypted msg is ::" << C1 << "  " << C2 << endl;
}

ZZ el_gamal::decrypt_elgamal(ZZ x)
{
    ZZ_p msg;
    ZZ_p C1x = power(this->C1, x);
    C1x = 1 / C1x;
    msg = (this->C2) * C1x;
    cout << "Decoded message is ::" << msg << endl;
    return (conv<ZZ>(msg));
}

void el_gamal::digitalSign_elgamal(int msg, ZZ prvkeyB)
{
    ZZ y;
    cout << "Enter value of y" << endl;
    cin >> y;
    ZZ_p::init(this->p - 1);
    ZZ_p gamma = power(this->g, conv<ZZ>(y));

    // cout << "gamma is ::" << this->gamma;

    ZZ_p prvkeyBinv = 1 / conv<ZZ_p>(y);
    ZZ_p arg1 = conv<ZZ_p>(prvkeyB) * conv<ZZ_p>(this->gamma);

    // cout << "arg1::" << arg1 << endl;

    ZZ_p delta = ((msg - arg1) * prvkeyBinv);
    this->gamma = conv<ZZ>(gamma);
    this->delta = conv<ZZ>(delta);
}

void el_gamal::verify_digitalSign_elgamal(ZZ msg)
{
    ZZ_p a1 = power((this->h), this->gamma);
    ZZ_p a2 = power(conv<ZZ_p>(this->gamma), conv<ZZ>(this->delta));
    ZZ_p res = a1 * a2;
    ZZ_p rhs = power(conv<ZZ_p>(this->g), msg);
    if (res == rhs)
    {
        cout << "Signature Verified\n";
    }
    else
    {
        cout << "Signature Forged\n";
    }
}