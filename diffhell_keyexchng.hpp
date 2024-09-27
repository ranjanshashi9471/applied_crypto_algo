#include "appl_crypto.hpp"

class dl_person
{
private:
    ZZ_p personSecret;

public:
    dl_person(ZZ_p personSecret);
    ZZ_p set_publickey(ZZ_p g);
    void set_comshared(ZZ_p PubKey);
};