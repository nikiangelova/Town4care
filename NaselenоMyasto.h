#ifndef NASELENO_MYASTO_H   // ako NaselenоMyasto.h ne e vklyuchen predi, vklyuchi go
#define NASELENO_MYASTO_H   // markiay, che veche e vklyuchen (pazi ot dvoino vklyuchvane)

#include <iostream>    // za cout (pechatane na ekrana)
#include <string>      // za tipa string (tekst)
using namespace std;   // za da pishem string vmesto std::string navsakade

// -------------------------------------------------------
//  Bazov klas NaselenоMyasto (Naseleno myasto)
//  Vsichki naseleni mesta spodelqt tezi danni i metodi.
//  Selo i GradMalak nasledqvat ot nego.
// -------------------------------------------------------
class NaselenоMyasto {

protected:                          // protected = dostapno v naslednicite (Selo, GradMalak)
    string ime;                    // ime na naselenoto myasto
    int    naselenie;              // broi zhiteli
    double byudzhet;                  // godishen byudzhet v leva
    int    procentVazrastni;          // procent zhiteli nad 65 godini
    double razstoqnieDoGrad;          // razstoqnie do nai-blizkiq golyam grad (km)
    string naiBlizakGrad;             // ime na nai-blizkiq golyam grad
    int    broiLiniiBus;           // tekusht broi avtobusni linii

public:                             // public = dostapno otvsqkade

    // Konstruktor: izvikva se pri sazdavane na obekt
    NaselenоMyasto(string ime, int naselenie, double byudzhet,
               int procentVazrastni, double razstoqnieDoGrad,
               string naiBlizakGrad, int broiLiniiBus);

    // Getters: vrashtat stoinostite na polyata
    string vzemIme()           const;   // vrasha imeto
    int    vzemNaselenie()     const;   // vrasha broa zhiteli
    double vzemByudzhet()         const;   // vrasha byudzheta
    int    vzemProcentVazrastni() const;   // vrasha % vazrastni
    double vzemRazstoqnie() const;   // vrasha razstoqnieto
    string vzemNaiBlizakGrad()    const;   // vrasha imeto na blizkiq grad
    int    vzemBroiLiniiBus()  const;   // vrasha broa avtobusni linii

    // Osnovna logika: analiz na transportnata nuzda
    bool eRiskovaZona()       const;  // vyarno ako > 40% sa vazrastni
    int  preporachaniLinii() const;  // izchislqva preporachaniya broi linii
    bool nuzhdaeSePoveche()  const;  // vyarno ako ima nuzda ot poveche transport
    void otchetMobilnost() const;  // pechat palen otchet myasto preporacka

    // Virtualni metodi: zamestvat se v naslednicite
    virtual void   pokazhiInfo()  const;   // pokazva informaciq za myastoto
    virtual string vzemTip()      const;   // vrasha tipa ("Selo", "Malak grad")
    virtual string kamFailString() const;   // formatira dannite za zapis vav fail

    virtual ~NaselenоMyasto() {}   // virtualen destruktor (vazhen pri nasledqvane myasto ukazateli)
};

#endif   // krai na zashtitata ot dvoino vklyuchvane
