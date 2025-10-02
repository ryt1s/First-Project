#include "student.h"
#include "io.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

int main() {
    srand(time(0));
    vector<Student> studentai;

    cout << "Pasirinkite veiksma:\n1 - Ivesti / generuoti / nuskaityti studentus\n2 - Sugeneruoti testinius failus\nJusu pasirinkimas: ";
    int pasirinkimas; cin >> pasirinkimas;

    if (pasirinkimas == 2) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        int kiekNd = 5;
        for (int dydis : dydziai) {
            string filename = "studentai" + std::to_string(dydis) + ".txt";
            auto start = high_resolution_clock::now();
            generuotiFaila(filename, dydis, kiekNd);
            auto end = high_resolution_clock::now();
            cout << "Sugeneravimo trukme: " << duration<double>(end-start).count() << " s\n";
        }
        return 0;
    }

    cout << "Pasirinkite duomenu ivedimo buda:\n1 - Rankiniu budu\n2 - Atsitiktiniai\n3 - Nuskaityti is failo\nJusu pasirinkimas: ";
    int ivestis; cin >> ivestis;

    auto start_read = high_resolution_clock::now();
    if (ivestis == 3) {
        string failas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failas;
        nuskaitytiIsFailo(failas, studentai);
    } else {
        char testi;
        do {
            Student stud;
            cout << "Vardas: "; cin >> stud.var;
            cout << "Pavarde: "; cin >> stud.pav;
            int suma=0, laik;
            if(ivestis==1) {
                while(true) {
                    laik=inputSkaicius("ND (0 baigti): ",0,10);
                    if(laik==0) break;
                    stud.paz.push_back(laik); suma+=laik;
                }
                stud.egz = inputSkaicius("Egzaminas: ",1,10);
            } else {
                int kiek = rand()%10+1;
                for(int i=0;i<kiek;i++){
                    int nd=rand()%10+1;
                    stud.paz.push_back(nd); suma+=nd;
                    cout << nd << " ";
                }
                cout << endl;
                stud.egz = rand()%10+1;
                cout << "Egzamino ivertinimas: " << stud.egz << endl;
            }
            skaiciuotiGalutinius(stud);
            studentai.push_back(stud);
            cout<<"Dar vienas? (t/n) "; cin>>testi;
        } while(testi=='t'||testi=='T');
    }
    auto end_read = high_resolution_clock::now();
    cout << "Duomenu ivesties/nuskaitymo trukme: " << duration<double>(end_read-start_read).count() << " s\n";

    cout << "Pasirinkite galutinio balo skaiciavimo metoda:\n1 - Vidurkis\n2 - Mediana\n3 - Abu (naudojame vidurki)\nJusu pasirinkimas: ";
    int metod; cin >> metod;
    if(metod==3) metod=1;

    auto start_sort = high_resolution_clock::now();
    vector<Student> vargsai, kietakiai;
    for(auto &s:studentai) {
        double gal = (metod==1)?s.galVid:s.galMed;
        if(gal<5.0) vargsai.push_back(s);
        else kietakiai.push_back(s);
    }
    auto end_sort = high_resolution_clock::now();
    cout<<"Rusiuojant uztruko: "<<duration<double>(end_sort-start_sort).count()<<" s\n";

    auto start_write = high_resolution_clock::now();
    issaugotiIFaila("vargsiukai.txt", vargsai, metod);
    issaugotiIFaila("kietakiai.txt", kietakiai, metod);
    auto end_write = high_resolution_clock::now();
    cout << "Isvedimas i failus uztruko: " << duration<double>(end_write-start_write).count() << " s\n";

    cout << "Vargsiukai ir kietakiai issaugoti i failus.\n";

    return 0;
}
