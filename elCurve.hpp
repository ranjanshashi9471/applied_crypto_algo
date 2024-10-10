#include "appl_crypto.hpp"

typedef struct point
{
    ZZ_p x;
    ZZ_p y;
} point;

class elCurve
{
private:
    bool chkResidue(ZZ_p a);

public:
    ZZ p;
    ZZ_p a, b;
    elCurve(ZZ p, ZZ_p a, ZZ_p b);
    void getPoint(ZZ_p x, ZZ_p ySquare, vector<point> &points);
    void getAllPoints(vector<point> &points);
};