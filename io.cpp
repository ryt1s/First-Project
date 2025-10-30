#include "io.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ------------------ GENERATOR ------------------
void generuotiFaila(const string& filename, int kiekStudentu, int kiekNd) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Nepavyko sukurti failo: " << filename << endl;
        return;
    }

    // Header
    fout << setw(20) << left << "Pavarde"
         << setw(20) << left << "Vardas";
    for (int i = 1; i <= kiekNd; i++)
        fout << setw(5) << ("ND" + to_string(i));
    fout << setw(10) << "Egzaminas" << "\n";

    // Random student data
    for (int i = 1; i <= kiekStudentu; i++) {
        string pav = "Pavarde" + to_string(i);
        string var = "Vardas" + to_string(i);

        fout << setw(20) << left << pav
             << setw(20) << left << var;

        for (int j = 0; j < kiekNd; j++)
            fout << setw(5) << (rand() % 10 + 1);
        fout << setw(10) << (rand() % 10 + 1) << "\n";
    }

    fout.close();
    cout << "Sugeneruotas failas: " << filename << " (" << kiekStudentu << " irasu)\n";
}

// ------------------ FILE READING ------------------
void nuskaitytiIsFailo(const string& filename, vector<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

    string header;
    getline(fin, header); // skip header
    string line;

    while (getline(fin, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Student stud;

        // Read surname and name separately
        if (!(iss >> stud.pav >> stud.var)) continue;

        vector<int> paz;
        int balas;
        while (iss >> balas) paz.push_back(balas);

        if (paz.empty()) continue;

        stud.egz = paz.back(); paz.pop_back();
        stud.paz = paz;

        skaiciuotiGalutinius(stud);
        studentai.push_back(stud);
    }
}

// ------------------ FILE WRITING ------------------
void issaugotiIFaila(const string& filename, const vector<Student>& studentai, int metod) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Nepavyko sukurti failo: " << filename << endl;
        return;
    }

    int pavWidth = 25;
    int varWidth = 25;
    int galWidth = 15;

    // Header
    fout << setw(pavWidth) << left << "Pavarde"
         << setw(varWidth) << left << "Vardas";
    if (metod == 3) {
        fout << setw(galWidth) << left << "Galutinis (Vid.)"
             << setw(galWidth) << left << "Galutinis (Med.)";
    } else {
        fout << setw(galWidth) << left << "Galutinis";
    }
    fout << endl;

    for (const auto& stud : studentai) {
        fout << setw(pavWidth) << left << stud.pav
             << setw(varWidth) << left << stud.var;

        if (metod == 3) {
            fout << setw(galWidth) << left << fixed << setprecision(2) << stud.galVid
                 << setw(galWidth) << left << fixed << setprecision(2) << stud.galMed;
        } else {
            double gal = (metod == 1 ? stud.galVid : stud.galMed);
            fout << setw(galWidth) << left << fixed << setprecision(2) << gal;
        }

        fout << endl;
    }
}

// ------------------ SAFE INPUT ------------------
int inputSkaicius(const string& pranesimas, int min, int max) {
    int value;
    while (true) {
        cout << pranesimas;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Klaida! Iveskite sveika skaiciu.\n";
            continue;
        }
        if (value < min || value > max) {
            cout << "Balas turi buti nuo " << min << " iki " << max << ". Bandykite dar karta.\n";
            continue;
        }
        break;
    }
    return value;
}
