#include <algorithm>
#include <string>
#include <vector>

#include "csv_parser.hpp"
#include "filter_vectors.hpp"
#include <boost/tokenizer.hpp>

using namespace boost;

// Top 100 words vector
std::vector < STR > top_100_words;

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

int main()
{
    // Declare Parser and vector/map variables
    CSV_Parser csv_parser;
    CSV_FIELDS descriptions;
	CSV_FIELDS top_100;
    STR line;
	
	// Status to track the return value of the CSV Parsers functions
	bool status;
	
    // Open the top 100 words file (subset of determiners)
    std :: ifstream word_file("Data/top_100_words.csv");
    if(word_file.is_open())
    {
        while(getline(word_file, line))
        {
            status = csv_parser.parse_line(line, top_100);
            if(status)
            {
				top_100_words = top_100;
                // display_vector_contents(line,top_100);
                top_100.clear();
            }
            else
            {
                std :: cout << "Error encountered while parsing the input line\n";
            }
        }
    }
	
    // Open the test case CSV file (subset of descriptions)
    std :: ifstream description_file("Data/Descriptions.csv");
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

    return 0;
}