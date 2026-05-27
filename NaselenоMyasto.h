#ifndef NASELENO_MYASTO_H   
#define NASELENO_MYASTO_H   

#include <iostream>    
#include <string>      
using namespace std;   

class NaselenоMyasto {

protected:                                  
    string ime;                            
    int    naselenie;                      
    double byudzhet;                          
    int    procentVazrastni;                  
    double razstoqnieDoGrad;                  
    string naiBlizakGrad;                     
    int    broiLiniiBus;                   

public:                                     

    NaselenоMyasto(string ime, int naselenie, double byudzhet,
               int procentVazrastni, double razstoqnieDoGrad,
               string naiBlizakGrad, int broiLiniiBus);

    string vzemIme()           const;   
    int    vzemNaselenie()     const;   
    double vzemByudzhet()         const;   
    int    vzemProcentVazrastni() const;   
    double vzemRazstoqnie() const;   
    string vzemNaiBlizakGrad()    const;   
    int    vzemBroiLiniiBus()  const;   

    bool eRiskovaZona()       const;  
    int  preporachaniLinii() const;  
    bool nuzhdaeSePoveche()  const;  
    void otchetMobilnost() const;  

    virtual void   pokazhiInfo()  const;   
    virtual string vzemTip()      const;   
    virtual string kamFailString() const;   

    virtual ~NaselenоMyasto() {}   
};

#endif
