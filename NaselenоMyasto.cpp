#include <iostream>      
#include <iomanip>       
#include "NaselenoMyasto.h"  
#define NOMINMAX
#include <windows.h>
using namespace std;

NaselenoMyasto::NaselenoMyasto(string ime, int naselenie, double byudzhet,
                       int procentVuzrastni, double razstoqnieDoGrad,
                       string naiBlizukGrad, int broiLiniiBus)
: ime(ime),                     
      naselenie(naselenie),         
      byudzhet(byudzhet),                 
      procentVuzrastni(procentVuzrastni), 
      razstoqnieDoGrad(razstoqnieDoGrad), 
      naiBlizukGrad(naiBlizukGrad),       
      broiLiniiBus(broiLiniiBus)    
{}  

string NaselenoMyasto::getIme() const { return ime; }
int NaselenoMyasto::getNaselenie() const { return naselenie; }
double NaselenoMyasto::getByudzhet() const { return byudzhet; }
int NaselenoMyasto::getProcentVuzrastni() const { return procentVuzrastni; }
double NaselenoMyasto::getRazstoqnie() const { return razstoqnieDoGrad; }
string NaselenoMyasto::getNaiBlizukGrad() const { return naiBlizukGrad; }
int NaselenoMyasto::getBroiLiniiBus() const { return broiLiniiBus; }

bool NaselenoMyasto::eRiskovaZona() const {
    return procentVuzrastni > 40;   
}

int NaselenoMyasto::preporuchaniLinii() const {
    int preporuchani = 1;                    

    if (eRiskovaZona()) preporuchani += 1;   
    if (razstoqnieDoGrad > 30.0) preporuchani += 1;   
    if (razstoqnieDoGrad > 60.0) preporuchani += 1;   

    return preporuchani;   
}

bool NaselenoMyasto::nuzhdaeSePoveche() const {
    return broiLiniiBus < preporuchaniLinii();   
}

void NaselenoMyasto::otchetMobilnost() const {
    int preporuchani = preporuchaniLinii();       
    int nedostig     = preporuchani - broiLiniiBus; 

    cout << "\n Отчет: " << ime << endl;

    cout << " Възрастни: " << procentVuzrastni << "%";
    if (eRiskovaZona())
        cout << "  (!!! Рискова зона)" << endl;
    else
        cout << "  (в норма)" << endl;

    cout << "  ДО " << naiBlizukGrad << ": " << razstoqnieDoGrad << " km" << endl;
    if (razstoqnieDoGrad > 60)
        cout << "  >> Много отдалечен - в критична нужда" << endl;
    else if (razstoqnieDoGrad > 30)
        cout << "  >> Отдалечен - повишена нужда" << endl;
    else
        cout << "  >> Близо до голям град - транспортът е достатъчен" << endl;

    cout << "  Текущи линии: " << broiLiniiBus << endl;
    cout << "  Препоръчителни: " << preporuchani << endl;

    if (nuzhdaeSePoveche()) {
        cout << "  Статус: Необходимо финансиране!!!" << endl;
        cout << "  Дефицит: " << nedostig << " линии" << endl;

        double nuzhdaFinans = nedostig * 7500.0;
        cout << "  Препоръчително финансиране: " << nuzhdaFinans << " евро/год." << endl;
        cout << "  >> Подайте заявление за субсидия към областна управа." << endl;
    } else {
        cout << "  Статус: Транспортното покритие е добро" << endl;
        cout << "  Няма нужда от допълнително финансиране." << endl;
    }

    cout << "  ----------------------------" << endl;
}

void NaselenoMyasto::pokazhiInfo() const {
    cout << "\n  Тип: " << getTip() << endl;    
    cout << "  Име: " << ime << endl;
    cout << "  Население: " << naselenie << " жители" << endl;
    cout << "  Бюджет: " << byudzhet << " евро" << endl;
    cout << "  Възрастни: " << procentVuzrastni << "%"
         << (eRiskovaZona() ? "  [!] Рискова зона": "") << endl;
    cout << "  Автобусни линии: " << broiLiniiBus
         << " (препоръчителни: " << preporuchaniLinii() << ")" << endl;
    cout << "  Най-близък: " << naiBlizukGrad << " - " << razstoqnieDoGrad << " км" << endl;

    if (nuzhdaeSePoveche())
        cout << "  >> Нужда от финансиране за транспорт!" << endl;
}

string NaselenoMyasto::getTip() const { return "Населено място"; }

string NaselenoMyasto::kumFailString() const {
    return "Населено място|" + ime + "|" +
           to_string(naselenie) + "|" +   
           to_string(byudzhet) + "|" +
           to_string(procentVuzrastni) + "|" +
           to_string(razstoqnieDoGrad) + "|" +
           naiBlizukGrad + "|" +
           to_string(broiLiniiBus);
}
