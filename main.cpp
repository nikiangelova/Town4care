#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "Selo.h"
#include "GradMalak.h"
using namespace std;

NaselenоMyasto* mesta[100];
int broi = 0;

void izchistiVhod() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool pitaiDaNe(const string& vapros) {
    char otgovor;
    cout << vapros << " (y/n): ";
    cin >> otgovor;
    izchistiVhod();
    return (otgovor == 'y' || otgovor == 'Y');
}

void pokazhiMeniu() {
    cout << "\n  === GLAVNO MENU ===" << endl;
    cout << "  1. Dobavi selo" << endl;
    cout << "  2. Dobavi malak grad" << endl;
    cout << "  3. Pokazhi vsichki mesta" << endl;
    cout << "  4. Obobshten analiz na mobilnostta" << endl;
    cout << "  5. Samo riskovi zoni" << endl;
    cout << "  6. Detailen otchet za edno myasto" << endl;
    cout << "  7. Zapazi dannite" << endl;
    cout << "  8. Zaredi danni" << endl;
    cout << "  0. Izhod" << endl;
    cout << "  Izbor: ";
}

struct ObshtiDanni {
    string ime, naiBlizakGrad;
    int    naselenie, procentVazrastni, liniiTemp;
    double byudzhet, razstoqnieDoGrad;
};

ObshtiDanni prochetиObshtiDanni() {
    ObshtiDanni danni;

    cout << "  Ime: ";
    getline(cin, danni.ime);

    cout << "  Naselenie: ";
    cin >> danni.naselenie;
    izchistiVhod();

    cout << "  Godishen byudzhet (lv.): ";
    cin >> danni.byudzhet;
    izchistiVhod();

    cout << "  % zhiteli nad 65 g.: ";
    cin >> danni.procentVazrastni;
    izchistiVhod();

    cout << "  Nai-blizak golyam grad: ";
    getline(cin, danni.naiBlizakGrad);

    cout << "  Razstoqnie do nego (km): ";
    cin >> danni.razstoqnieDoGrad;
    izchistiVhod();

    cout << "  Broi avtobusni linii sega: ";
    cin >> danni.liniiTemp;
    izchistiVhod();

    return danni;
}

void dobavqSelo() {
    if (broi >= 100) {
        cout << "  Maksimalen broi mesta dostignat!" << endl;
        return;
    }

    cout << "\n  >> DOBAVYANE NA SELO" << endl;
    ObshtiDanni danni = prochetиObshtiDanni();

    bool zemedelie   = pitaiDaNe("  Zemedelska deinost?");
    bool uchilishte = pitaiDaNe("  Ima li uchilishte?");

    mesta[broi] = new Selo(
        danni.ime, danni.naselenie, danni.byudzhet,
        danni.procentVazrastni, danni.razstoqnieDoGrad, danni.naiBlizakGrad, danni.liniiTemp,
        zemedelie, uchilishte
    );
    broi++;

    cout << "\n  [OK] \"" << danni.ime << "\" dobaveno!" << endl;

    NaselenоMyasto* myasto = mesta[broi - 1];
    if (myasto->eRiskovaZona())
        cout << "  [!] VNIMANIE: Riskova zona — "
             << myasto->vzemProcentVazrastni() << "% vazrastni!" << endl;
    if (myasto->nuzhdaeSePoveche())
        cout << "  [!] Nuzda ot transport: ima " << myasto->vzemBroiLiniiBus()
             << " linii, preporachani " << myasto->preporachaniLinii() << endl;
}

void dobavqGrad() {
    if (broi >= 100) {
        cout << "  Maksimalen broi mesta dostignat!" << endl;
        return;
    }

    cout << "\n  >> DOBAVYANE NA MALAK GRAD" << endl;
    ObshtiDanni danni = prochetиObshtiDanni();

    bool obshtina  = pitaiDaNe("  Obshtinska uprava?");
    bool bolnica = pitaiDaNe("  Bolnica / zdraven dom?");

    mesta[broi] = new GradMalak(
        danni.ime, danni.naselenie, danni.byudzhet,
        danni.procentVazrastni, danni.razstoqnieDoGrad, danni.naiBlizakGrad, danni.liniiTemp,
        obshtina, bolnica
    );
    broi++;

    cout << "\n  [OK] \"" << danni.ime << "\" dobaven!" << endl;

    NaselenоMyasto* myasto = mesta[broi - 1];
    if (myasto->eRiskovaZona())
        cout << "  [!] VNIMANIE: Riskova zona — "
             << myasto->vzemProcentVazrastni() << "% vazrastni!" << endl;
    if (myasto->nuzhdaeSePoveche())
        cout << "  [!] Nuzda ot transport: ima " << myasto->vzemBroiLiniiBus()
             << " linii, preporachani " << myasto->preporachaniLinii() << endl;
}

void pokazhiVsichki() {
    if (broi == 0) {
        cout << "\n  Nyama dobaveni mesta." << endl;
        return;
    }
    cout << "\n  Obshto: " << broi << " mesta" << endl;
    for (int i = 0; i < broi; i++) {
        cout << "\n  [" << i << "] ";
        mesta[i]->pokazhiInfo();
    }
}

void analiziziMobilnost() {
    if (broi == 0) {
        cout << "\n  Nyama danni." << endl;
        return;
    }

    int broiRiskovi    = 0;
    int broiNuzhda = 0;
    double obshtoFinans = 0;

    cout << "\n  === ANALIZ NA MOBILNOSTTA ===" << endl;

    for (int i = 0; i < broi; i++) {
        NaselenоMyasto* myasto = mesta[i];

        int nedostig = myasto->preporachaniLinii() - myasto->vzemBroiLiniiBus();
        string statys = myasto->nuzhdaeSePoveche() ? "NUZDA!" : "OK";

        cout << "  " << myasto->vzemIme()
             << " | " << myasto->vzemProcentVazrastni() << "% vazr."
             << " | " << (int)myasto->vzemRazstoqnie() << " km"
             << " | " << myasto->vzemBroiLiniiBus() << "/" << myasto->preporachaniLinii() << " lin."
             << " | " << statys << endl;

        if (myasto->eRiskovaZona())       broiRiskovi++;
        if (myasto->nuzhdaeSePoveche()) {
            broiNuzhda++;
            obshtoFinans += nedostig * 15000.0;
        }
    }

    cout << "\n  Riskovi zoni             : " << broiRiskovi << endl;
    cout << "  Nuzhdaeshti se ot transport: " << broiNuzhda << endl;
    cout << "  Obshto finansirane         : " << obshtoFinans << " lv./god." << endl;
}

void pokazhiRiskoviZoni() {
    cout << "\n  === RISKOVI ZONI ===" << endl;
    bool nameren = false;
    for (int i = 0; i < broi; i++) {
        if (mesta[i]->eRiskovaZona()) {
            cout << "\n  [" << i << "] ";
            mesta[i]->pokazhiInfo();
            nameren = true;
        }
    }
    if (!nameren) cout << "\n  Nyama riskovi zoni." << endl;
}

void detailenOtchet() {
    if (broi == 0) { cout << "\n  Nyama danni." << endl; return; }

    cout << "\n  Mesta:" << endl;
    for (int i = 0; i < broi; i++)
        cout << "    [" << i << "] " << mesta[i]->vzemIme() << endl;

    int indeks;
    cout << "  Izberi indeks: ";
    cin >> indeks;
    izchistiVhod();

    if (indeks < 0 || indeks >= broi) {
        cout << "  Nevaliden indeks!" << endl;
        return;
    }

    mesta[indeks]->otchetMobilnost();
}

void zapishibVFail() {
    ofstream fail("town4care_data.txt");
    if (!fail.is_open()) {
        cout << "\n  Greshka pri zapis!" << endl;
        return;
    }
    for (int i = 0; i < broi; i++)
        fail << mesta[i]->kamFailString() << "\n";

    fail.close();
    cout << "\n  [OK] Zapazeno (" << broi << " zapisa)" << endl;
}

void zaredіOtFail() {
    ifstream fail("town4care_data.txt");
    if (!fail.is_open()) {
        cout << "\n  Failat ne e nameren." << endl;
        return;
    }

    for (int i = 0; i < broi; i++) delete mesta[i];
    broi = 0;

    string red;
    while (getline(fail, red)) {
        if (red.empty()) continue;

        stringstream potok(red);
        string tip, ime, blizakGrad, pomSpom;
        int naselenieTemp, vazrastniTemp, liniiTemp;
        double byudzhet, razstoqnieTemp;
        bool flag1, flag2;

        getline(potok, tip,    '|');
        getline(potok, ime,    '|');
        getline(potok, pomSpom,     '|');  naselenieTemp     = stoi(pomSpom);
        getline(potok, pomSpom,     '|');  byudzhet  = stod(pomSpom);
        getline(potok, pomSpom,     '|');  vazrastniTemp = stoi(pomSpom);
        getline(potok, pomSpom,     '|');  razstoqnieTemp    = stod(pomSpom);
        getline(potok, blizakGrad,'|');
        getline(potok, pomSpom,     '|');  liniiTemp = stoi(pomSpom);
        getline(potok, pomSpom,     '|');  flag1 = stoi(pomSpom);
        getline(potok, pomSpom      );     flag2 = stoi(pomSpom);

        if (tip == "VILLAGE")
            mesta[broi++] = new Selo(ime, naselenieTemp, byudzhet, vazrastniTemp, razstoqnieTemp, blizakGrad, liniiTemp, flag1, flag2);
        else if (tip == "TOWN")
            mesta[broi++] = new GradMalak(ime, naselenieTemp, byudzhet, vazrastniTemp, razstoqnieTemp, blizakGrad, liniiTemp, flag1, flag2);
    }

    fail.close();
    cout << "\n  [OK] Zaredeni " << broi << " zapisa." << endl;
}

int main() {
    cout << "\n  ===============================" << endl;
    cout << "        T O W N 4 C A R E  v2" << endl;
    cout << "  Po-dobra mobilnost v Balgariya" << endl;
    cout << "  ===============================" << endl;

    int izbor;
    do {
        pokazhiMeniu();

        if (!(cin >> izbor)) { izchistiVhod(); izbor = -1; continue; }
        izchistiVhod();

        switch (izbor) {
            case 1: dobavqSelo();      break;
            case 2: dobavqGrad();         break;
            case 3: pokazhiVsichki();         break;
            case 4: analiziziMobilnost(); break;
            case 5: pokazhiRiskoviZoni();   break;
            case 6: detailenOtchet();    break;
            case 7: zapishibVFail();      break;
            case 8: zaredіOtFail();    break;
            case 0:
                cout << "\n  Dovizdane ot Town4Care!" << endl;
                break;
            default:
                cout << "\n  Nevaliden izbor." << endl;
        }
    } while (izbor != 0);

    for (int i = 0; i < broi; i++) delete mesta[i];

    return 0;
}
