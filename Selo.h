#ifndef SELO_H    // zashtita ot dvoino vklyuchvane
#define SELO_H

#include "NaselenоMyasto.h"   // Selo nasledqva NaselenоMyasto, zatova go vklyuchvame

// -------------------------------------------------------
//  Klas Selo (Selo)
//  Nasledqva NaselenоMyasto i dobavya 2 specifichni poleta:
//    - imaZemedelie : dali ima zemedelska deinost
//    - imaUchilishte  : dali ima uchilishte
// -------------------------------------------------------
class Selo : public NaselenоMyasto {   // "public NaselenоMyasto" = Selo e vid NaselenоMyasto

private:                    // private = dostapno samo vatre v klasa Selo
    bool imaZemedelie;        // true = ima zemedelie, false = nema
    bool imaUchilishte;         // true = ima uchilishte, false = nema

public:
    // Konstruktor: priema vsichki danni na NaselenоMyasto + specifichnite za selo
    Selo(string ime, int naselenie, double byudzhet,
            int procentVazrastni, double razstoqnieDoGrad,
            string naiBlizakGrad, int broiLiniiBus,
            bool imaZemedelie, bool imaUchilishte);

    // Getters za specifichnite poleta
    bool imaZemedelskaDeinos() const;   // vrasha stoinostta na imaZemedelie
    bool imaUchilishteMetod()  const;   // vrasha stoinostta na imaUchilishte

    // override = zamestya metoda na bazoviq klas NaselenоMyasto
    void   pokazhiInfo()  const override;   // pokazva infoto + specifichnoto za selo
    string vzemTip()      const override;   // vrasha "Selo"
    string kamFailString() const override;   // formatira za zapis myasto tip "VILLAGE"
};

#endif
