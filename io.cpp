#include "io.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void nuskaitytiIsFailo(const string& filename, vector<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) { cout << "Nepavyko atidaryti failo: " << filename << endl; return; }

    string header;
    getline(fin, header);

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Student stud;
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

int inputSkaicius(const string& pranesimas, int min, int max) {
    int value;
    while (true) {
        cout << pranesimas;
        cin >> value;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (value < min || value > max) continue;
        break;
    }
    return value;
}

void generuotiFaila(const string& filename, int kiekStudentu, int kiekNd) {
    auto start = high_resolution_clock::now();
    ofstream fout(filename);
    if (!fout) { cerr << "Nepavyko sukurti failo: " << filename << endl; return; }

    fout << setw(12) << left << "Pavarde" << setw(12) << left << "Vardas";
    for (int i = 1; i <= kiekNd; i++) fout << setw(5) << ("ND" + to_string(i));
    fout << setw(10) << "Egzaminas\n";

    for (int i = 1; i <= kiekStudentu; i++) {
        fout << setw(12) << left << ("Pavarde" + to_string(i))
             << setw(12) << left << ("Vardas" + to_string(i));
        for (int j = 0; j < kiekNd; j++) fout << setw(5) << (rand() % 10 + 1);
        fout << setw(10) << (rand() % 10 + 1) << "\n";
    }

    fout.close();
    auto end = high_resolution_clock::now();
    cout << "Sugeneruotas failas: " << filename << " (" << kiekStudentu << " irasu) per "
         << duration<double>(end - start).count() << " s\n";
}

void issaugotiIFaila(const string& filename, const vector<Student>& studentai, int metodas) {
    ofstream fout(filename);
    if (!fout) { cerr << "Nepavyko sukurti failo: " << filename << endl; return; }

    fout << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas";
    if (metodas == 1) fout << "Galutinis (Vid.)";
    else if (metodas == 2) fout << "Galutinis (Med.)";
    else fout << setw(18) << left << "Galutinis (Vid.)" << setw(17) << left << "Galutinis (Med.)";
    fout << "\n" << string(55, '-') << "\n";

    for (auto& stud : studentai) {
        fout << setw(15) << left << stud.pav << setw(15) << left << stud.var;
        if (metodas == 1) fout << fixed << setprecision(2) << stud.galVid;
        else if (metodas == 2) fout << fixed << setprecision(2) << stud.galMed;
        else fout << setw(18) << left << fixed << setprecision(2) << stud.galVid
                  << setw(17) << left << fixed << setprecision(2) << stud.galMed;
        fout << "\n";
    }
}
