#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include "student.h"

void nuskaitytiIsFailo(const std::string& filename, std::vector<Student>& studentai);
int inputSkaicius(const std::string& pranesimas, int min, int max);
void generuotiFaila(const std::string& filename, int kiekStudentu, int kiekNd);
void issaugotiIFaila(const std::string& filename, const std::vector<Student>& studentai, int metodas);

#endif
