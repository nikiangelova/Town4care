#include <iostream>      
#include <iomanip>       // za setw 
#include "NaselenоMyasto.h"  // vklyuchi zaglavniya file na clasa
using namespace std;


//  Konstruktor na NaselenоMyasto
//  Inicializira vsichki poleta chrez spisak myasto inicializatori (:)
//  Sintaksis:  pole(stoinost), pole(stoinost), ...

NaselenоMyasto::NaselenоMyasto(string ime, int naselenie, double byudzhet,
                       int procentVazrastni, double razstoqnieDoGrad,
                       string naiBlizakGrad, int broiLiniiBus)
    : ime(ime),                     // zapisva podadenoto ime v poleto ime
      naselenie(naselenie),         
      byudzhet(byudzhet),                 
      procentVazrastni(procentVazrastni), // zapisva % vazrastni
      razstoqnieDoGrad(razstoqnieDoGrad), // zapisva razstoqnieto
      naiBlizakGrad(naiBlizakGrad),       // zapisva nai-blizkiq grad
      broiLiniiBus(broiLiniiBus)    // zapisva broi avtobusni linii
{}  // tyaloto na konstruktora e prazno - vsichko e v spisuka

// -------------------------------------------------------
//  Getters — prosto vrashtat stoinostite na poleta
// -------------------------------------------------------
string NaselenоMyasto::vzemIme()           const { return ime; }
int    NaselenоMyasto::vzemNaselenie()     const { return naselenie; }
double NaselenоMyasto::vzemByudzhet()         const { return byudzhet; }
int    NaselenоMyasto::vzemProcentVazrastni() const { return procentVazrastni; }
double NaselenоMyasto::vzemRazstoqnie() const { return razstoqnieDoGrad; }
string NaselenоMyasto::vzemNaiBlizakGrad()    const { return naiBlizakGrad; }
int    NaselenоMyasto::vzemBroiLiniiBus()  const { return broiLiniiBus; }


//  Riskova zona — vyarno ako poveche ot 40% sa vazrastni (>65g.)
//  Takiva mesta imat po-visoka nuzda ot obshtestven transport.

bool NaselenоMyasto::eRiskovaZona() const {
    return procentVazrastni > 40;   // > 40% -> riskova zona
}


//  Preporachitelen broi avtobusni linii
//  Logika:
//    - Bazovo: 1 liniya za vsyako myasto
//    - +1 ako e riskova zona (mnogo vuzrastni)
//    - +1 ako e otdalecheno (> 30 km)
//    - +1 ako e mnogo otdalecheno (> 60 km) — vtora dobavka

int NaselenоMyasto::preporachaniLinii() const {
    int preporachani = 1;                    // minimum 1 liniya

    if (eRiskovaZona())       preporachani += 1;   // mnogo vazrastni -> +1
    if (razstoqnieDoGrad > 30.0) preporachani += 1;   // dalech -> +1
    if (razstoqnieDoGrad > 60.0) preporachani += 1;   // mnogo dalech -> oshte +1

    return preporachani;   // vrasha obshtiya preporachan broi
}


//  Nuzhdae se ot poveche transport?
//  Sravnqva tekushtite linii myasto preporachanite.

bool NaselenоMyasto::nuzhdaeSePoveche() const {
    return broiLiniiBus < preporachaniLinii();   // istina ako ima nedostig
}


//  Detailen otchet za mobilnostta
//  Pechat status i finansova preporucka za konkretnoto myasto.

void NaselenоMyasto::otchetMobilnost() const {
    int preporachani = preporachaniLinii();       // preporachan broi linii
    int nedostig     = preporachani - broiLiniiBus; // kolko linii lipsvat

    cout << "\n  --- OTCHET: " << ime << " ---" << endl;

    // pokazva % vazrastni i dali e riskova zona
    cout << "  Vazrastni: " << procentVazrastni << "%";
    if (eRiskovaZona())
        cout << "  (!!! RISKOVA ZONA)" << endl;
    else
        cout << "  (v norma)" << endl;

    // pokazva razstoqnieto i nivoto na nuzda
    cout << "  Do " << naiBlizakGrad << ": " << razstoqnieDoGrad << " km" << endl;
    if (razstoqnieDoGrad > 60)
        cout << "  >> Mnogo otdalechen — kriticna nuzda" << endl;
    else if (razstoqnieDoGrad > 30)
        cout << "  >> Otdalechen — povishena nuzda" << endl;
    else
        cout << "  >> Blizo — bazova nuzda" << endl;

    // sravnqva tekushti i preporachani linii
    cout << "  Tekushti linii   : " << broiLiniiBus << endl;
    cout << "  Preporachitelni  : " << preporachani << endl;

    // finalen statys i preporacka za finansirane
    if (nuzhdaeSePoveche()) {
        cout << "  STATUS: NEOBHODIMO FINANSIRANE" << endl;
        cout << "  Deficit: " << nedostig << " linii" << endl;

        // priblizitelna cena: 15 000 lv. na linia na godina
        double nuzhdaFinans = nedostig * 15000.0;
        cout << "  Preporachano finansirane: " << nuzhdaFinans << " lv./god." << endl;
        cout << "  >> Podaite zaqvlenie za subsidiq kam oblastnata uprava." << endl;
    } else {
        cout << "  STATUS: TRANSPORTNOTO POKRITIE E DOBRO" << endl;
        cout << "  Nyama nuzda ot dopalnitelno finansirane." << endl;
    }

    cout << "  ----------------------------" << endl;
}


//  pokazhiInfo — pokazva obshtata informaciya za naselenoto myasto
//  Izvikva se i ot Selo::pokazhiInfo() i GradMalak::pokazhiInfo()

void NaselenоMyasto::pokazhiInfo() const {
    cout << "\n  Tip         : " << vzemTip() << endl;    // vika virtualniq metod
    cout << "  Ime         : " << ime << endl;
    cout << "  Naselenie   : " << naselenie << " zhiteli" << endl;
    cout << "  Byudzhet    : " << byudzhet << " lv." << endl;
    cout << "  Vazrastni   : " << procentVazrastni << "%"
         << (eRiskovaZona() ? "  [!] RISKOVA ZONA" : "") << endl;
    cout << "  Avt. linii  : " << broiLiniiBus
         << " (preporachani: " << preporachaniLinii() << ")" << endl;
    cout << "  Nai-blizak  : " << naiBlizakGrad << " — " << razstoqnieDoGrad << " km" << endl;

    // preduprezhdenie ako ima nuzda ot poveche transport
    if (nuzhdaeSePoveche())
        cout << "  !! NUZDA OT FINANSIRANE ZA TRANSPORT!" << endl;
}

// bazovite versii na vzemTip i kamFailString — zamestvat se v naslednicite
string NaselenоMyasto::vzemTip() const { return "Naseleno myasto"; }

// formatira dannite kato tekst razdelen myasto | za zapis v tekstov fail
string NaselenоMyasto::kamFailString() const {
    return "BASE|" + ime + "|" +
           to_string(naselenie)     + "|" +   // to_string: chislo -> tekst
           to_string(byudzhet)         + "|" +
           to_string(procentVazrastni) + "|" +
           to_string(razstoqnieDoGrad) + "|" +
           naiBlizakGrad               + "|" +
           to_string(broiLiniiBus);
}
