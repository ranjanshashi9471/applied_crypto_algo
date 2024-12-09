#include "diffhell_keyexchng.hpp"

dl_person::dl_person(ZZ_p secretKey)
{
    this->personSecret = secretKey;
}

ZZ_p dl_person::set_publickey(ZZ_p g)
{
    ZZ_p B = power(g, conv<ZZ>(this->personSecret));
    return B;
}

void dl_person::set_comshared(ZZ_p person2PubKey)
{
    ZZ_p B1 = power(person2PubKey, conv<ZZ>(this->personSecret));
    cout << "shared key is :" << B1 << endl;
}