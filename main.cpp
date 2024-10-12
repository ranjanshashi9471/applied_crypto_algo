// g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
#include "crypto_main.hpp"

int main()
{
        // ZZ p = conv<ZZ>("1009)");
        // ZZ_p::init(p);
        // ZZ_p g = conv<ZZ_p>("999");
        // ZZ x = conv<ZZ>("500");
        // ZZ_p h = power(g, x);

        // bruteattack_dlp(p, g, h);

        // // diffiehell
        // p = conv<ZZ>("137");
        // ZZ_p::init(p);

        // dl_person alice(conv<ZZ_p>("15"));
        // dl_person bob(conv<ZZ_p>("125"));

        // ZZ_p A = alice.set_publickey(conv<ZZ_p>("3"));
        // ZZ_p B = bob.set_publickey(conv<ZZ_p>("3"));

        // alice.set_comshared(B);
        // bob.set_comshared(A);

        // bruteattack_dlp(p, conv<ZZ_p>("3"), A);
        // bruteattack_dlp(p, conv<ZZ_p>("3"), B);

        // // Elgamal
        // p = conv<ZZ>("467");
        // ZZ_p::init(p);
        // ZZ_p secKey = conv<ZZ_p>("5");
        // g = conv<ZZ_p>("2");
        // ZZ msg = conv<ZZ>("9");

        // el_gamal e1(p, g);
        // e1.set_pubKey(secKey);
        // cipherText c = e1.encrypt(msg);
        // msg = e1.decrypt(secKey, c);

        // el_gamal e2(p, g);
        // secKey = conv<ZZ_p>("127");
        // msg = conv<ZZ>("100");

        // e2.set_pubKey(secKey);
        // signature s = e2.digitalSign(msg, secKey);
        // bool b = e2.verify_digitalSign(s, msg);

        // Elliptic Curve
        ZZ p = conv<ZZ>("11");
        ZZ_p::init(p);
        elCurve ec1(p, to_ZZ_p(1), to_ZZ_p(6));
        // vector<point> points;
        // ec1.getAllPoints(points);
        // for (int i = 0; i < points.size(); i++)
        // {
        //         cout << "(" << points[i].x << ", " << points[i].y << ")\n";
        // }

        point P(to_ZZ_p(2), to_ZZ_p(7)), Q(to_ZZ_p(2), to_ZZ_p(4));
        point R = ec1.pointAddDouble(P, Q);
        R = ec1.scalarMult(4, P);
        return 0;
}