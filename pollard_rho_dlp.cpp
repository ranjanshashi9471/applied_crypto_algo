#include <iostream>
#include <NTL/ZZ.h>
#include <map>

using namespace std;
using namespace NTL;

// Structure to store (X, a, b) triplet
struct State
{
    ZZ a, b;
};

// // Function to update X, a, b based on partitions
// void partitionUpdate(const ZZ &g, const ZZ &h, const ZZ &p, State &state)
// {
// }

// Pollard's Rho for Discrete Logarithm Problem
ZZ pollardsRhoDLP(const ZZ &g, const ZZ &h, const ZZ &p)
{
    State tortoise = {ZZ(0), ZZ(0)}; // a0, b0
    ZZ r0 = ZZ(1);
    ZZ prev_r0;
    ZZ diff_a;
    ZZ diff_b;
    map<ZZ, State> savedState;
    savedState[r0] = tortoise;

    // Floyd's cycle-finding algorithm
    do
    {
        // State tmp;
        prev_r0 = r0;
        if (r0 % 3 == 0)
        {
            r0 = (PowerMod(g, tortoise.a, p) * PowerMod(h, tortoise.b, p)) % p;
            // r0 = (PowerMod(g, savedState[prev_r0].a, p) * PowerMod(h, savedState[prev_r0].b, p)) % p;
            r0 = (r0 * r0) % p;
            tortoise.a = (2 * tortoise.a) % (p - 1);
            tortoise.b = (2 * tortoise.b) % (p - 1);
            // tortoise.a = (2 * savedState[prev_r0].a) % (p - 1);
            // tortoise.b = (2 * savedState[prev_r0].b) % (p - 1);
        }
        else if (r0 % 3 == 1)
        {
            r0 = (PowerMod(g, tortoise.a, p) * PowerMod(h, tortoise.b, p) * g) % p;
            // r0 = (PowerMod(g, savedState[prev_r0].a, p) * PowerMod(h, savedState[prev_r0].b, p) * g) % p;
            // tortoise.a = (savedState[prev_r0].a + 1) % (p - 1);
            // tortoise.b = (savedState[prev_r0].b) % (p - 1);
            tortoise.a = (tortoise.a + 1) % (p - 1);
            tortoise.b = (tortoise.b) % (p - 1);
        }
        else
        {
            r0 = (PowerMod(g, tortoise.a, p) * PowerMod(h, tortoise.b, p)) % p;
            // r0 = (PowerMod(g, savedState[prev_r0].a, p) * PowerMod(h, savedState[prev_r0].b, p)) % p;
            r0 = (r0 * h) % p;
            // tortoise.b = (savedState[prev_r0].b + 1) % (p - 1);
            // tortoise.a = savedState[prev_r0].a % (p - 1);
            tortoise.b = (tortoise.b + 1) % (p - 1);
            tortoise.a = tortoise.a % (p - 1);
        }
        cout << "r0 is " << r0 << endl;
        cout << "tmp a: " << tortoise.a << ", b: " << tortoise.b << endl;
        // if (savedState.find(r0) != savedState.end())
        // {
        //     cout << "found duplicate r" << endl;
        //     diff_b = (savedState[r0].b - tmp.b) % (p - 1);
        //     if (diff_b != 0)
        //     {
        //         tortoise = tmp;
        //         break;
        //     }
        //     else
        //     {
        //         cout << "diff = 0" << endl;
        //     }
        // }
        // else
        // {
        //     savedState[r0] = tmp;
        // }
    } while (1);

    // // Collision detected: solve for x
    // diff_a = (tortoise.a - savedState[r0].a) % (p - 1);
    // // diff_b = (savedState[r0].b - tortoise.b) % (p - 1);

    // // Solve diff_a ≡ diff_b * x (mod p-1)
    // ZZ x;
    // if (InvModStatus(x, diff_b, p - 1) == 0)
    // {
    //     cout << "inv(a11-a5)=" << x << endl;
    //     x = (x * diff_a) % (p - 1);
    //     if (x < 0)
    //         x += (p - 1); // Ensure positive result
    //     return x;
    // }
    // else
    // {
    //     cout << "diff_b is : " << diff_b << endl;
    //     cout << "Failure: No modular inverse for diff_b exists." << endl;
    //     return ZZ(-1);
    // }
}

int main()
{
    ZZ p = ZZ(137); // Prime modulus
    ZZ g = ZZ(3);   // Generator
    ZZ h = ZZ(106); // Target value (h = g^x mod p)

    cout << "Solving DLP: g^x ≡ h (mod p)" << endl;
    cout << "p = " << p << ", g = " << g << ", h = " << h << endl;

    ZZ x = pollardsRhoDLP(g, h, p);
    if (x != -1)
    {
        cout << "Solution found: x = " << x << endl;
    }
    else
    {
        cout << "Failed to solve the DLP." << endl;
    }

    return 0;
}
