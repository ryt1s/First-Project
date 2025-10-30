#include "student.h"
#include "io.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;
using namespace chrono;

int main() {
    srand(time(0));
    vector<Student> studentai;

    cout << "Pasirinkite veiksma:\n"
            "1 - Ivesti / generuoti / nuskaityti studentus\n"
            "2 - Sugeneruoti testinius failus\n"
            "Jusu pasirinkimas: ";
    int pasirinkimas; 
    cin >> pasirinkimas;

    if (pasirinkimas == 2) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        int kiekNd = 5;

        for (int dydis : dydziai) {
            string filename = "studentai_" + to_string(dydis) + ".txt";
            auto start = high_resolution_clock::now();
            generuotiFaila(filename, dydis, kiekNd);
            auto end = high_resolution_clock::now();
            cout << "Sugeneruotas failas " << filename 
                 << " per " << duration<double>(end - start).count() << " s\n";
        }
        return 0;
    }

    cout << "Pasirinkite duomenu ivedimo buda:\n"
            "1 - Rankiniu budu\n"
            "2 - Atsitiktiniai\n"
            "3 - Nuskaityti is failo\n"
            "Jusu pasirinkimas: ";
    int ivestis; 
    cin >> ivestis;

    string failas;
    double t_read = 0.0;

    if (ivestis == 3) {
        cout << "Iveskite failo pavadinima: ";
        cin >> failas;

        auto start_read = high_resolution_clock::now();
        nuskaitytiIsFailo(failas, studentai);
        auto end_read = high_resolution_clock::now();
        t_read = duration<double>(end_read - start_read).count();
        cout << "Duomenu nuskaitymas: " << t_read << " s\n";
    } else {
        char testi;
        do {
            Student stud;
            cout << "Vardas: "; cin >> stud.var;
            cout << "Pavarde: "; cin >> stud.pav;

            if (ivestis == 1) {
                int laik;
                while (true) {
                    laik = inputSkaicius("ND (0 baigti): ", 0, 10);
                    if (laik == 0) break;
                    stud.paz.push_back(laik);
                }
                stud.egz = inputSkaicius("Egzaminas: ", 1, 10);
            } else {
                int kiek = rand() % 10 + 1;
                cout << "ND ivertinimai: ";
                for (int i = 0; i < kiek; i++) {
                    int nd = rand() % 10 + 1;
                    stud.paz.push_back(nd);
                    cout << nd << " ";
                }
                cout << endl;
                stud.egz = rand() % 10 + 1;
                cout << "Egzamino ivertinimas: " << stud.egz << endl;
            }

            skaiciuotiGalutinius(stud);
            studentai.push_back(stud);

            cout << "Dar vienas? (t/n) "; cin >> testi;
        } while (testi == 't' || testi == 'T');
        failas = "manual_input";
    }

    cout << "Pasirinkite galutinio balo skaiciavimo metoda:\n"
            "1 - Vidurkis\n"
            "2 - Mediana\n"
            "3 - Abu\n"
            "Jusu pasirinkimas: ";
    int metod; 
    cin >> metod;

    int sortParam = 1;
    if (metod == 3) {
        cout << "Pagal ka rusiuoti?\n1 - Vidurki\n2 - Mediana\n";
        cin >> sortParam;
    }

    cout << "Rikiuoti:\n1 - Didejanciai\n2 - Mazejanciai\n";
    int order; cin >> order;

    auto start_sort = high_resolution_clock::now();
    sort(studentai.begin(), studentai.end(), [&](const Student &a, const Student &b) {
        double left = (sortParam == 2 ? a.galMed : a.galVid);
        double right = (sortParam == 2 ? b.galMed : b.galVid);
        return order == 1 ? left < right : left > right;
    });
    auto end_sort = high_resolution_clock::now();
    double t_sort = duration<double>(end_sort - start_sort).count();
    cout << "Rikiavimas: " << t_sort << " s\n";

    auto start_split = high_resolution_clock::now();
    vector<Student> vargsiukai, kietiakai;
    for (auto &s : studentai) {
        double gal = (sortParam == 2 ? s.galMed : s.galVid);
        if (gal < 5.0) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }
    auto end_split = high_resolution_clock::now();
    double t_split = duration<double>(end_split - start_split).count();
    cout << "Skirstymas i grupes: " << t_split << " s\n";

    auto start_write = high_resolution_clock::now();
    issaugotiIFaila("vargsiukai.txt", vargsiukai, metod);
    issaugotiIFaila("kietiakai.txt", kietiakai, metod);
    auto end_write = high_resolution_clock::now();
    double t_write = duration<double>(end_write - start_write).count();
    cout << "Isvedimas i failus: " << t_write << " s\n";

    auto printTime = [](double seconds) {
    cout << fixed << setprecision(6);
    if (seconds < 0.5)
        cout << seconds * 1000 << " ms";
    else
        cout << seconds << " s";
};

string metricStr = (sortParam == 1) ? "Vidurkis" : "Mediana";
string orderStr = (order == 1) ? "Didejimo tvarka" : "Mazejimo tvarka";

cout << "\n========== TESTING FILE: " << failas << " ==========\n";
cout << "Duomenu nuskaitymas: "; printTime(t_read); cout << "\n";
cout << "Rikiavimas pagal " << metricStr << " (" << orderStr << "): "; printTime(t_sort); cout << "\n";
cout << "Skirstymas i grupes: "; printTime(t_split); cout << "\n";
cout << "Isvedimas i failus: "; printTime(t_write); cout << "\n";

double t_total = t_read + t_sort + t_split + t_write;
cout << "Testavimo laikas: "; printTime(t_total); cout << "\n\n";
    return 0;
}
