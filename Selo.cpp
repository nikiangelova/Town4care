#include <iostream>
#include "Selo.h"
using namespace std;

Selo::Selo(string ime, int naselenie, double byudzhet,
                 int procentVazrastni, double razstoqnieDoGrad,
                 string naiBlizakGrad, int broiLiniiBus,
                 bool imaZemedelie, bool imaUchilishte)
    : NaselenоMyasto(ime, naselenie, byudzhet, procentVazrastni,
                 razstoqnieDoGrad, naiBlizakGrad, broiLiniiBus),
      imaZemedelie(imaZemedelie),
      imaUchilishte(imaUchilishte)
{}

bool Selo::imaZemedelskaDeinos() const { return imaZemedelie; }
bool Selo::imaUchilishteMetod()  const { return imaUchilishte; }

void Selo::pokazhiInfo() const {
    NaselenоMyasto::pokazhiInfo();

    cout << "  --- SELO specificno ---" << endl;
    cout << "  Zemedelie : " << (imaZemedelie ? "Da" : "Ne") << endl;
    cout << "  Uchilishte: " << (imaUchilishte  ? "Da" : "Ne") << endl;
}

string Selo::vzemTip() const { return "Selo"; }

string Selo::kamFailString() const {
    return "VILLAGE|"                      +
           vzemIme()                       + "|" +
           to_string(vzemNaselenie())      + "|" +
           to_string(vzemByudzhet())          + "|" +
           to_string(vzemProcentVazrastni())  + "|" +
           to_string(vzemRazstoqnie())  + "|" +
           vzemNaiBlizakGrad()                + "|" +
           to_string(vzemBroiLiniiBus())   + "|" +
           to_string(imaZemedelie)            + "|" +
           to_string(imaUchilishte);
}
