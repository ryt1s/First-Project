#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;

struct Student {
    string var;
    string pav;
    vector <int> paz;
    int egz;
    double gal;
};

int main()
{
    vector<Student> studentai;
    char testi;

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
            stud.gal = 0.4 * (double)suma / stud.paz.size() + 0.6 * stud.egz;
        } else {
            stud.gal = 0.6 * stud.egz;
        }

        studentai.push_back(stud);

        cout << "Ar norite ivesti dar viena studenta? (t/n):";
        cin >> testi;
    } while(testi == 't' || testi == 'T');

    //  for (auto i = 0; i<n; i++) {
    //     cout << i+1 << "-asis pazymys: "; cin >> laik_paz;
    //     stud.paz.push_back(laik_paz);
    //     suma+=laik_paz;
    // }
    // cout << "Koks egzamino ivertinimas? "; cin >> stud.egz;
    // stud.gal = 0.4 * double(suma)/double(n) + 0.6 * stud.egz;

    cout << setw(15) << left << "Pavarde"
         << setw(10) << left << "Vardas"
         << "Galutinis (Vid.)" << endl;


    cout << "----------------------------------------" << endl;

//     cout << setw(15) << left << stud.pav
//          << setw(10) << left << stud.var 
//          << fixed << setprecision(2) << stud.gal << endl;
}
