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


void generuotiFaila(const string& filename, int kiekStudentu, int kiekNd) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Nepavyko sukurti failo: " << filename << endl;
        return;
    }

    
    fout << setw(20) << left << "Pavarde"
         << setw(20) << left << "Vardas";
    for (int i = 1; i <= kiekNd; i++)
        fout << setw(5) << ("ND" + to_string(i));
    fout << setw(10) << "Egzaminas" << "\n";

   
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


void nuskaitytiIsFailo(const string& filename, vector<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

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


void issaugotiIFaila(const string& filename, const vector<Student>& students, int metod) {
    // Naudojame std::ios::trunc, kad perrašytumėme failą
    std::ofstream fout(filename, std::ios::out | std::ios::trunc); 
    if (!fout.is_open()) return;

    // Antraštės formatavimas (naudojamas lėtas, bet patikimas stream)
    fout << setw(25) << left << "Pavarde"
         << setw(25) << left << "Vardas";
    if (metod == 3) {
        fout << setw(15) << left << "Galutinis (Vid.)"
             << setw(15) << left << "Galutinis (Med.)";
    } else {
        fout << setw(15) << left << "Galutinis";
    }
    fout << "\n"; // Naudojame \n, nes fstream naudoja buferius

    // Bufferio nustatymas (jūsų optimizacija)
    std::string buffer;
    buffer.reserve(1 << 20);  // ~1MB initial buffer
    const size_t FLUSH_THRESHOLD = (1 << 20); // 1MB

    for (const auto &s : students) {
        char line[256];
        int n = 0;
        
        if (metod == 3) {
             n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f %15.2f\n",
                               s.pav.c_str(), s.var.c_str(), s.galVid, s.galMed);
        } else {
            double galutinis = (metod == 1 ? s.galVid : s.galMed);
             n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f\n",
                               s.pav.c_str(), s.var.c_str(), galutinis);
        }
        
        buffer.append(line, n);

        if (buffer.size() > FLUSH_THRESHOLD) { // flush every ~1MB
            fout.write(buffer.data(), buffer.size());
            buffer.clear();
        }
    }
    // Išvalyti likusį buferį
    if (!buffer.empty()) fout.write(buffer.data(), buffer.size());
    
    fout.close();
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

void nuskaitytiIsFailo(const string& filename, list<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

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

void issaugotiIFaila(const string& filename, const list<Student>& students, int metod) {
    // Naudojame std::ios::trunc, kad perrašytumėme failą
    std::ofstream fout(filename, std::ios::out | std::ios::trunc);
    if (!fout.is_open()) return;

    // Antraštės formatavimas
    fout << setw(25) << left << "Pavarde"
         << setw(25) << left << "Vardas";
    if (metod == 3) {
        fout << setw(15) << left << "Galutinis (Vid.)"
             << setw(15) << left << "Galutinis (Med.)";
    } else {
        fout << setw(15) << left << "Galutinis";
    }
    fout << "\n";

    // Bufferio nustatymas (jūsų optimizacija)
    std::string buffer;
    buffer.reserve(1 << 20); // ~1MB initial buffer
    const size_t FLUSH_THRESHOLD = (1 << 20); // 1MB

    for (const auto &s : students) {
        char line[256];
        int n = 0;
        
        if (metod == 3) {
             n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f %15.2f\n",
                               s.pav.c_str(), s.var.c_str(), s.galVid, s.galMed);
        } else {
            double galutinis = (metod == 1 ? s.galVid : s.galMed);
             n = std::snprintf(line, sizeof(line),
                               "%-25s %-25s %15.2f\n",
                               s.pav.c_str(), s.var.c_str(), galutinis);
        }
        
        buffer.append(line, n);

        if (buffer.size() > FLUSH_THRESHOLD) { // flush every ~1MB
            fout.write(buffer.data(), buffer.size());
            buffer.clear();
        }
    }
    // Išvalyti likusį buferį
    if (!buffer.empty()) fout.write(buffer.data(), buffer.size());
    
    fout.close();
}
