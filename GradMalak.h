#ifndef GRAD_MALAK_H    
#define GRAD_MALAK_H

#include "NaselenоMyasto.h"   // GradMalak nasledqva NaselenоMyasto


//  Klas GradMalak (Malak grad)
//  Nasledqva NaselenоMyasto i dobavya 2 specifichni poleta:
//    - imaObshtina : dali ima obshtinska uprava
//    - imaBolnica     : dali ima bolnica ili zdraven dom

class GradMalak : public NaselenоMyasto {   // "public NaselenоMyasto" = GradMalak e vid NaselenоMyasto

private:
    bool imaObshtina;   // true = ima obshtinska uprava
    bool imaBolnica;       // true = ima bolnica / zdraven dom

public:
    // Konstruktor: vsichki danni na NaselenоMyasto + specifichnite za malak grad
    GradMalak(string ime, int naselenie, double byudzhet,
         int procentVazrastni, double razstoqnieDoGrad,
         string naiBlizakGrad, int broiLiniiBus,
         bool imaObshtina, bool imaBolnica);

    bool imaObshtinaMetod() const;   // vrasha imaObshtina
    bool imaBolnicaMetod()     const;   // vrasha imaBolnica

    // override = zamestya metoda na NaselenоMyasto
    void   pokazhiInfo()  const override;
    string vzemTip()      const override;   // vrasha "Malak grad"
    string kamFailString() const override;   // formatira myasto tip "TOWN"
};

#endif
