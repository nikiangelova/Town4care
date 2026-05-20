#include <iostream>
#include "GradMalak.h"
using namespace std;

// -------------------------------------------------------
//  Konstruktor na GradMalak
//  Izvikva konstruktora na NaselenоMyasto za obshtite danni,
//  sled koeto inicializira specifichnite poleta.
// -------------------------------------------------------
GradMalak::GradMalak(string ime, int naselenie, double byudzhet,
           int procentVazrastni, double razstoqnieDoGrad,
           string naiBlizakGrad, int broiLiniiBus,
           bool imaObshtina, bool imaBolnica)
    : NaselenоMyasto(ime, naselenie, byudzhet, procentVazrastni,
                 razstoqnieDoGrad, naiBlizakGrad, broiLiniiBus),  // bazov konstruktor
      imaObshtina(imaObshtina),   // inicializira obshtinska uprava
      imaBolnica(imaBolnica)            // inicializira bolnica
{}

// Getters
bool GradMalak::imaObshtinaMetod() const { return imaObshtina; }
bool GradMalak::imaBolnicaMetod()     const { return imaBolnica; }

// -------------------------------------------------------
//  pokazhiInfo — pokazva obshtoto + specifichnoto za malak grad
// -------------------------------------------------------
void GradMalak::pokazhiInfo() const {
    NaselenоMyasto::pokazhiInfo();   // obshtata informaciq ot bazoviq klas

    // specificno za malak grad
    cout << "  --- MALAK GRAD specificno ---" << endl;
    cout << "  Obshtinska uprava: " << (imaObshtina ? "Da" : "Ne") << endl;
    cout << "  Bolnica          : " << (imaBolnica     ? "Da" : "Ne") << endl;
}

// vrasha tipa kato tekst
string GradMalak::vzemTip() const { return "Malak grad"; }

// -------------------------------------------------------
//  kamFailString — formatira za fail myasto tip "TOWN"
// -------------------------------------------------------
string GradMalak::kamFailString() const {
    return "TOWN|"                         +
           vzemIme()                       + "|" +
           to_string(vzemNaselenie())      + "|" +
           to_string(vzemByudzhet())          + "|" +
           to_string(vzemProcentVazrastni())  + "|" +
           to_string(vzemRazstoqnie())  + "|" +
           vzemNaiBlizakGrad()                + "|" +
           to_string(vzemBroiLiniiBus())   + "|" +
           to_string(imaObshtina)      + "|" +   // bool -> "0" ili "1"
           to_string(imaBolnica);
}
