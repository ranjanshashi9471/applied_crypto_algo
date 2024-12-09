// g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
#include "crypto_main.hpp"

int main()
{
  ZZ p = conv<ZZ>("1009)");
  // ZZ_p::init(p);
  // ZZ_p g = conv<ZZ_p>("999");
  // ZZ x = conv<ZZ>("500");
  // ZZ_p h = power(g, x);

  // bruteattack_dlp(p, g, h);

  // diffiehell
  // p = conv<ZZ>("103");
  // ZZ_p::init(p);

  // dl_person alice(conv<ZZ_p>("13"));
  // dl_person bob(conv<ZZ_p>("91"));

  // ZZ_p A = alice.set_publickey(conv<ZZ_p>("5"));
  // cout << "Public key of alice is :" << A << endl;
  // ZZ_p B = bob.set_publickey(conv<ZZ_p>("5"));
  // cout << "Public key of bob is :" << B << endl;
  // alice.set_comshared(B);
  // bob.set_comshared(A);

  // bruteattack_dlp(p, conv<ZZ_p>("3"), A);
  // bruteattack_dlp(p, conv<ZZ_p>("3"), B);

  // // Elgamal
  // p = conv<ZZ>("73");
  // ZZ_p::init(p);
  // ZZ_p secKey = conv<ZZ_p>("36");
  // ZZ_p g = conv<ZZ_p>("5");
  // ZZ msg = conv<ZZ>("54");

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
  // p = conv<ZZ>("29");
  // ZZ_p::init(p);

  // elCurve ec1(p);
  // point P(to_ZZ_p(7), to_ZZ_p(2));
  // ec1.scalarMult(to_ZZ_p(3), P);
  // ZZ_p R;
  // ZZ_p secret = to_ZZ_p(10); // random_ZZ_p();
  // point Q(to_ZZ_p(7), to_ZZ_p(2));
  // point Q = ec1.genPublicKey(secret);
  // ZZ_p msg = to_ZZ_p(4);
  // point msg(to_ZZ_p(3), to_ZZ_p(7));
  // cout << "random generated msg:" << msg << endl;
  // encryptedText enctxt1 = ec1.elCurveEncrypt(msg, Q);
  // ZZ_p R = ec1.elCurveDecrypt(enctxt1, secret);
  // cout << "Decrypteed msg:" << R << endl;
  // ec1.setPublicKey(secret);
  // elCurve_signature esign = ec1.elCurveDigiSign(secret, msg);
  // ec1.elCurveVerifySign(esign, msg);

  //  RSA Encryption - Decryption
  RSA r1;
  ZZ P = GenPrime_ZZ(512);
  ZZ Q = GenPrime_ZZ(512);
  ZZ n = P * Q;
  ZZ phi = (P - 1) * (Q - 1);
  ZZ_p A = r1.generateA(phi);
  cout << "A is " << A << endl;
  ZZ_p B = inv(A);

  return 0;
}
