#ifndef __DATA_MAPPER_H
#define __DATA_MAPPER_H

#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include "../include/csv_parser.hpp"

float fetch_cosine();
void begin_categorisation();
CSV_FIELDS parse_csv_file(std::string);

#endif