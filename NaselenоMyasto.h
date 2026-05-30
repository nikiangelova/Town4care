#ifndef NASELENO_MYASTO_H   
#define NASELENO_MYASTO_H   

#include <iostream>    
#include <string>      
#define NOMINMAX
#include <windows.h>
using namespace std;   

class NaselenoMyasto {

protected:                          
    string ime;                    
    int naselenie;              
    double byudzhet;                  
    int procentVuzrastni;          
    double razstoqnieDoGrad;          
    string naiBlizukGrad;             
    int broiLiniiBus;           

public:                             

    NaselenoMyasto(string ime, int naselenie, double byudzhet,
               int procentVuzrastni, double razstoqnieDoGrad,
               string naiBlizukGrad, int broiLiniiBus);

    string getIme() const;   
    int getNaselenie() const;   
    double getByudzhet() const;   
    int getProcentVuzrastni() const;   
    double getRazstoqnie() const;   
    string getNaiBlizukGrad() const;   
    int getBroiLiniiBus() const;   

    bool eRiskovaZona() const;  
    int preporuchaniLinii() const;  
    bool nuzhdaeSePoveche() const;  
    void otchetMobilnost() const;  

    virtual void pokazhiInfo() const;   
    virtual string getTip() const;   
    virtual string kumFailString() const;   

    virtual ~NaselenoMyasto() {}   
};

#endif   
