#include "bruteforce_dlp.hpp"
dlp::dlp(ZZ a)
{
    ZZ_p::init(a);
    this->p = a;
}

void dlp::calc_dlp_h()
{
    h = power(g, x);
}
void dlp::setparameters(ZZ_p g, ZZ x)
{
    this->g = g;
    this->x = x;
    calc_dlp_h();
}
void dlp::solve_dlp()
{
    int i;
    char flag = 0;
    for (i = 0; i < p; i++)
    {
        h1 = power(g, i);
        if (h1 == h)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        cout << "\n DLP solved for x::" << i << endl;
    }
    else
    {
        cout << "\n DLP not solved" << endl;
    }
}