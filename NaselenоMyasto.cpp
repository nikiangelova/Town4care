#include <iostream>      
#include <iomanip>       
#include "NaselenоMyasto.h"  
using namespace std;

NaselenоMyasto::NaselenоMyasto(string ime, int naselenie, double byudzhet,
                       int procentVazrastni, double razstoqnieDoGrad,
                       string naiBlizakGrad, int broiLiniiBus)
    : ime(ime),                     
      naselenie(naselenie),         
      byudzhet(byudzhet),                 
      procentVazrastni(procentVazrastni), 
      razstoqnieDoGrad(razstoqnieDoGrad), 
      naiBlizakGrad(naiBlizakGrad),       
      broiLiniiBus(broiLiniiBus)    
{}  

string NaselenоMyasto::vzemIme()           const { return ime; }
int    NaselenоMyasto::vzemNaselenie()     const { return naselenie; }
double NaselenоMyasto::vzemByudzhet()         const { return byudzhet; }
int    NaselenоMyasto::vzemProcentVazrastni() const { return procentVazrastni; }
double NaselenоMyasto::vzemRazstoqnie() const { return razstoqnieDoGrad; }
string NaselenоMyasto::vzemNaiBlizakGrad()    const { return naiBlizakGrad; }
int    NaselenоMyasto::vzemBroiLiniiBus()  const { return broiLiniiBus; }

bool NaselenоMyasto::eRiskovaZona() const {
    return procentVazrastni > 40;   
}

int NaselenоMyasto::preporachaniLinii() const {
    int preporachani = 1;                    

    if (eRiskovaZona())       preporachani += 1;   
    if (razstoqnieDoGrad > 30.0) preporachani += 1;   
    if (razstoqnieDoGrad > 60.0) preporachani += 1;   

    return preporachani;   
}

bool NaselenоMyasto::nuzhdaeSePoveche() const {
    return broiLiniiBus < preporachaniLinii();   
}

void NaselenоMyasto::otchetMobilnost() const {
    int preporachani = preporachaniLinii();       
    int nedostig     = preporachani - broiLiniiBus; 

    cout << "\n  --- OTCHET: " << ime << " ---" << endl;

    cout << "  Vazrastni: " << procentVazrastni << "%";
    if (eRiskovaZona())
        cout << "  (!!! RISKOVA ZONA)" << endl;
    else
        cout << "  (v norma)" << endl;

    cout << "  Do " << naiBlizakGrad << ": " << razstoqnieDoGrad << " km" << endl;
    if (razstoqnieDoGrad > 60)
        cout << "  >> Mnogo otdalechen — kriticna nuzda" << endl;
    else if (razstoqnieDoGrad > 30)
        cout << "  >> Otdalechen — povishena nuzda" << endl;
    else
        cout << "  >> Blizo — bazova nuzda" << endl;

    cout << "  Tekushti linii   : " << broiLiniiBus << endl;
    cout << "  Preporachitelni  : " << preporachani << endl;

    if (nuzhdaeSePoveche()) {
        cout << "  STATUS: NEOBHODIMO FINANSIRANE" << endl;
        cout << "  Deficit: " << nedostig << " linii" << endl;

        double nuzhdaFinans = nedostig * 15000.0;
        cout << "  Preporachano finansirane: " << nuzhdaFinans << " lv./god." << endl;
        cout << "  >> Podaite zaqvlenie za subsidiq kam oblastnata uprava." << endl;
    } else {
        cout << "  STATUS: TRANSPORTNOTO POKRITIE E DOBRO" << endl;
        cout << "  Nyama nuzda ot dopalnitelno finansirane." << endl;
    }

    cout << "  ----------------------------" << endl;
}

void NaselenоMyasto::pokazhiInfo() const {
    cout << "\n  Tip          : " << vzemTip() << endl;    
    cout << "  Ime          : " << ime << endl;
    cout << "  Naselenie    : " << naselenie << " zhiteli" << endl;
    cout << "  Byudzhet     : " << byudzhet << " lv." << endl;
    cout << "  Vazrastni    : " << procentVazrastni << "%"
         << (eRiskovaZona() ? "  [!] RISKOVA ZONA" : "") << endl;
    cout << "  Avt. linii  : " << broiLiniiBus
         << " (preporachani: " << preporachaniLinii() << ")" << endl;
    cout << "  Nai-blizak  : " << naiBlizakGrad << " — " << razstoqnieDoGrad << " km" << endl;

    if (nuzhdaeSePoveche())
        cout << "  !! NUZDA OT FINANSIRANE ZA TRANSPORT!" << endl;
}

string NaselenоMyasto::vzemTip() const { return "Naseleno myasto"; }

string NaselenоMyasto::kamFailString() const {
    return "BASE|" + ime + "|" +
           to_string(naselenie)     + "|" +   
           to_string(byudzhet)         + "|" +
           to_string(procentVazrastni) + "|" +
           to_string(razstoqnieDoGrad) + "|" +
           naiBlizakGrad               + "|" +
           to_string(broiLiniiBus);
}
