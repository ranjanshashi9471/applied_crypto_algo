#include "appl_crypto.hpp"

class dlp
{
private:
    ZZ x, p;
    ZZ_p g, h, h1;
    void calc_dlp_h();

public:
    dlp(ZZ a);
    void setparameters(ZZ_p g, ZZ x);
    void solve_dlp();
};