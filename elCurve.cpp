#include "elCurve.hpp"

elCurve::elCurve(const ZZ &p)
{
  this->p = p; // group Zp

  this->e1.a = 23; // curve parameters a&b
  this->e1.b = 10;
  // this->e1 = this->getNonSingCurParams();   // curve parameters a&b
  this->generator.x = 22;
  this->generator.y = 12;
  // this->generator = this->getRandomPoint(); // generator a point on elcurve
}

ZZ_p elCurve::generateAllPoints()
{
  ZZ_p count = to_ZZ_p(0);
  for (ZZ i = to_ZZ(0); i < this->p; i++)
  {
    ZZ_p ysq = this->getYsq(to_ZZ_p(i));
    cout << "i is:" << i << " ysq is:" << ysq << endl;
    if (chkResidue(ysq))
    {
      point p = this->getYCoordinate(ysq);
      cout << "x:" << i << "y1:" << p.x << "y2:" << p.y << endl;
      count += 2;
    }
  }
  count += 1;
  return count;
}

bool elCurve::chkResidue(const ZZ_p &ySquare)
{
  // works for all primes(p) except 2
  // y^2=a%p
  ZZ_p a = power(ySquare, (this->p - 1) / 2);
  cout << "inside chkresidue a:" << a << endl;
  return (a == 1);
}

point elCurve::getRandomPoint()
{
  ZZ_p x, ysq;
  do
  {
    x = random_ZZ_p();
    ysq = this->getYsq(x);
  } while (!chkResidue(ysq));

  point p;
  p.x = x;
  p.y = power(ysq, (this->p + 1) / 4);
  // cout << "y coordinates are: (" << p.x << ", " << p.y << ")" << endl;
  return p;
}

ZZ_p elCurve::getYsq(const ZZ_p &x)
{
  ZZ_p ysq = power(x, to_ZZ(3)) + (this->e1.a * x) + this->e1.b;
  return ysq;
}

point elCurve::getYCoordinate(const ZZ_p &ysq)
{
  // ZZ_p ysq = this->getYsq(x);
  point p1;
  p1.x = power(ysq, (this->p + 1) / 4);
  p1.y = -1 * p1.x;
  return p1;
}

// bool elCurve::chkValidPoint(const point &pt)
// {
//   if(pt.x == 0 && pt.y == 1)
//     return true;
//   ZZ_p ysq = this->getYsq(pt.x);
//   if(chkResidue(ysq)){
//     this->getYCoordinate()
//   }
// }

bool elCurve::isInfinity(const point &P)
{
  if (P.x == 0 && P.y == 1)
    return true;
  else
    return false;
}

point elCurve::pointNegation(const point &P)
{
  point p(P.x, -1 * P.y);

  // p.y = to_ZZ_p(this->p - conv<ZZ>(p.y));
  return p;
}

bool elCurve::chkSingularity(const ellipt_curve &parameters)
{
  ZZ_p tmp = ((4 * power(parameters.a, to_ZZ(3))) + (27 * power(parameters.b, to_ZZ(2))));
  return (tmp == 0);
}

ellipt_curve elCurve::getNonSingCurParams()
{
  ellipt_curve params;
  do
  {
    params.a = random_ZZ_p();
    params.b = random_ZZ_p();
  } while (chkSingularity(params));
  return params;
}

point elCurve::genPublicKey(const ZZ_p &secret)
{
  return scalarMult(secret, this->generator);
}

encryptedText elCurve::elCurveEncrypt(const point &msg, const point &Q)
{
  encryptedText e1;
  ZZ_p y = to_ZZ_p(3);
  // ZZ_p y = random_ZZ_p();
  point tmp = scalarMult(y, this->generator);
  cout << "yP is X: " << tmp.x << "Y: " << tmp.y << endl;
  e1.c1.x = tmp.x;
  e1.c1.y = tmp.y;
  cout << "e1.c1 is X: " << e1.c1.x << "Y: " << e1.c1.y << endl;

  tmp = scalarMult(y, Q);
  cout << "yQ is X: " << tmp.x << "Y: " << tmp.y << endl;
  e1.c2 = this->pointAddDouble(tmp, msg);
  cout << "e1.c2 is X: " << e1.c2.x << "Y: " << e1.c2.y << endl;
  return e1;
}

point elCurve::elCurveDecrypt(const encryptedText &e1, const ZZ_p &secret)
{
  point arg1 = scalarMult(secret, e1.c1);
  cout << "x*enc.c1 is x: " << arg1.x << "y: " << arg1.y << endl;
  arg1 = this->pointNegation(arg1);
  cout << "Negation of x*enc.c1 is x: " << arg1.x << "y: " << arg1.y << endl;
  arg1 = this->pointAddDouble(e1.c2, arg1);
  cout << "c2 + Negation of x*enc.c1 is x: " << arg1.x << "y: " << arg1.y << endl;
  ZZ_p a = to_ZZ_p(1);
  return arg1;
}

point elCurve::pointAddDouble(const point &P, const point &Q)
{
  cout << "pointAddDouble" << endl;
  if (isInfinity(P))
    return Q;
  if (isInfinity(Q))
    return P;

  ZZ_p lambda;
  point R;
  if ((P.x == Q.x) && (P.y == Q.y))
  {
    ZZ_p arg1 = P.x * P.x;
    cout << "x1^2 is: " << arg1 << endl;
    arg1 *= 3;
    cout << "3*x1^2 is: " << arg1 << endl;
    arg1 += this->e1.a;
    cout << "3x1^2+a is : " << arg1 << endl;
    ZZ_p yin2 = (2 * P.y);
    yin2 = 1 / yin2;
    cout << "inv(2y) is: " << yin2 << endl;
    lambda = (arg1 * yin2);
  }
  else if ((P.x == Q.x) && ((P.y + Q.y) == 0))
  {
    R.x = 0;
    R.y = 1;
    return R;
  }
  else
  {
    ZZ_p tmp = inv(Q.x - P.x);
    cout << "inv(Q.x - P.x) :" << tmp << endl;
    lambda = (Q.y - P.y) * tmp;
    cout << "lambda is :" << lambda << endl;
  }
  R.x = lambda * lambda - P.x - Q.x;
  R.y = (lambda * (P.x - R.x)) - P.y;
  return R;
}

point elCurve::scalarMult(const ZZ_p &x, const point &P)
{
  ZZ_p::init(this->p);
  cout << "Scalar Multiplication of x:" << x << " , (" << P.x << "," << P.y
       << ")" << endl;
  ZZ m = rep(x);
  // ZZ_p ysqare = power(P.x, to_ZZ(3));
  // ysqare += (this->e1.a) * (P.x);
  // ysqare += this->e1.b;
  // if (chkResidue(ysqare))
  // {
  //   point y = getYCoordinate(ysqare); // it holds both the y coordinates corresponding to x of P.
  //   if (!(y.x == P.y || y.y == P.y))
  //   {
  //     cout << "!(y.x == P.y || y.y == P.y)" << endl;
  //     return P;
  //   }
  // }
  point Q(to_ZZ_p(0), to_ZZ_p(1));
  unsigned long long totbits = NumBits(m);
  while (totbits > 0)
  {
    ZZ no = 1 & (m >> (totbits - 1));
    totbits--;
    if (no == 1)
    {
      // Double and Add
      cout << "Double and add" << endl;
      Q = pointAddDouble(Q, Q);
      cout << "Result is X:" << Q.x << " Y:" << Q.y << endl;
      Q = pointAddDouble(P, Q);
      cout << "Result is X:" << Q.x << " Y:" << Q.y << endl;
    }
    else
    {
      cout << "Double" << endl;
      Q = pointAddDouble(Q, Q); // Double and skip
      cout << "Result is X:" << Q.x << " Y:" << Q.y << endl;
    }
  }
  cout << "Final result is: (" << Q.x << "," << Q.y << ")\n";
  return Q;
}

// elCurve_signature elCurve::elCurveDigiSign(const ZZ_p &secret, const ZZ_p &msg)
// {
//   elCurve_signature esign;
//   ZZ_p y = random_ZZ_p();
//   point tmp = this->scalarMult(y, this->generator);
//   esign.r = ;
// }

// bool elCurve::elCurveVerifySign(const elCurve_signature &digisign, const ZZ_p &msg)
// {
// }