#include <iostream>
#include <NTL/ZZ.h>
#include <vector>
#include <map>

using namespace std;
using namespace NTL;

// State structure for R-Adding Walk
struct State
{
    ZZ s0, t0;
};

// R partitions for the algorithm
const int R = 8; // Number of partitions
vector<ZZ> sigma_vals = {ZZ(56), ZZ(23), ZZ(39), ZZ(60), ZZ(2), ZZ(19), ZZ(17), ZZ(5)};
vector<ZZ> tau_vals = {ZZ(5), ZZ(6), ZZ(5), ZZ(18), ZZ(22), ZZ(50), ZZ(42), ZZ(35)};
vector<ZZ> m_vals(R); //= {37, 63, 32, 25, 14, 43, 63, 50}; // Precomputed a[i], b[i] values

// Initialize the R partitions
// void initRPartitions(const ZZ &p)
// {
//     // sigma_vals = {56, 23, 39, 60, 2, 19, 17, 5};
//     for (int i = 0; i < R; i++)
//     {
//         sigma_vals[i] = RandomBnd(p - 1);
//         cout << "sigma val " << sigma_vals[i] << endl;
//         tau_vals[i] = RandomBnd(p - 1);
//         cout << "tau val " << tau_vals[i] << endl;
//     }
// }

void generateMs(const ZZ &p, const ZZ &g, const ZZ &h)
{
    for (int i = 0; i < R; i++)
    {
        m_vals[i] = (PowerMod(g, (sigma_vals[i]), p) * PowerMod(h, (tau_vals[i]), p)) % p;
        cout << "M val " << m_vals[i] << endl;
    }
}

// Pollard's Rho with R-Adding Walk for DLP
ZZ pollardsRhoRAddingWalk(const ZZ &g, const ZZ &h, const ZZ &p)
{
    ZZ diff_t;
    // initRPartitions(p);
    generateMs(p, g, h);
    cout << "rhoalgo" << endl;
    map<ZZ, State> list;
    State state;
    state.s0 = RandomBnd(p);
    state.t0 = RandomBnd(p);
    ZZ x0 = (PowerMod(g, state.s0, p) * PowerMod(h, state.t0, p) % p);
    cout << "first x0 is " << x0 << endl;
    cout << "1state s0: " << state.s0 << ", t0: " << state.t0 << endl;

    list[x0] = state;
    while (true)
    {
        ZZ prev_x0 = x0;
        int u = prev_x0 % R;
        x0 = (prev_x0 * m_vals[u]) % p;
        cout << "New x0 is " << x0 << endl;
        cout << "u is " << u << endl;
        state.s0 += sigma_vals[u];
        state.t0 += tau_vals[u];
        cout << "state s0: " << state.s0 << ", t0: " << state.t0 << endl;

        // Check for collision
        if (list.find(x0) != list.end())
        {
            cout << "found duplicate r" << endl;
            diff_t = (list[x0].t0 - state.t0) % (p - 1);
            if (diff_t != 0)
            {
                break;
            }
            else
            {
                cout << "diff = 0" << endl;
            }
        }
        else
        {
            list[x0] = state;
        }
    }

    // Solve for x
    ZZ diff_s = (list[x0].s0 - state.s0) % (p - 1);

    if (diff_t == 0)
    {
        cout << "Failure: Collision doesn't lead to a solution." << endl;
        return ZZ(-1);
    }

    // Compute modular inverse of diff_b
    ZZ x, inv_b;
    if (InvModStatus(inv_b, diff_t, p - 1) == 0)
    {
        x = (diff_s * inv_b) % (p - 1);
        if (x < 0)
            x += (p - 1); // Ensure x is positive
        return x;
    }
    else
    {
        cout << "Failure: Modular inverse does not exist for diff_b." << endl;
        return ZZ(-1);
    }
}

int main()
{
    ZZ p = ZZ(61); // Prime modulus
    ZZ g = ZZ(2);  // Generator
    ZZ h = ZZ(45); // Target value (h = g^x mod p)

    cout << "Solving DLP: g^x ≡ h (mod p)" << endl;
    cout << "p = " << p << ", g = " << g << ", h = " << h << endl;

    ZZ x = pollardsRhoRAddingWalk(g, h, p);
    if (x != -1)
    {
        cout << "Solution found: x = " << x << endl;
        cout << "Verification: g^x mod p = " << PowerMod(g, x, p) << endl;
    }
    else
    {
        cout << "Failed to solve the DLP." << endl;
    }

    return 0;
}
