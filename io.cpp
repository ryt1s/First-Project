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

void nuskaitytiIsFailo(const std::string& filename, vector<Student>& studentai) {
    ifstream fin(filename);
    if(!fin) { cout << "Nepavyko atidaryti failo: " << filename << endl; return; }

    string header; getline(fin, header);
    string line;
    while(getline(fin, line)) {
        if(line.empty()) continue;
        istringstream iss(line);
        Student stud;
        if(!(iss >> stud.pav >> stud.var)) continue;

        vector<int> paz;
        int balas;
        while(iss >> balas) paz.push_back(balas);

        if(paz.empty()) continue;
        stud.egz = paz.back(); paz.pop_back();
        stud.paz = paz;
        skaiciuotiGalutinius(stud);
        studentai.push_back(stud);
    }
}

void issaugotiIFaila(const string& filename, const vector<Student>& studentai, int metod) {
    ofstream fout(filename);
    if(!fout) { cerr << "Nepavyko sukurti failo: " << filename << endl; return; }

    fout << setw(15) << left << "Pavarde"
         << setw(15) << left << "Vardas"
         << "Galutinis" << endl;

    for(const auto& stud : studentai) {
        double gal = (metod == 1) ? stud.galVid : stud.galMed;
        fout << setw(15) << left << stud.pav
             << setw(15) << left << stud.var
             << fixed << setprecision(2) << gal << endl;
    }
}

void generuotiFaila(const string& filename, int kiekStudentu, int kiekNd) {
    auto start = high_resolution_clock::now();
    ofstream fout(filename);
    if(!fout) { cerr << "Nepavyko sukurti failo: " << filename << endl; return; }

    fout << setw(12) << left << "Pavarde" << setw(12) << left << "Vardas";
    for(int i=1; i<=kiekNd; i++) fout << setw(5) << ("ND"+to_string(i));
    fout << setw(10) << "Egzaminas" << "\n";

    for(int i=1; i<=kiekStudentu; i++){
        fout << setw(12) << left << ("Pavarde"+to_string(i))
             << setw(12) << left << ("Vardas"+to_string(i));
        for(int j=0;j<kiekNd;j++) fout << setw(5) << (rand()%10+1);
        fout << setw(10) << (rand()%10+1) << "\n";
    }

    fout.close();
    auto end = high_resolution_clock::now();
    cout << "Sugeneruotas failas: " << filename
         << " (" << kiekStudentu << " irasu) per " << duration<double>(end-start).count() << " s\n";
}
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
