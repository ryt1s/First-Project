#include "student.h"
#include <algorithm>

double skaiciuotiMediana(std::vector<int> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 1) return paz[n/2];
    return (paz[n/2-1] + paz[n/2]) / 2.0;
}

void skaiciuotiGalutinius(Student& stud) {
    if (stud.paz.empty()) {
        stud.galVid = 0.6 * stud.egz;
        stud.galMed = 0.6 * stud.egz;
    } else {
        double sum = 0;
        for (int p : stud.paz) sum += p;
        stud.galVid = 0.4 * (sum / stud.paz.size()) + 0.6 * stud.egz;
        stud.galMed = 0.4 * skaiciuotiMediana(stud.paz) + 0.6 * stud.egz;
    }
}
