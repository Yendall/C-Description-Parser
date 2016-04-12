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
		std::vector < STR > irrelevancy_vector;
		std::vector < STR > uniqueness_vector;
		
		// Filter functions
		bool tokenise_description(const std::string&);
		std::string filter_irrelevancy(const CSV_FIELDS&);
		
		// Determiner words to filter from a string
		static std::string determiners[];
		
		// Top 100 words in the English language (will need to change
		// this for Mandarin)
		static std::string top_100_words[];
};
#endif