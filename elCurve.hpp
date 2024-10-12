#include "appl_crypto.hpp"

typedef struct point
{
    ZZ_p x;
    ZZ_p y;
    point() : x(0), y(0) {}
    point(ZZ_p x, ZZ_p y) : x(x), y(y) {}
} point;

class elCurve
{
private:
    bool chkResidue(ZZ_p a);
    bool isInfinity(const point &P);
    point getY(const ZZ_p &ySquare);

public:
    ZZ p;
    ZZ_p a, b;
    elCurve(ZZ p, ZZ_p a, ZZ_p b);
    point pointAddDouble(const point &P, const point &Q);
    point scalarMult(long long m, const point &P);
};