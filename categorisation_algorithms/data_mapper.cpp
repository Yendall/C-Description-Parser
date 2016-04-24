#include "data_mapper.h"
#include <boost/tokenizer.hpp>

// Set Identifier
std::string set_descriptor;
// Parent set for holding data
std::vector<STR> parent_set;
// Child map for holding data and frequency
std::map<STR,int> child_map;


// Compare two sets and compute the frequency
// @return: void
void compare_sets()
{
    
}

// Parse the parent set for comparison
// @return: void
void parse_set(std::string file)
{
    // Parser and vector/map variables
    STR         line;
	bool 		status;
	int			index_ptr;
	CSV_Parser 	csv_parser;
    CSV_FIELDS 	data_set;
    
	index_ptr = 0;
	
    // Open the data CSV file
    std :: ifstream data_file("data/"+file);
    if(data_file.is_open())
    {
        while(getline(data_file, line))
        {
            status = csv_parser.parse_line(line, data_set);
            
            if(!status)
            {
				std :: cout << "Error encountered while parsing the input line\n";
            }
        }
    }
	
	// Create data_map
	for(const auto& data : data_set)
	{
		parent_set.push_back(data);
	}
}

// Main function
// @return: void
void begin_categorisation()
{
    // Parse Description Set
    set_descriptor = "description_set";
	parse_set("combined_description_set.csv");
}