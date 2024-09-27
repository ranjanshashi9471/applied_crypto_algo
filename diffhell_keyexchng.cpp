#include "diffhell_keyexchng.hpp"

person::person(ZZ_p secretKey)
{
    this->personSecret = secretKey;
}

ZZ_p person::person_set_p(ZZ_p g)
{
    ZZ_p B = power(g, conv<ZZ>(this->personSecret));
    return B;
}

ZZ_p person::person_set_p1(ZZ_p person2PubKey)
{
    ZZ_p B1 = power(person2PubKey, conv<ZZ>(this->personSecret));
    return B1;
}

diffie_hellman::diffie_hellman(ZZ_p g)
{
    this->g = g;
}

void diffie_hellman::start_key_exchange(person *alice, person *bob)
{
    this->A = alice->person_set_p(this->g);
    this->B = bob->person_set_p(this->g);
    this->A1 = alice->person_set_p1(this->A);
    this->B1 = bob->person_set_p1(this->B);
}