#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

// Function to compute lcm of integers from 1 to B
ZZ computeLCM(int B)
{
    ZZ lcm = ZZ(1);
    for (int i = 1; i <= B; ++i)
    {
        lcm = (lcm / GCD(lcm, ZZ(i))) * ZZ(i);
    }
    return lcm;
}

// Pollard's p-1 algorithm for factoring
ZZ pollardsPminus1(const ZZ &n, int B)
{
    ZZ a = RandomBnd(n - 2) + 2; // Random base a in range [2, n-1]
    cout << "a is " << a << endl;
    ZZ d;
    for (ZZ i = ZZ(2); i < to_ZZ(B); i++)
    {
        a = PowerMod(a, i, n);
        cout << "New (a^i\%n) = " << a << endl;
        d = GCD(a - 1, n);
        cout << "GCD(a-1, n) = " << d << endl;
        if (d > 1 && d < n)
            return d; // Non-trivial factor
    }
    // ZZ lcm = computeLCM(B);      // Compute lcm(1, 2, ..., B)
    // ZZ aM = PowerMod(a, lcm, n); // Compute a^lcm % n
    // ZZ d = GCD(aM - 1, n);       // Compute gcd(a^M - 1, n)
    return ZZ(0); // Failure
}

int main()
{
    ZZ n = ZZ(1717); // Number to be factored
    int B = 10;      // Smoothness bound
    cout << "Factoring n = " << n << " using Pollard's p-1 algorithm with bound B = " << B << endl;

    ZZ factor = pollardsPminus1(n, B);
    if (factor == 0)
    {
        cout << "Pollard's p-1 algorithm failed to find a factor. Try increasing B." << endl;
    }
    else
    {
        cout << "A non-trivial factor of " << n << " is " << factor << endl;
        cout << "Other factor is " << n / factor << endl;
    }

    return 0;
}
