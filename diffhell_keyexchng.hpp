#include "appl_crypto.hpp"
class diffie_hellman
{
private:
    ZZ_p A1, B1;
    ZZ alice_set_A();
    ZZ bob_set_B();
    void alice_set_A1(ZZ a);
    void bob_set_B1(ZZ b);

public:
    ZZ p;
    ZZ_p A, B, g, h;
    diffie_hellman(ZZ p, ZZ_p g);
    void eve();
};