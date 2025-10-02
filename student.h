#pragma once
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

// Function declarations
double skaiciuotiMediana(std::vector<int> paz);
void skaiciuotiGalutinius(Student& stud);
