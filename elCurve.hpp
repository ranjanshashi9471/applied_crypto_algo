#include "appl_crypto.hpp"

typedef struct point
{
  ZZ_p x;
  ZZ_p y;
  point() : x(0), y(1) {}
  point(ZZ_p x, ZZ_p y) : x(x), y(y) {}
} point;

typedef struct encryptedText
{
  point c1;
  point c2;
} encryptedText;

typedef struct ellipt_curve
{
  ZZ_p a;
  ZZ_p b;
  ellipt_curve() : a(0), b(1) {}
  ellipt_curve(ZZ_p a, ZZ_p b) : a(a), b(b) {}
} ellipt_curve;

class elCurve
{
private:
  bool chkResidue(const ZZ_p &a);
  bool isInfinity(const point &P);
  point getY(const ZZ_p &ySquare);

public:
  ZZ p;
  ellipt_curve e1;
  point generator;
  elCurve(const ZZ &p, const ellipt_curve &parameters, const point &generator);
  point genPublicKey(const ZZ &secret);
  point pointAddDouble(const point &P, const point &Q);
  point scalarMult(const ZZ &m, const point &P);
  point pointNegation(const point &P);
  encryptedText elCurveEncrypt(const point &msg, const point &Q);
  point elCurveDecrypt(const encryptedText &e1, const ZZ &secret);
};
