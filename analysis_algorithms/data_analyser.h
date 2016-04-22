#ifndef __DATA_ANALYSER_H
#define __DATA_ANALYSER_H

#include <algorithm>
#include <string>
#include <vector>
#include "../include/csv_parser.hpp"

#define TEXT_DELIMITER " "

bool tokenise_data();
void begin_analysis();
void parse_data(std::string);
CSV_FIELDS parse_csv_file(std::string);
std::string remove_punctuation(std::string);
std::string filter_irrelevancy(const std::string&);

#endif