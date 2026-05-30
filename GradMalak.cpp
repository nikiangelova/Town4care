#include <iostream>
#include "GradMaluk.h"
#define NOMINMAX
#include <windows.h>
using namespace std;

GradMaluk::GradMaluk(string ime, int naselenie, double byudzhet,
           int procentVuzrastni, double razstoqnieDoGrad,
           string naiBlizukGrad, int broiLiniiBus,
           bool imaObshtina, bool imaBolnica)
: NaselenoMyasto(ime, naselenie, byudzhet, procentVuzrastni,
                 razstoqnieDoGrad, naiBlizukGrad, broiLiniiBus),  
      imaObshtina(imaObshtina),   
      imaBolnica(imaBolnica)            
{}

bool GradMaluk::imaObshtinaMetod() const { return imaObshtina; }
bool GradMaluk::imaBolnicaMetod() const { return imaBolnica; }

void GradMaluk::pokazhiInfo() const {
    NaselenoMyasto::pokazhiInfo();   

    cout << "  --- Малък град (специфично) ---" << endl;
    cout << "  Общинска управа: " << (imaObshtina ? "Да": "Не") << endl;
    cout << "  Болница: " << (imaBolnica ? "Да": "Не") << endl;
}

string GradMaluk::getTip() const { return "Малък град"; }

string GradMaluk::kumFailString() const {
    return "Малък град|" +
           getIme() + "|" +
           to_string(getNaselenie()) + "|" +
           to_string(getByudzhet()) + "|" +
           to_string(getProcentVuzrastni()) + "|" +
           to_string(getRazstoqnie()) + "|" +
           getNaiBlizukGrad() + "|" +
           to_string(getBroiLiniiBus()) + "|" +
           to_string(imaObshtina) + "|" +   
           to_string(imaBolnica);
}
