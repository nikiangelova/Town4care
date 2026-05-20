// -------------------------------------------------------
//  Town4Care v2 — Mobilnost i dostap v malki naseleni mesta
//  "Grizha za grada — ot chetiri gledni tochki."
//  Ekip: [ime na ekipa]
// -------------------------------------------------------

#include <iostream>    // za cout, cin
#include <fstream>     // za ofstream (zapis) i ifstream (chetene na fail)
#include <sstream>     // za stringstream (razbivane na tekstov red po razdelitel)
#include <string>      // za string
#include <limits>      // za numeric_limits (izchistvane na vhodniq bufer)
#include "Selo.h"   // vklyuchva Selo (i NaselenоMyasto.h vatre v nego)
#include "GradMalak.h"      // vklyuchva GradMalak
using namespace std;

// -------------------------------------------------------
//  Globalen masiv ot ukazateli kam NaselenоMyasto
//  Mozhe da pazi obekti ot tip Selo ili GradMalak (polimorfizam).
//  Maksimum 100 mesta — lesen masiv vmesto vector.
// -------------------------------------------------------
NaselenоMyasto* mesta[100];   // masiv ot ukazateli
int broi = 0;                  // kolko mesta sa dobaveni dosega

// -------------------------------------------------------
//  Pomoshni funkcii
// -------------------------------------------------------

// izchistya vhodniq bufer sled cin >> — predotvratqva "zalepvane" na Enter
void izchistiVhod() {
    cin.clear();                                          // nulira flagovete za greshka
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // propuska do kraq na reda
}

// zadava vapros i ochakva y/n otgovor
// vrasha true ako e 'y' ili 'Y', inache false
bool pitaiDaNe(const string& vapros) {
    char otgovor;
    cout << vapros << " (y/n): ";
    cin >> otgovor;
    izchistiVhod();
    return (otgovor == 'y' || otgovor == 'Y');
}

// pechat glavnoto menu
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

// -------------------------------------------------------
//  Struktura za vremenno pazene na obshtite danni pri vavezhdane
//  Izpolzva se v dobavqSelo() i dobavqGrad()
// -------------------------------------------------------
struct ObshtiDanni {
    string ime, naiBlizakGrad;                          // tekstovi poleta
    int    naselenie, procentVazrastni, liniiTemp;       // celochiselni
    double byudzhet, razstoqnieDoGrad;                     // drobni chisla
};

// prochita ot konzolata obshtite danni za vsyako naseleno myasto
ObshtiDanni prochetиObshtiDanni() {
    ObshtiDanni danni;   // sazdava prazna struktura

    cout << "  Ime: ";
    getline(cin, danni.ime);                   // getline chete cyal red myasto intervali

    cout << "  Naselenie: ";
    cin >> danni.naselenie;
    izchistiVhod();                           // izchistya bufera sled chisloto

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

    return danni;   // vrasha popalnenata struktura
}

// -------------------------------------------------------
//  Dobavyane na selo
// -------------------------------------------------------
void dobavqSelo() {
    if (broi >= 100) {               // proverka dali masivat ne e palen
        cout << "  Maksimalen broi mesta dostignat!" << endl;
        return;
    }

    cout << "\n  >> DOBAVYANE NA SELO" << endl;
    ObshtiDanni danni = prochetиObshtiDanni();   // prochita obshtite danni

    // zadava dopalnitelni vaprosi specificni za selo
    bool zemedelie   = pitaiDaNe("  Zemedelska deinost?");
    bool uchilishte = pitaiDaNe("  Ima li uchilishte?");

    // sazdava nov Selo obekt v dinamichnata pamet (heap)
    // new vrasha ukazatel, koito pazim v masiva
    mesta[broi] = new Selo(
        danni.ime, danni.naselenie, danni.byudzhet,
        danni.procentVazrastni, danni.razstoqnieDoGrad, danni.naiBlizakGrad, danni.liniiTemp,
        zemedelie, uchilishte
    );
    broi++;   // uvelicava broyacha

    cout << "\n  [OK] \"" << danni.ime << "\" dobaveno!" << endl;

    // vednaga preduprezhdava ako e riskova zona
    NaselenоMyasto* myasto = mesta[broi - 1];   // posled dobavenoto
    if (myasto->eRiskovaZona())
        cout << "  [!] VNIMANIE: Riskova zona — "
             << myasto->vzemProcentVazrastni() << "% vazrastni!" << endl;
    if (myasto->nuzhdaeSePoveche())
        cout << "  [!] Nuzda ot transport: ima " << myasto->vzemBroiLiniiBus()
             << " linii, preporachani " << myasto->preporachaniLinii() << endl;
}

// -------------------------------------------------------
//  Dobavyane na malak grad
// -------------------------------------------------------
void dobavqGrad() {
    if (broi >= 100) {
        cout << "  Maksimalen broi mesta dostignat!" << endl;
        return;
    }

    cout << "\n  >> DOBAVYANE NA MALAK GRAD" << endl;
    ObshtiDanni danni = prochetиObshtiDanni();

    bool obshtina  = pitaiDaNe("  Obshtinska uprava?");
    bool bolnica = pitaiDaNe("  Bolnica / zdraven dom?");

    // sazdava nov GradMalak obekt
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

// -------------------------------------------------------
//  Pokazva vsichki dobaveni mesta
//  Chrez mesta[i]->pokazhiInfo() se vika virtualniqt metod —
//  ako e Selo, se vika Selo::pokazhiInfo(); ako e GradMalak — GradMalak::pokazhiInfo()
//  Tova e polimorfizam: edin i sasht red kod pravi razlichni neshta.
// -------------------------------------------------------
void pokazhiVsichki() {
    if (broi == 0) {
        cout << "\n  Nyama dobaveni mesta." << endl;
        return;
    }
    cout << "\n  Obshto: " << broi << " mesta" << endl;
    for (int i = 0; i < broi; i++) {
        cout << "\n  [" << i << "] ";
        mesta[i]->pokazhiInfo();   // polimorfno izvikvane
    }
}

// -------------------------------------------------------
//  Obobshten analiz na mobilnostta za vsichki mesta
//  Pechat tablica i obobshtena statistika.
// -------------------------------------------------------
void analiziziMobilnost() {
    if (broi == 0) {
        cout << "\n  Nyama danni." << endl;
        return;
    }

    int broiRiskovi    = 0;   // broi riskovi zoni
    int broiNuzhda = 0;   // broi mesta nuzhdaeshti se ot finansirane
    double obshtoFinans = 0;   // obshto preporachano finansirane

    cout << "\n  === ANALIZ NA MOBILNOSTTA ===" << endl;

    // obhozhdya vsichki mesta myasto cikyal
    for (int i = 0; i < broi; i++) {
        NaselenоMyasto* myasto = mesta[i];   // sakrashenie za po-chetim kod

        // izchislqva deficita na linii
        int nedostig = myasto->preporachaniLinii() - myasto->vzemBroiLiniiBus();
        string statys = myasto->nuzhdaeSePoveche() ? "NUZDA!" : "OK";

        // pechat red ot tablicata za vsyako myasto
        cout << "  " << myasto->vzemIme()
             << " | " << myasto->vzemProcentVazrastni() << "% vazr."
             << " | " << (int)myasto->vzemRazstoqnie() << " km"
             << " | " << myasto->vzemBroiLiniiBus() << "/" << myasto->preporachaniLinii() << " lin."
             << " | " << statys << endl;

        // aktualizira statistikata
        if (myasto->eRiskovaZona())       broiRiskovi++;
        if (myasto->nuzhdaeSePoveche()) {
            broiNuzhda++;
            obshtoFinans += nedostig * 15000.0;   // 15 000 lv. na linia na godina
        }
    }

    // obobshtenie
    cout << "\n  Riskovi zoni             : " << broiRiskovi << endl;
    cout << "  Nuzhdaeshti se ot transport: " << broiNuzhda << endl;
    cout << "  Obshto finansirane         : " << obshtoFinans << " lv./god." << endl;
}

// -------------------------------------------------------
//  Pokazva samo riskovite zoni (> 40% vazrastni)
// -------------------------------------------------------
void pokazhiRiskoviZoni() {
    cout << "\n  === RISKOVI ZONI ===" << endl;
    bool nameren = false;
    for (int i = 0; i < broi; i++) {
        if (mesta[i]->eRiskovaZona()) {   // proverqva samo riskovite
            cout << "\n  [" << i << "] ";
            mesta[i]->pokazhiInfo();
            nameren = true;
        }
    }
    if (!nameren) cout << "\n  Nyama riskovi zoni." << endl;
}

// -------------------------------------------------------
//  Detailen otchet za edno konkretno myasto (po indeks)
// -------------------------------------------------------
void detailenOtchet() {
    if (broi == 0) { cout << "\n  Nyama danni." << endl; return; }

    // pokazva spisak za izbor
    cout << "\n  Mesta:" << endl;
    for (int i = 0; i < broi; i++)
        cout << "    [" << i << "] " << mesta[i]->vzemIme() << endl;

    int indeks;
    cout << "  Izberi indeks: ";
    cin >> indeks;
    izchistiVhod();

    // proverka za validen indeks
    if (indeks < 0 || indeks >= broi) {
        cout << "  Nevaliden indeks!" << endl;
        return;
    }

    mesta[indeks]->otchetMobilnost();   // pechat detailniya otchet
}

// -------------------------------------------------------
//  Zapazva dannite v tekstov fail
//  Vsyako naseleno myasto se zapisva na otdelen red.
// -------------------------------------------------------
void zapishibVFail() {
    ofstream fail("town4care_data.txt");   // otvara fail za zapis
    if (!fail.is_open()) {
        cout << "\n  Greshka pri zapis!" << endl;
        return;
    }
    for (int i = 0; i < broi; i++)
        fail << mesta[i]->kamFailString() << "\n";   // zapisva vsyako myasto

    fail.close();   // zatvara faila
    cout << "\n  [OK] Zapazeno (" << broi << " zapisa)" << endl;
}

// -------------------------------------------------------
//  Zarezhda danni ot tekstov fail
//  Razbiva vseki red po | i sazdava Selo ili GradMalak obekt.
// -------------------------------------------------------
void zaredіOtFail() {
    ifstream fail("town4care_data.txt");   // otvara fail za chetene
    if (!fail.is_open()) {
        cout << "\n  Failat ne e nameren." << endl;
        return;
    }

    // izchistya starite danni ot pametta
    for (int i = 0; i < broi; i++) delete mesta[i];
    broi = 0;

    string red;
    while (getline(fail, red)) {   // chete red po red
        if (red.empty()) continue;   // preskača prazni redove

        stringstream potok(red);   // stringstream: pozvolqva chetene ot string kato ot cin
        string tip, ime, blizakGrad, pomSpom;
        int naselenieTemp, vazrastniTemp, liniiTemp;
        double byudzhet, razstoqnieTemp;
        bool flag1, flag2;

        // razbiva reda po razdelitelya | i prisvoyava stoinostite
        getline(potok, tip,    '|');   // chete do sledvashtoto |
        getline(potok, ime,    '|');
        getline(potok, pomSpom,     '|');  naselenieTemp     = stoi(pomSpom);   // stoi: string -> int
        getline(potok, pomSpom,     '|');  byudzhet  = stod(pomSpom);   // stod: string -> double
        getline(potok, pomSpom,     '|');  vazrastniTemp = stoi(pomSpom);
        getline(potok, pomSpom,     '|');  razstoqnieTemp    = stod(pomSpom);
        getline(potok, blizakGrad,'|');
        getline(potok, pomSpom,     '|');  liniiTemp = stoi(pomSpom);
        getline(potok, pomSpom,     '|');  flag1 = stoi(pomSpom);        // "0"/"1" -> bool
        getline(potok, pomSpom      );     flag2 = stoi(pomSpom);

        // sazdava praviliya tip obekt sprqmo zapisaniya tip
        if (tip == "VILLAGE")
            mesta[broi++] = new Selo(ime, naselenieTemp, byudzhet, vazrastniTemp, razstoqnieTemp, blizakGrad, liniiTemp, flag1, flag2);
        else if (tip == "TOWN")
            mesta[broi++] = new GradMalak(ime, naselenieTemp, byudzhet, vazrastniTemp, razstoqnieTemp, blizakGrad, liniiTemp, flag1, flag2);
    }

    fail.close();
    cout << "\n  [OK] Zaredeni " << broi << " zapisa." << endl;
}

// -------------------------------------------------------
//  main — vhodna tochka na programata
//  Pokazva menu i obrabotva izbora na potrebitelya v cikyal.
// -------------------------------------------------------
int main() {
    cout << "\n  ===============================" << endl;
    cout << "       T O W N 4 C A R E  v2" << endl;
    cout << "  Po-dobra mobilnost v Balgariya" << endl;
    cout << "  ===============================" << endl;

    int izbor;
    do {
        pokazhiMeniu();

        // ako vhodat ne e chislo, izchistiVhod i probva otnovo
        if (!(cin >> izbor)) { izchistiVhod(); izbor = -1; continue; }
        izchistiVhod();

        // switch: izpalnyava razlichen kod sprqmo izbora
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
    } while (izbor != 0);   // cikalat produlzhava dokato ne izberem 0

    // osvobozhdava dinamichnata pamet (delete za vseki new)
    for (int i = 0; i < broi; i++) delete mesta[i];

    return 0;   // 0 = programata zavarshy uspeshno
}
