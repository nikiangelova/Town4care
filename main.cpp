
#include <iostream>    
#include <fstream>     
#include <sstream>     
#include <string>      
#include <limits>      
#include "Selo.h"   
#include "GradMaluk.h"      
using namespace std;

NaselenoMyasto* mesta[100];   
int broi = 0;                  

void izchistiVhod() {
    cin.clear();                                          
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
}

bool pitaiDaNe(const string& vupros) {
    string otgovor;
    cout << vupros << " (да/не): ";
    cin >> otgovor;
    izchistiVhod();
    return (otgovor == 'да' || otgovor == 'Да');
}

void pokazhiMenu() {
    cout << "\n         ГЛАВНО МЕНЮ    " << endl;
    cout << endl;
    cout << "  1. Добави село" << endl;
    cout << "  2. Добави малък град" << endl;
    cout << "  3. Покажи всички места" << endl;
    cout << "  4. Обобщен анализ на обществения транспорт" << endl;
    cout << "  5. Само рискови зони" << endl;
    cout << "  6. Детайлен отчет за едно място" << endl;
    cout << "  7. Запази данни" << endl;
    cout << "  8. Зареди данни" << endl;
    cout << "  0. Изход" << endl;
    cout << "  Избор: ";
}

struct ObshtiDanni {
    string ime, naiBlizukGrad;                          
    int naselenie = 0;
    int procentVuzrastni = 0;
    int liniiTemp = 0;
    double byudzhet = 0.0;
    double razstoqnieDoGrad = 0.0;
};

ObshtiDanni prochetiObshtiDanni() {
    ObshtiDanni danni;   

    cout << "  Име: ";
    getline(cin, danni.ime);                   

    cout << "  Население: ";
    cin >> danni.naselenie;
    izchistiVhod();                           

    cout << "  Годишен бюджет (евро): ";
    cin >> danni.byudzhet;
    izchistiVhod();

    cout << "  % жители над 65 г.: ";
    cin >> danni.procentVuzrastni;
    izchistiVhod();

    cout << "  Най-близък голям град: ";
    getline(cin, danni.naiBlizukGrad);

    cout << "  Разстояние (км): ";
    cin >> danni.razstoqnieDoGrad;
    izchistiVhod();

    cout << "  Брой автобусни линии сега: ";
    cin >> danni.liniiTemp;
    izchistiVhod();

    return danni;   
}

void dobavqSelo() {
    if (broi >= 100) {               
        cout << "  Достигнат максимален брой места!" << endl;
        return;
    }

    cout << "\n  >> Добавяне на село" << endl;
    ObshtiDanni danni = prochetiObshtiDanni();   

    bool zemedelie = pitaiDaNe(" Земеделска дейност?");
    bool uchilishte = pitaiDaNe(" Има ли училище?");

    mesta[broi] = new Selo(
        danni.ime, danni.naselenie, danni.byudzhet,
        danni.procentVuzrastni, danni.razstoqnieDoGrad, danni.naiBlizukGrad, danni.liniiTemp,
        zemedelie, uchilishte
    );
    broi++;   

    cout << "\n  [OK] \"" << danni.ime << "\" добавено!" << endl;

    NaselenoMyasto* myasto = mesta[broi - 1];   
    if (myasto->eRiskovaZona())
        cout << "  [!] Внимание: Рискова зона - "
             << myasto->getProcentVuzrastni() << "% възрастни!" << endl;
    if (myasto->nuzhdaeSePoveche())
        cout << "  [!] Нужда от транспорт: Има " << myasto->getBroiLiniiBus()
             << " линии, препоръчителни " << myasto->preporuchaniLinii() << endl;
}

void dobavqGrad() {
    if (broi >= 100) {
        cout << "  Максимален брой достигнат!" << endl;
        return;
    }

    cout << "\n  >> Добавяне на малък град" << endl;
    ObshtiDanni danni = prochetiObshtiDanni();

    bool obshtina  = pitaiDaNe("  Общинска управа?");
    bool bolnica = pitaiDaNe("  Болница/ здравен дом?");

    mesta[broi] = new GradMaluk(
        danni.ime, danni.naselenie, danni.byudzhet,
        danni.procentVuzrastni, danni.razstoqnieDoGrad, danni.naiBlizukGrad, danni.liniiTemp,
        obshtina, bolnica
    );
    broi++;

    cout << "\n  [OK] \"" << danni.ime << "\" добавен!" << endl;

    NaselenoMyasto* myasto = mesta[broi - 1];
    if (myasto->eRiskovaZona())
        cout << "  [!] Внимание: Рискова зона - "
             << myasto->getProcentVuzrastni() << "% възрастни!" << endl;
    if (myasto->nuzhdaeSePoveche())
        cout << "  [!] Нужда от транспорт: Има " << myasto->getBroiLiniiBus()
             << " линии, препоръчани " << myasto->preporuchaniLinii() << endl;
}

void pokazhiVsichki() {
    if (broi == 0) {
        cout << "\n  Няма добавени места." << endl;
        return;
    }
    cout << "\n  Общо: " << broi << " места" << endl;
    for (int i = 0; i < broi; i++) {
        cout << "\n  [" << i << "] ";
        mesta[i]->pokazhiInfo();   
    }
}

void analiziziMobilnost() {
    if (broi == 0) {
        cout << "\n  Няма данни." << endl;
        return;
    }

    int broiRiskovi = 0;
    int broiNuzhda = 0;
    double obshtoFinans = 0;

    cout << "\n  === Анализ на мобилността ===" << endl;

    for (int i = 0; i < broi; i++) {
        NaselenoMyasto* myasto = mesta[i];

        int nedostig = myasto->preporuchaniLinii() - myasto->getBroiLiniiBus();
        string statys = myasto->nuzhdaeSePoveche() ? "Нужда!": "Ок";

        cout << "  " << myasto->getIme()
             << " | " << myasto->getProcentVuzrastni() << "% възрастни"
             << " | " << (int)myasto->getRazstoqnie() << " км"
             << " | " << myasto->getBroiLiniiBus() << "/" << myasto->preporuchaniLinii() << " линии"
             << " | " << statys << endl;

        if (myasto->eRiskovaZona())broiRiskovi++;
        if (myasto->nuzhdaeSePoveche()) {
            broiNuzhda++;
            obshtoFinans += nedostig * 7500.0;
        }
    }

    cout << "\n  Рискови зони: " << broiRiskovi << endl;
    cout << "  Нуждаещи се от транспорт: " << broiNuzhda << endl;
    cout << "  Общо финансиране: " << obshtoFinans << " евро/год." << endl;
}

void pokazhiRiskoviZoni() {
    cout << "\n  === Рискови зони ===" << endl;
    bool nameren = false;
    for (int i = 0; i < broi; i++) {
        if (mesta[i]->eRiskovaZona()) {
            cout << "\n  [" << i << "] ";
            mesta[i]->pokazhiInfo();
            nameren = true;
        }
    }
    if (!nameren) cout << "\n  Няма рискови зони." << endl;
}

void detailenOtchet() {
    if (broi == 0) { cout << "\n  Няма данни." << endl; return; }

    cout << "\n  Места:" << endl;
    for (int i = 0; i < broi; i++)
        cout << "    [" << i << "] " << mesta[i]->getIme() << endl;

    int indeks;
    cout << "  Избери индекс: ";
    cin >> indeks;
    izchistiVhod();

    if (indeks < 0 || indeks >= broi) {
        cout << "  Невалиден индекс!" << endl;
        return;
    }

    mesta[indeks]->otchetMobilnost();
}

void zapishibVFail() {
    ofstream fail("town4care_data.txt");
    if (!fail.is_open()) {
        cout << "\n  Грешка при запис!" << endl;
        return;
    }
    for (int i = 0; i < broi; i++)
        fail << mesta[i]->kumFailString() << "\n";

    fail.close();
    cout << "\n  [OK] Запазено (" << broi << " записа)" << endl;
}

void zarediOtFail() {
    ifstream fail("town4care_data.txt");
    if (!fail.is_open()) {
        cout << "\n  Файлът не е намерен." << endl;
        return;
    }

    for (int i = 0; i < broi; i++) delete mesta[i];
    broi = 0;

    string red;
    while (getline(fail, red)) {
        if (red.empty()) continue;

        stringstream potok(red);
        string tip, ime, BlizukGrad, pomSpom;
        int naselenieTemp, vuzrastniTemp, liniiTemp;
        double byudzhet, razstoqnieTemp;
        bool flag1, flag2;

        getline(potok, tip, '|');
        getline(potok, ime, '|');
        getline(potok, pomSpom, '|');  naselenieTemp = stoi(pomSpom);
        getline(potok, pomSpom, '|');  byudzhet = stod(pomSpom);
        getline(potok, pomSpom, '|');  vuzrastniTemp = stoi(pomSpom);
        getline(potok, pomSpom, '|');  razstoqnieTemp = stod(pomSpom);
        getline(potok, BlizukGrad, '|');
        getline(potok, pomSpom, '|');  liniiTemp = stoi(pomSpom);
        getline(potok, pomSpom, '|');  flag1 = stoi(pomSpom);
        getline(potok, pomSpom);     flag2 = stoi(pomSpom);

        if (tip == "Село")
            mesta[broi++] = new Selo(ime, naselenieTemp, byudzhet, vuzrastniTemp, razstoqnieTemp, BlizukGrad, liniiTemp, flag1, flag2);
        else if (tip == "Малък град")
            mesta[broi++] = new GradMaluk(ime, naselenieTemp, byudzhet, vuzrastniTemp, razstoqnieTemp, BlizukGrad, liniiTemp, flag1, flag2);
    }

    fail.close();
    cout << "\n  [OK] Заредени " << broi << " записа." << endl;
}

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "\n  ===============================" << endl;
    cout << "       T O W N 4 C A R E  v2" << endl;
    cout << "   По-добра мобилност в България" << endl;
    cout << "  ===============================" << endl;

    int izbor;
    do {
        pokazhiMenu();

        if (!(cin >> izbor)) { izchistiVhod(); izbor = -1; continue; }
        izchistiVhod();

        switch (izbor) {
            case 1: dobavqSelo(); break;
            case 2: dobavqGrad(); break;
            case 3: pokazhiVsichki(); break;
            case 4: analiziziMobilnost(); break;
            case 5: pokazhiRiskoviZoni(); break;
            case 6: detailenOtchet(); break;
            case 7: zapishibVFail(); break;
            case 8: zarediOtFail(); break;
            case 0:
                cout << "\n  Довиждане от Town4Care!" << endl;
                break;
            default:
                cout << "\n  Невалиден избор." << endl;
        }
    } while (izbor != 0);

    for (int i = 0; i < broi; i++) delete mesta[i];

    return 0;
}
