#include "elCurve.hpp"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

elCurve::elCurve(const ZZ &p, const ellipt_curve &a, const point &P)
{
  this->generator = P; // generator a point on elcurve
  this->e1 = a;        // curve parameters a&b
  this->p = p;         // group Zp
}

bool elCurve::chkResidue(const ZZ_p &ySquare)
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
  // cout << "y coordinates are: (" << p.x << ", " << p.y << ")" << endl;
  return p;
}

bool elCurve::isInfinity(const point &P)
{
  if (P.x == 0 && P.y == 1)
    return true;
  else
    return false;
}

point elCurve::pointNegation(const point &P)
{
  point p(P.x, P.y);
  p.y = to_ZZ_p(this->p - conv<ZZ>(p.y));
  return p;
}

point elCurve::genPublicKey(const ZZ &secret)
{
  return scalarMult(secret, this->generator);
}

encryptedText elCurve::elCurveEncrypt(const point &msg, const point &Q)
{
  ZZ_p y = random_ZZ_p();
  encryptedText e1;
  e1.c1 = scalarMult(rep(y), this->generator);
  e1.c2 = pointAddDouble(msg, scalarMult(rep(y), Q));
  return e1;
}

point elCurve::elCurveDecrypt(const encryptedText &e1, const ZZ &secret)
{
  return (pointAddDouble(e1.c2, pointNegation(scalarMult(secret, e1.c1))));
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
    lambda = ((3 * (P.x) * (P.x)) + this->e1.a) * (1 / (2 * P.y));
  else if ((P.x == Q.x) && ((P.y + Q.y) == 0))
  {
    R.x = 0;
    R.y = 1;
    return R;
  }
  else
    lambda = (Q.y - P.y) * inv(Q.x - P.x);
  R.x = lambda * lambda - P.x - Q.x;
  R.y = (lambda * (P.x - R.x)) - P.y;
  return R;
}

point elCurve::scalarMult(const ZZ &m, const point &P)
{
  ZZ_p ysqare = power(P.x, to_ZZ(3));
  ysqare += (this->e1.a) * (P.x);
  ysqare += this->e1.b;
  if (chkResidue(ysqare))
  {
    point y = getY(ysqare); // it holds both the y coordinates corresponding to x of P.
    if (!(y.x == P.y || y.y == P.y))
      return P;
  }
  point Q(to_ZZ_p(0), to_ZZ_p(1));
  unsigned long long totbits = NumBits(m);
  while (totbits > 0)
  {
    ZZ no = 1 & (m >> (totbits - 1));
    totbits--;
    if (no == 1)
    {
      // Double and Add
      Q = pointAddDouble(Q, Q);
      Q = pointAddDouble(P, Q);
    }
    else
      Q = pointAddDouble(Q, Q); // Double and skip
  }
  // cout << "(" << Q.x << "," << Q.y << ")\n";
  return Q;
}