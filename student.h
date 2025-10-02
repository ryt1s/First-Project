#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>

struct Student {
    std::string var;
    std::string pav;
    std::vector<int> paz;
    int egz;
    double galVid;
    double galMed;
};

// Funkcijos susijusios su studentais
double skaiciuotiMediana(std::vector<int> paz);
void skaiciuotiGalutinius(Student& stud);

#endif
