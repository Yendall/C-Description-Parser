#ifndef __FILTER_VECTORS_HPP
#define __FILTER_VECTORS_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "csv_parser.hpp"

#define TEXT_DELIMITER " "

class Filter_Vectors
{
	public:
		Filter_Vectors() {};
		~Filter_Vectors() {};
		
		// Filter functions
		void 			init_description_parsing();;
		bool			parse_keyword_vectors(const CSV_FIELDS&);
		bool 			tokenise_description(const std::string&);		
		STR 			filter_irrelevancy(const CSV_FIELDS&);	
		CSV_FIELDS		parse_csv_file(STR);
};

#endif