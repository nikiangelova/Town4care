#include <iostream>
#include "GradMalak.h"
using namespace std;

GradMalak::GradMalak(string ime, int naselenie, double byudzhet,
           int procentVazrastni, double razstoqnieDoGrad,
           string naiBlizakGrad, int broiLiniiBus,
           bool imaObshtina, bool imaBolnica)
    : NaselenоMyasto(ime, naselenie, byudzhet, procentVazrastni,
                 razstoqnieDoGrad, naiBlizakGrad, broiLiniiBus),
      imaObshtina(imaObshtina),
      imaBolnica(imaBolnica)
{}

bool GradMalak::imaObshtinaMetod() const { return imaObshtina; }
bool GradMalak::imaBolnicaMetod()     const { return imaBolnica; }

void GradMalak::pokazhiInfo() const {
    NaselenоMyasto::pokazhiInfo();

    cout << "  --- MALAK GRAD specificno ---" << endl;
    cout << "  Obshtinska uprava: " << (imaObshtina ? "Da" : "Ne") << endl;
    cout << "  Bolnica          : " << (imaBolnica     ? "Da" : "Ne") << endl;
}

string GradMalak::vzemTip() const { return "Malak grad"; }

string GradMalak::kamFailString() const {
    return "TOWN|"                                 +
           vzemIme()                               + "|" +
           to_string(vzemNaselenie())      + "|" +
           to_string(vzemByudzhet())          + "|" +
           to_string(vzemProcentVazrastni())  + "|" +
           to_string(vzemRazstoqnie())  + "|" +
           vzemNaiBlizakGrad()                 + "|" +
           to_string(vzemBroiLiniiBus())   + "|" +
           to_string(imaObshtina)      + "|" +
           to_string(imaBolnica);
}
