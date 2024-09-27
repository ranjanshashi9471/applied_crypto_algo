#include "appl_crypto.hpp"

class person
{
private:
    ZZ_p personSecret;

public:
    person(ZZ_p personSecret);
    ZZ_p person_set_p(ZZ_p g);
    ZZ_p person_set_p1(ZZ_p person2PubKey);
};

class diffie_hellman
{
private:
    ZZ_p A1, B1;

public:
    ZZ_p A, B, g;
    diffie_hellman(ZZ_p g);
    void start_key_exchange(person *alice, person *bob);
};