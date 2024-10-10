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

void elCurve::getPoint(ZZ_p x, ZZ_p ysquare, vector<point> &points)
{
    point p1, p2;
    p1.x = x;
    p2.x = x;
    p1.y = power(ysquare, (this->p + 1) / 4);
    p2.y = conv<ZZ_p>(-1 * p1.y);
    points.push_back(p1);
    points.push_back(p2);
}

void elCurve::getAllPoints(vector<point> &points)
{
    for (ZZ i = to_ZZ(0); i < p; i++)
    {
        ZZ_p ysqare = power(conv<ZZ_p>(i), to_ZZ(3));
        ysqare += a * to_ZZ_p(i);
        ysqare += b;
        if (chkResidue(ysqare))
        {
            getPoint(to_ZZ_p(i), ysqare, points);
        }
    }
}