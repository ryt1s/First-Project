#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::cout; using std::cin;
using std::string; using std::vector;
using std::endl; using std::setw;
using std::left; using std::fixed;
using std::setprecision; using std::sort;
using std::getline; using std::ifstream;
using std::istringstream;

struct Student {
    string var;
    string pav;
    vector <int> paz;
    int egz;
    double galVid;
    double galMed;
};

double skaiciuotiMediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 1)
        return paz[n / 2];
    else
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
}

void skaiciuotiGalutinius(Student& stud) {
    int suma = 0;
    for (int nd : stud.paz) suma += nd;
    stud.galVid = stud.paz.empty() ? 0.6 * stud.egz : 0.4 * (double)suma / stud.paz.size() + 0.6 * stud.egz;
    stud.galMed = stud.paz.empty() ? 0.6 * stud.egz : 0.4 * skaiciuotiMediana(stud.paz) + 0.6 * stud.egz;
}

void nuskaitytiIsFailo(const string& filename, vector<Student>& studentai) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Nepavyko atidaryti failo: " << filename << endl;
        return;
    }

    string headerLine;
    getline(fin, headerLine); 

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        Student stud;
        if (!(iss >> stud.pav >> stud.var)) {
            cout << "Klaida faile: nepavyko nuskaityti vardo arba pavardes." << endl;
            continue; // praleidžiame blogą įrašą
        }

        vector<int> paz;
        int balas;
        bool klaida = false;

        while (iss >> balas) {
            if (balas < 0 || balas > 10) {
                cout << "Klaida faile studentui " << stud.pav << " " << stud.var 
                     << ": balas ne intervale 0-10.\n";
                klaida = true;
                break;
            }
            paz.push_back(balas);
        }

        if (klaida || paz.empty()) continue; // praleidžiame blogą įraš

        stud.egz = paz.back(); paz.pop_back();
        stud.paz = paz;
        skaiciuotiGalutinius(stud);
        studentai.push_back(stud);
    }

    fin.close();
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

int main()
{
    srand(time(0));
    vector<Student> studentai;
    char testi;

    int metodas;
    cout << "Pasirinkite galutinio balo skaiciavimo metoda:\n";
    cout << "1 - Vidurkis\n";
    cout << "2 - Mediana\n";
    cout << "3 - Abu\n";
    cout << "Jusu pasirinkimas: ";
    cin >> metodas;

    int pasirinkimas;
    cout << "Pasirinkite duomenu ivedimo buda:\n";
    cout << "1 - Ivesti ranka\n";
    cout << "2 - Generuoti atsitiktinai\n";
    cout << "3 - Nuskaityti is failo (kursiokai.txt)\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pasirinkimas;

    if (pasirinkimas == 3) {
        nuskaitytiIsFailo("kursiokai.txt", studentai);
    } else{

    do {
        int suma = 0, laik_paz;
        Student stud;
        cout << "Kuo vardu studentas(-e)?"; cin >> stud.var;
        cout << "Kokia jo (jos) pavarde? "; cin >> stud.pav;

        if (pasirinkimas == 1){
            while(true) {
                laik_paz = inputSkaicius("Iveskite namu darbo bala (0 baigti): ", 0, 10); 
                if (laik_paz == 0) break;
                
                stud.paz.push_back(laik_paz);
                suma += laik_paz;
            }
            
            stud.egz = inputSkaicius("Koks egzamino ivertinimas? ", 1, 10);
        } else {
            int kiek = rand() % 10 + 1;
            cout << "Sugeneruoti " << kiek << " namu darbu pazymiai: ";
            for (int i = 0; i < kiek; i++) {
                int paz = rand() % 10 + 1;
                stud.paz.push_back(paz);
                suma += paz;
                cout << paz << " ";
            }
            cout << endl;
            stud.egz = rand() % 10 + 1; 
            cout << "Sugeneruotas egzamino ivertinimas: " << stud.egz << endl;
        }
        
        if (!stud.paz.empty()) {
            stud.galVid = 0.4 * (double)suma / stud.paz.size() + 0.6 * stud.egz;
            stud.galMed = 0.4 * skaiciuotiMediana(stud.paz) + 0.6 * stud.egz;
        } else {
            stud.galVid = 0.6 * stud.egz;
            stud.galMed = 0.6 * stud.egz;
        }

        studentai.push_back(stud);

        cout << "Ar norite ivesti dar viena studenta? (t/n):";
        cin >> testi;
    } while(testi == 't' || testi == 'T');
 }

    cout << setw(15) << left << "Pavarde"
         << setw(10) << left << "Vardas";

    if (metodas == 1)
        cout << "Galutinis (Vid.)";
    else if (metodas == 2)
        cout << "Galutinis (Med.)";
    else {
        cout << "Galutinis (Vid.)" << "  ";
        cout << "Galutinis (Med.)";
    }

    cout << endl;
    cout << "--------------------------------------------------------------" << endl;

    sort(studentai.begin(), studentai.end(), [](const Student& first, const Student& second){
        return first.pav < second.pav;
    });
    for (const auto& stud : studentai) {
        cout << setw(15) << left << stud.pav
             << setw(10) << left << stud.var;
        if (metodas == 1)
            cout << fixed << setprecision(2) << stud.galVid;
        else if (metodas == 2)
            cout << fixed << setprecision(2) << stud.galMed;
        else {
            cout << setw(18) << left << fixed << setprecision(2) << stud.galVid;
            cout << setw(17) << left << fixed << setprecision(2) << stud.galMed;
        }

        cout << endl;
    }
}