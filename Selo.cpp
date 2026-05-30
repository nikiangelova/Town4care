#include <iostream>
#include "Selo.h"   
#define NOMINMAX
#include <windows.h>
using namespace std;

Selo::Selo(string ime, int naselenie, double byudzhet,
           int procentVuzrastni, double razstoqnieDoGrad,
           string naiBlizukGrad, int broiLiniiBus,
           bool imaZemedelie, bool imaUchilishte)
: NaselenoMyasto(ime, naselenie, byudzhet, procentVuzrastni,
                 razstoqnieDoGrad, naiBlizukGrad, broiLiniiBus),  
      imaZemedelie(imaZemedelie),    
      imaUchilishte(imaUchilishte)       
{}

bool Selo::ImaZemedelskaDeinost() const { return imaZemedelie; }
bool Selo::imaUchilishteMetod() const { return imaUchilishte; }

void Selo::pokazhiInfo() const {
    NaselenoMyasto::pokazhiInfo();   

    cout << "  --- Село(специфично) ---" << endl;
    cout << " Земеделие: " << (imaZemedelie ? "Да": "Не") << endl;   
    cout << " Училище: " << (imaUchilishte  ? "Да": "Не") << endl;
}

string Selo::getTip() const { return "Село"; }

string Selo::kumFailString() const {
    return "Село|" +
           getIme() + "|" +
           to_string(getNaselenie()) + "|" +   
           to_string(getByudzhet()) + "|" +   
           to_string(getProcentVuzrastni()) + "|" +
           to_string(getRazstoqnie()) + "|" +
           getNaiBlizukGrad() + "|" +
           to_string(getBroiLiniiBus()) + "|" +
           to_string(imaZemedelie) + "|" +   
           to_string(imaUchilishte);
}
