#include "diffhell_keyexchng.hpp"

ZZ diffie_hellman::alice_set_A()
{

    ZZ a;
    cout << "Enter value of a for alice\n";
    cin >> a;
    A = power(g, a);
    cout << "value of A :: " << A << endl;
    return a;
}
ZZ diffie_hellman::bob_set_B()
{
    ZZ b;
    cout << "Enter value of b for bob\n";
    cin >> b;
    B = power(g, b);
    cout << "value of B :: " << B << endl;
    return b;
}
void diffie_hellman::alice_set_A1(ZZ a)
{
    A1 = power(B, a);
    cout << "value of A1 :: " << A1 << endl;
}
void diffie_hellman::bob_set_B1(ZZ b)
{
    B1 = power(A, b);
    cout << "value of B1 :: " << B1 << endl;
}

diffie_hellman::diffie_hellman(ZZ p, ZZ_p g)
{
    cout << "Inside class constructor\n";
    ZZ_p::init(p);
    this->p = p;
    this->g = g;
    ZZ m = alice_set_A();
    ZZ n = bob_set_B();
    alice_set_A1(m);
    bob_set_B1(n);
    eve();
}

void diffie_hellman::eve()
{
    ZZ i;
    int flag = 0;
    ZZ_p j = conv<ZZ_p>("0");
    for (i = 0; i <= p; i++)
    {
        j = power(g, i);
        if (j == A)
        {
            flag = 1;
            break;
        }
        else if (j == B)
        {
            flag = 2;
            break;
        }
    }
    if (flag == 1)
    {
        j = power(B, i);
        cout << "Found the private Key :: " << j << endl;
    }
    else if (flag == 2)
    {
        j = power(A, i);
        cout << "Found the private Key :: " << j << endl;
    }
    else
    {
        cout << "couldn't Find the private Key :: " << endl;
    }
}