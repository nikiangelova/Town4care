#ifndef GRAD_MALUK_H    
#define GRAD_MALUK_H

#include "NaselenoMyasto.h"   

#define NOMINMAX
#include <windows.h>

class GradMaluk: public NaselenoMyasto {   

private:
    bool imaObshtina;   
    bool imaBolnica;       

public:
    
    GradMaluk(string ime, int naselenie, double byudzhet,
         int procentVuzrastni, double razstoqnieDoGrad,
         string naiBlizukGrad, int broiLiniiBus,
         bool imaObshtina, bool imaBolnica);

    bool imaObshtinaMetod() const;   
    bool imaBolnicaMetod() const;   

    void pokazhiInfo() const override;
    string getTip() const override;   
    string kumFailString() const override;   
};

#endif
