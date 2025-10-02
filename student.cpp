#include "student.h"
#include <algorithm>

double skaiciuotiMediana(std::vector<int> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 1) return paz[n / 2];
    return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
}

void skaiciuotiGalutinius(Student& stud) {
    int suma = 0;
    for (int nd : stud.paz) suma += nd;
    stud.galVid = stud.paz.empty() ? 0.6 * stud.egz : 0.4 * (double)suma / stud.paz.size() + 0.6 * stud.egz;
    stud.galMed = stud.paz.empty() ? 0.6 * stud.egz : 0.4 * skaiciuotiMediana(stud.paz) + 0.6 * stud.egz;
}
