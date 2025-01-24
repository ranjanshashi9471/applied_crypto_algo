#include "appl_crypto.hpp"

typedef struct point
{
  ZZ_p x;
  ZZ_p y;
  point() : x(0), y(1) {}
  point(ZZ_p x, ZZ_p y) : x(x), y(y) {}
} point;

// typedef struct compressedPoint
// {
//   ZZ_p x;
//   bool y;
//   compressedPoint() : x(0), y(1) {}
//   compressedPoint(ZZ_p x, bool y) : x(x), y(y) {}
// } compressedPoint;

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

typedef struct elCurve_signature
{
  ZZ_p r;
  ZZ_p s;
} elCurve_signature;

class elCurve
{
private:
  ZZ p;
  point generator;
  ellipt_curve e1;
  bool chkValidPoint(const point &pt);
  ZZ_p getYsq(const ZZ_p &x);
  bool chkResidue(const ZZ_p &a);
  bool isInfinity(const point &P);
  point getYCoordinate(const ZZ_p &x);
  point getRandomPoint();

public:
  elCurve(const ZZ &p);
  ZZ_p generateAllPoints();
  void setGenerator(const point &P);
  ellipt_curve getNonSingCurParams();
  point genPublicKey(const ZZ_p &secret);
  bool chkSingularity(const ellipt_curve &parameters);
  point pointAddDouble(const point &P, const point &Q);
  point scalarMult(const ZZ_p &m, const point &P);
  point pointNegation(const point &P);
  encryptedText elCurveEncrypt(const point &msg, const point &Q);
  point elCurveDecrypt(const encryptedText &e1, const ZZ_p &secret);
  elCurve_signature elCurveDigiSign(const ZZ_p &secret, const ZZ_p &msg);
  bool elCurveVerifySign(const elCurve_signature &digisign, const ZZ_p &msg);
};