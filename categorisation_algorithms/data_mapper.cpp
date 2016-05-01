#include "data_mapper.h"
#include <boost/tokenizer.hpp>

// Set Identifier
std::string set_descriptor;
// Parent set for holding data
std::map<int,STR> parent_map;
// Child map for holding data and frequency
std::map<int,std::map<int,int> > child_map;

void loop_map()
{
    typedef std::map< int, int>             inner_t;
    typedef std::map< int, inner_t >        outer_t;
    typedef outer_t::iterator               outer_iter_t;
    typedef inner_t::iterator               inner_iter_t;
    
    int pointer = 0;
    for(outer_iter_t o = child_map.begin(); o != child_map.end(); ++o )
    {
        for(inner_iter_t i = o->second.begin(); i != o->second.end(); ++i)
        {
            std::cout << o->first << " == " << i->second << std::endl;
        }
        
    }   
}

// Fetch the cosine similarity between two data sets
// @return: Cosine similarity value of the two sets
float fetch_cosine()
{
    // Define two data sets (these are just examples)
    std::vector<std::string> first  =   {"globally","recognised","hotspot","unique","streetart", "melbourne" };
    
    std::vector<std::string> second =   {"through","experience", "uncover", "city", "much", "hidden", "plain", "sight", "pleasure", "show", "others", "place", "call", "home","melbourne"};
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
    int         index_dup;
	CSV_Parser 	csv_parser;
    CSV_FIELDS 	data_set;
    
    CONST_MAP_ITR_INT it;
    
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
		parent_map[index_ptr] = data;
        
        index_ptr += 1;
	}
    
    // Populate child map with parent_map indices 
    index_ptr = 0;
    it = parent_map.begin();
    
    for(; it != parent_map.end(); ++it)
    {
        for(int i=0; i < data_set.size(); i++)
        {
            child_map[index_ptr][i] = 0.0;
            
        }
        
        index_ptr += 1;
    }
}

// Main function
// @return: void
void begin_categorisation()
{
    float cosine_similarity;
    
    // Parse Description Set
    set_descriptor = "description_set";
	parse_set("condensed_description_set.csv");
    
    cosine_similarity = fetch_cosine();
    
    std::cout << "Cosine: " << cosine_similarity << std::endl;

    // loop_map();
    
}