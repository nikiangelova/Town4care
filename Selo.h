#ifndef SELO_H    
#define SELO_H

#include "NaselenoMyasto.h"   
#define NOMINMAX
#include <windows.h>

class Selo: public NaselenoMyasto {   

private:                    
    bool imaZemedelie;        
    bool imaUchilishte;         

public:
    
    Selo(string ime, int naselenie, double byudzhet,
         int procentVuzrastni, double razstoqnieDoGrad,
         string naiBlizukGrad, int broiLiniiBus,
         bool imaZemedelie, bool imaUchilishte);

    bool ImaZemedelskaDeinost() const;   
    bool imaUchilishteMetod() const;   

    void pokazhiInfo() const override;   
    string getTip() const override;   
    string kumFailString() const override;   
};

#endif
