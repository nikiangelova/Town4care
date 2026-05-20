#include <iostream>
#include "Selo.h"   // vklyuchi zaglavniya fail na Selo
using namespace std;

// -------------------------------------------------------
//  Konstruktor na Selo
//  Parvo izvikva konstruktora na NaselenоMyasto (bazoviq klas)
//  chrez : NaselenоMyasto(...), sled koeto inicializira
//  specifichnite poleta imaZemedelie i imaUchilishte.
// -------------------------------------------------------
Selo::Selo(string ime, int naselenie, double byudzhet,
                 int procentVazrastni, double razstoqnieDoGrad,
                 string naiBlizakGrad, int broiLiniiBus,
                 bool imaZemedelie, bool imaUchilishte)
    : NaselenоMyasto(ime, naselenie, byudzhet, procentVazrastni,
                 razstoqnieDoGrad, naiBlizakGrad, broiLiniiBus),  // izvikva bazoviq konstruktor
      imaZemedelie(imaZemedelie),    // inicializira poleto za zemedelie
      imaUchilishte(imaUchilishte)       // inicializira poleto za uchilishte
{}

// Getters — prosto vrashtat stoinostite na chastnite poleta
bool Selo::imaZemedelskaDeinos() const { return imaZemedelie; }
bool Selo::imaUchilishteMetod()  const { return imaUchilishte; }

// -------------------------------------------------------
//  pokazhiInfo — pokazva cyalata informaciya za seloto
//  Parvo vika NaselenоMyasto::pokazhiInfo() za obshtite danni,
//  sled koeto dobavya specifichnite za selo.
// -------------------------------------------------------
void Selo::pokazhiInfo() const {
    NaselenоMyasto::pokazhiInfo();   // izvikva metoda na bazoviq klas

    // dobavya specifichnite danni za selo
    cout << "  --- SELO specificno ---" << endl;
    cout << "  Zemedelie : " << (imaZemedelie ? "Da" : "Ne") << endl;   // ternaren operator
    cout << "  Uchilishte: " << (imaUchilishte  ? "Da" : "Ne") << endl;
}

// vrasha tipa kato tekst — izpolzva se v pokazhiInfo() na bazoviq klas
string Selo::vzemTip() const { return "Selo"; }

// -------------------------------------------------------
//  kamFailString — formatira dannite za zapis v tekstov fail
//  Format: VILLAGE|<pole>|<pole>|...
//  Vsyako pole e razdeleno myasto | za lesno chetene pri zarezhvane.
// -------------------------------------------------------
string Selo::kamFailString() const {
    return "VILLAGE|"                      +
           vzemIme()                       + "|" +
           to_string(vzemNaselenie())      + "|" +   // int -> string
           to_string(vzemByudzhet())          + "|" +   // double -> string
           to_string(vzemProcentVazrastni())  + "|" +
           to_string(vzemRazstoqnie())  + "|" +
           vzemNaiBlizakGrad()                + "|" +
           to_string(vzemBroiLiniiBus())   + "|" +
           to_string(imaZemedelie)           + "|" +   // bool -> "0" ili "1"
           to_string(imaUchilishte);
}
