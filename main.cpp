#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::sort;

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



int main()
{
    vector<Student> studentai;
    char testi;

    int metodas;
    cout << "Pasirinkite galutinio balo skaiciavimo metoda:\n";
    cout << "1 - Vidurkis\n";
    cout << "2 - Mediana\n";
    cout << "3 - Abu\n";
    cout << "Jusu pasirinkimas: ";
    cin >> metodas;

    do {
        int suma = 0, laik_paz;
        Student stud;
        cout << "Kuo vardu studentas(-e)?"; cin >> stud.var;
        cout << "Kokia jo (jos) pavarde? "; cin >> stud.pav;
        cout << "Iveskite namu darbu pazymius (0 - baigti):" << endl;

        while(true) {
            cin >> laik_paz;
            if (laik_paz == 0) break;
            
            stud.paz.push_back(laik_paz);
            suma += laik_paz;
        }

        cout << "Koks egzamino ivertinimas? ";
        cin >> stud.egz;
        
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

    cout << setw(15) << left << "Pavarde"
         << setw(10) << left << "Vardas";

    if (metodas == 1)
        cout << "Galutinis (Vid.)";
    else if (metodas == 2)
        cout << "Galutinis (Med.)";
    else
        cout << "Galutinis (Vid.) / Galutinis (Med.)";

    cout << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (const auto& stud : studentai) {
        cout << setw(15) << left << stud.pav
             << setw(10) << left << stud.var;
        if (metodas == 1)
            cout << fixed << setprecision(2) << stud.galVid;
        else if (metodas == 2)
            cout << fixed << setprecision(2) << stud.galMed;
        else
            cout << fixed << setprecision(2) << stud.galVid
                 << setw(15) << left << "" << stud.galMed;
        cout << endl;
    }
}