#include "bruteforce_dlp.hpp"

ZZ bruteattack_dlp(ZZ p, ZZ_p g, ZZ_p pubKey)
{
    ZZ i;
    bool flag = 0;
    for (i = 0; i < p; i++)
    {
        ZZ_p h1 = power(g, i);
        if (h1 == pubKey)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        cout << "\n DLP solved for x::" << i << endl;
        return i;
    }
    else
    {
        cout << "\n DLP not solved" << endl;
        return conv<ZZ>("-1");
    }
}