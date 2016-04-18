#ifndef __FILTER_VECTORS_HPP
#define __FILTER_VECTORS_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

#define TEXT_DELIMITER " "

class Filter_Vectors
{
	public:
		Filter_Vectors() {};
		~Filter_Vectors() {};
		
		// Filter variables
		std::vector <STR> 	irrelevancy_vector;
		std::vector <STR> 	uniqueness_vector;
		std::vector <STR>	top_100_words;
		// Keyword dictionaries
		KEY_VAL_FIELDS 		keyword_map;
		
		
		// Filter functions
		void 			init_description_parsing();
		void			set_top100_vector(CSV_FIELDS&);
		void			set_keyword_map(KEY_VAL_FIELDS&);
		bool			parse_keyword_vectors(const CSV_FIELDS&);
		bool 			tokenise_description(const std::string&);		
		STR 			filter_irrelevancy(const CSV_FIELDS&);	
		CSV_FIELDS		parse_csv_file(STR);
};

// Keyword map setter
void Filter_Vectors::set_keyword_map(KEY_VAL_FIELDS& map)
{
	keyword_map = map;
}

void Filter_Vectors::set_top100_vector(CSV_FIELDS& vector)
{
	top_100_words = vector;
}
#endif