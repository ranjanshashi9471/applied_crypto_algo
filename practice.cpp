#include <iostream>
#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;

int main()
{
    ZZ_p::init(ZZ(137));
    ZZ_p x = power(to_ZZ_p(3), to_ZZ(75));
    cout << "x" << x << endl;
}