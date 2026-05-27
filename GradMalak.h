#ifndef GRAD_MALAK_H    
#define GRAD_MALAK_H

#include "NaselenоMyasto.h"

class GradMalak : public NaselenоMyasto {

private:
    bool imaObshtina;
    bool imaBolnica;

public:
    GradMalak(string ime, int naselenie, double byudzhet,
         int procentVazrastni, double razstoqnieDoGrad,
         string naiBlizakGrad, int broiLiniiBus,
         bool imaObshtina, bool imaBolnica);

    bool imaObshtinaMetod() const;
    bool imaBolnicaMetod()     const;

    void   pokazhiInfo()  const override;
    string vzemTip()      const override;
    string kamFailString() const override;
};

#endif
