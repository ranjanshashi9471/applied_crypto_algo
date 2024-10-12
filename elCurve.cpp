#include "elCurve.hpp"

elCurve::elCurve(ZZ p, ZZ_p a, ZZ_p b)
{
    this->a = a;
    this->b = b;
    this->p = p;
}

bool elCurve::chkResidue(ZZ_p ySquare)
{
    // works for all primes(p) except 2
    // y^2=a%p

    ZZ_p a = power(ySquare, (this->p - 1) / 2);
    return (a == 1);
}

point elCurve::getY(const ZZ_p &ysquare)
{
    point p;
    p.x = power(ysquare, (this->p + 1) / 4);
    p.y = conv<ZZ_p>(-1 * p.x);
    return p;
}

bool elCurve::isInfinity(const point &P)
{
    if (P.x == 0 && P.y == 1)
        return true;
    else
        return false;
}

point elCurve::pointAddDouble(const point &P, const point &Q)
{
    if (isInfinity(P))
        return Q;
    if (isInfinity(Q))
        return P;

    ZZ_p lambda;
    point R;
    if ((P.x == Q.x) && (P.y == Q.y))
    {
        lambda = ((3 * (P.x) * (P.x)) + this->a) * (1 / (2 * P.y));
    }
    else if ((P.x == Q.x) && ((P.y + Q.y) == 0))
    {
        R.x = 0;
        R.y = 1;
        return R;
    }
    else
    {
        lambda = (Q.y - P.y) * inv(Q.x - P.x);
    }
    R.x = lambda * lambda - P.x - Q.x;
    R.y = (lambda * (P.x - R.x)) - P.y;
    return R;
}

point elCurve::scalarMult(long long m, const point &P)
{
    ZZ_p ysqare = power(P.x, to_ZZ(3));
    ysqare += a * (P.x);
    ysqare += b;
    if (chkResidue(ysqare))
    {
        point y = getY(ysqare);
        if (!(y.x == P.y || y.y == P.y))
        {
            return P;
        }
    }
    point Q(to_ZZ_p(0), to_ZZ_p(1));
    int bits = floor(log2(m)) + 1;
    while (bits > 0)
    {
        int no = 1 & (m >> (bits - 1));
        bits--;
        if (no == 1)
        {
            // Double and Add
            Q = pointAddDouble(Q, Q);
            Q = pointAddDouble(P, Q);
        }
        else
        {
            Q = pointAddDouble(Q, Q);
            // Double and skip
        }
    }
    cout << "(" << Q.x << "," << Q.y << ")\n";
    return Q;
}