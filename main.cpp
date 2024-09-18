// g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
#include "appl_crypto.hpp"

using namespace std;
using namespace NTL;

int main()
{
        dlp d1 = dlp(conv<ZZ>("1009"));
        d1.setparameters(conv<ZZ_p>("999"), conv<ZZ>("500"));
        d1.solve_dlp();

        diffie_hellman d2(conv<ZZ>("1009"), conv<ZZ_p>("999"));
        d2.eve();

        el_gamal e1(conv<ZZ>("467"));

        return 0;
}