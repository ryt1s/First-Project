#ifndef IO_H
#define IO_H

#include "student.h"
#include <vector>
#include <string>

void nuskaitytiIsFailo(const std::string& filename, std::vector<Student>& studentai);
void issaugotiIFaila(const std::string& filename, const std::vector<Student>& studentai, int metod);
void generuotiFaila(const std::string& filename, int kiekStudentu, int kiekNd);
int inputSkaicius(const std::string& pranesimas, int min, int max);

#endif
