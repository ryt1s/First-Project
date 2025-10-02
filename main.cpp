#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "student.h"
#include "io.h"
using namespace std;

int main() {
    srand(time(0));
    vector<Student> studentai;

    int pasirinkimas;
    cout << "Pasirinkite veiksma:\n1 - Ivesti / generuoti / nuskaityti studentus\n"
            "2 - Sugeneruoti testinius failus (1000, 10k, 100k, 1M, 10M)\nJusu pasirinkimas: ";
    cin >> pasirinkimas;

    if (pasirinkimas == 2) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        for (int dydis : dydziai) generuotiFaila("studentai" + to_string(dydis) + ".txt", dydis, 5);
        return 0;
    }

    int metodas;
    cout << "Pasirinkite galutinio balo skaiciavimo metoda:\n1 - Vidurkis\n2 - Mediana\n3 - Abu\n";
    cin >> metodas;

    int ivestis;
    cout << "1 - Ivesti ranka\n2 - Generuoti atsitiktinai\n3 - Nuskaityti is failo (kursiokai.txt)\n";
    cin >> ivestis;

    if (ivestis == 3) nuskaitytiIsFailo("kursiokai.txt", studentai);
    else {
        char testi;
        do {
            Student stud;
            cout << "Kuo vardu studentas(-e)? "; cin >> stud.var;
            cout << "Kokia jo (jos) pavarde? "; cin >> stud.pav;

            if (ivestis == 1) {
                int paz;
                while (true) {
                    paz = inputSkaicius("Iveskite namu darbo bala (0 baigti): ", 0, 10);
                    if (paz == 0) break;
                    stud.paz.push_back(paz);
                }
                stud.egz = inputSkaicius("Koks egzamino ivertinimas? ", 1, 10);
            } else {
                int kiek = rand() % 10 + 1;
                cout << "Sugeneruoti " << kiek << " namu darbu pazymiai: ";
                for (int i = 0; i < kiek; i++) {
                    int paz = rand() % 10 + 1;
                    stud.paz.push_back(paz);
                    cout << paz << " ";
                }
                cout << "\n";
                stud.egz = rand() % 10 + 1;
                cout << "Sugeneruotas egzamino ivertinimas: " << stud.egz << "\n";
            }

            skaiciuotiGalutinius(stud);
            studentai.push_back(stud);

            cout << "Ar norite ivesti dar viena studenta? (t/n): ";
            cin >> testi;
        } while (testi == 't' || testi == 'T');
    }

    sort(studentai.begin(), studentai.end(),
         [](const Student& a, const Student& b) { return a.pav < b.pav; });

    // Padalijame į grupes
    vector<Student> vargsiukai, kietakiai;
    for (auto& stud : studentai) {
        double gal = (metodas == 2 ? stud.galMed : stud.galVid);
        if (gal < 5.0) vargsiukai.push_back(stud);
        else kietakiai.push_back(stud);
    }

    issaugotiIFaila("vargsiukai.txt", vargsiukai, metodas);
    issaugotiIFaila("kietakiai.txt", kietakiai, metodas);

    cout << "\nRezultatai issaugoti i failus: vargsiukai.txt ir kietakiai.txt\n";
    return 0;
}
