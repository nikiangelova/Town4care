#ifndef SELO_H    
#define SELO_H

#include "NaselenоMyasto.h" 

class Selo : public NaselenоMyasto {  

private:                   
    bool imaZemedelie;        
    bool imaUchilishte;        

public:
    Selo(string ime, int naselenie, double byudzhet,
            int procentVazrastni, double razstoqnieDoGrad,
            string naiBlizakGrad, int broiLiniiBus,
            bool imaZemedelie, bool imaUchilishte);

    bool imaZemedelskaDeinos() const;  
    bool imaUchilishteMetod()  const; 

    void   pokazhiInfo()  const override; 
    string vzemTip()      const override;   
    string kamFailString() const override;  
};

#endif
