#include "data_mapper.h"
#include <boost/tokenizer.hpp>

// Set Identifier
std::string set_descriptor;
// Parent set for holding data
std::vector<STR> parent_set;
// Child map for holding data and frequency
std::map<STR,int> child_map;

// Fetch the cosine similarity between two data sets
// @return: Cosine similarity value of the two sets
float fetch_cosine()
{
    // Define two data sets (these are just examples)
    std::vector<std::string> first= {"Torquay","beach","wonderful","beautiful"};
    std::vector<std::string> second = {"beach","beautiful","scenery","adventure"};
    int numerator = 0;
    int denominator = 0;
    
    // Intersection holder to be populated with a back inserter
    std::vector<std::string> intersection;
    
    // Sort the vectors for comparison
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    // Compute the intersection of the two sets
    std::set_intersection(first.begin(),first.end(),
                          second.begin(),second.end(),back_inserter(intersection));
    
    // Compute the numerator - size of the intersection of sets
    numerator = intersection.size();
    // Compute the denominator - dot product of the sets
    denominator = std::sqrt(first.size()) * std::sqrt(second.size());
    
    // If the denominator confirms there is a relationship
    if(denominator > 0)
    {
        return float(numerator) / denominator;
    }
    
    // There is no similarity between the sets
    return 0.0;
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
    float cosine_similarity;
    // Parse Description Set
    set_descriptor = "description_set";
	parse_set("combined_description_set.csv");
    
    cosine_similarity = fetch_cosine();
    
    std::cout << "Cosine Similarity: " << cosine_similarity << std::endl;
}