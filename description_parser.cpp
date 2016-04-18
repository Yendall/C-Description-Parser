#include <algorithm>
#include <string>
#include <vector>

#include "Include/filter_vectors.hpp"
#include <boost/tokenizer.hpp>

using namespace boost;

// Vector of label names
std::vector <STR> label_vector;
// Top 100 words vector
std::vector <STR> top_100_words;
// Map of labels
std::map <STR,std::vector<STR> > label_map;	
 
// Filters the bag of words by removing irrelevant words and concatenating
// the words back into a description.
std::string filter_irrelevancy(const std::string& token)
{
    std::string new_word;
    new_word = token;
    
    // Transform word to lowercase for easy comparison
    std::transform(new_word.begin(), new_word.end(), new_word.begin(), ::tolower);
    
    for(const auto& determiner : top_100_words)
    {
        if(new_word.compare(determiner) == 0)
        {
            new_word = "";
        } 
    }
    return new_word;
}

// Tokenises the string into a bag of words. The bag of words must maintain
// order so the description is somewhat linear once it's been manipulated
bool tokenise_description(const CSV_FIELDS& descriptions)
{
    
    // Define a Bag of Words for the description
    std::string sentence_construct;
    std::string filtered_word;
    CSV_FIELDS bag_of_words;
    KEY_VAL_FIELDS bag_of_words_map;
    
    int iterator = 0;
    
    for(const auto& sentence : descriptions)
    {
        char_separator<char> sep(TEXT_DELIMITER);
        tokenizer<char_separator<char> > tokens(sentence,sep);
        
        for (const auto& token : tokens)
        {
            filtered_word = filter_irrelevancy(token);
            if(filtered_word.compare("") != 0)
            {
                sentence_construct = sentence_construct + " " + filtered_word;
            }
        }
        std::cout << sentence_construct << std::endl;
        std::cout << std::endl << std::endl;
        std::cout << "------NEW DESCRIPTION------" << std::endl;
        sentence_construct.clear();
    }
    // Define separator constants which will split the description
    
    return false;
}


// Displays the entire CSV file within the vector as one long string
void display_vector_contents(const STR& input_line, const CSV_FIELDS& output_fields)
{
    CONST_VECTOR_ITR it = output_fields.begin();
    int i = 0;
    
    for( ; it != output_fields.end(); ++it)
    {
        std :: cout << "Field [" << i++ << "] - " << *it << "\n";
    }
}

// Displays the key->pair mapping of the CSV file
void display_map_contents(const STR& input_line, const KEY_VAL_FIELDS& output_map)
{
    CONST_MAP_ITR it = output_map.begin();
    for (; it != output_map.end(); ++it)
    {
        std :: cout << "Field[ " << it->first << " ] : " << it->second << "\n";
    }
}
CSV_FIELDS parse_csv_file(STR path)
{
	CSV_Parser csv_parser;
	CSV_FIELDS csv_return;
	CSV_FIELDS csv_temp;
	STR line;
	
	bool status;
    // Open the top 100 words file (subset of determiners)
    std :: ifstream csv_file(path);
    if(csv_file.is_open())
    {
        while(getline(csv_file, line))
        {
            status = csv_parser.parse_line(line, csv_temp);
            if(status)
            {
				csv_return = csv_temp;
                // debug: display_vector_contents(line,csv_return);
                csv_temp.clear();
            }
            else
            {
                std :: cout << "Error encountered while parsing the input line\n";
            }
        }
    }
	
	return csv_return;
}

void init_description_parsing()
{
    // Declare Parser and vector/map variables
    STR 		line;
	bool 		status;
	CSV_Parser 	csv_parser;
    CSV_FIELDS 	descriptions;
	
    // Open the description CSV file (subset of descriptions)
    std :: ifstream description_file("Data/Description_Set.csv");
    if(description_file.is_open())
    {
        while(getline(description_file, line))
        {
            status = csv_parser.parse_line(line, descriptions);
            
            if(status)
            {
                tokenise_description(descriptions);
                // display_vector_contents(line,descriptions);
                descriptions.clear();
            }
            else
            {
                std :: cout << "Error encountered while parsing the input line\n";
            }
        }
    }
}
int main()
{
	// Set top 100 words
	top_100_words = parse_csv_file("Data/top_100_words.csv");
	// Set label categories
	label_vector = parse_csv_file("Data/label_categories.csv");
	// Map label keywords to label
	STR path;
	std::vector<STR> labels;
	
	for(const auto& label : label_vector)
	{
		// Set path for CSV data and insert value at the
		// map key mirrored from the label vector
		path = "Data/Labels/" + label + ".csv";
		labels = parse_csv_file(path);
		label_map[label] = labels;
	}
	
	// Begin parsing the description
	init_description_parsing();
	
    return 0;
}