#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

// Pollard's Rho algorithm for factoring
ZZ pollardsRho(const ZZ &n)
{
    if (n % 2 == 0)
        return ZZ(2); // Quick check for even numbers

    ZZ x = ZZ(865); // RandomBnd(n); // Random starting point x in [0, n)
    ZZ y = x;       // y starts as x
    ZZ c = ZZ(1);   // RandomBnd(n); // Random constant c in [0, n)
    ZZ d = ZZ(1);   // Initial gcd value

    cout << "Initial values: x = " << x << ", y = " << y << ", c = " << c << endl;

    while (d == 1)
    {
        // f(x) = (x^2 + c) mod n
        x = (PowerMod(x, ZZ(2), n) + c) % n;
        y = (PowerMod(y, ZZ(2), n) + c) % n;
        cout << "f(y): " << y << endl;
        y = (PowerMod(y, ZZ(2), n) + c) % n;

        if (abs(x - y) == 0)
        {
            cout << "abs(x-x') == 0" << endl;
            x = RandomBnd(n);
            y = x;
            d = 1;
            cout << "Initial values: x = " << x << ", y = " << y << ", c = " << c << endl;
            continue;
        }

        d = GCD(abs(x - y), n); // Compute gcd(|x-y|, n)

        cout << "x = " << x << ", f(f(y)) = " << y << ", gcd = " << d << endl;

        if (d == n)
            return ZZ(0); // Failure (cannot factorize further)
    }
    return d;
}

int main()
{
    ZZ n = ZZ(1717); // Number to be factored
    cout << "Factoring n = " << n << " using Pollard's Rho algorithm." << endl;

    ZZ factor = pollardsRho(n);
    if (factor == 0)
    {
        cout << "Pollard's Rho failed to find a factor." << endl;
    }
    else
    {
        cout << "A non-trivial factor of " << n << " is " << factor << endl;
        cout << "Other factor is " << n / factor << endl;
    }

    return 0;
}
