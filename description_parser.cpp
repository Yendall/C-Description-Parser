#include <algorithm>
#include <string>
#include "csv_parser.hpp"
#include "filter_vectors.hpp"
#include <boost/tokenizer.hpp>

using namespace boost;

std::string Filter_Vectors::determiners[] =
{
    "a","at","an","and","any","another","by","be","other","do","what",
    "the","my","your","his","her","if","its","is","i'll","I","our","of","or",
    "on","their","this","whose","this","that","these","those","too","to","you",
    "which","with","why"
};

std::string Filter_Vectors::top_100_words[] =
{
    "be", "and", "of", "in", "to", "have", "it", "I", "for", "you", "he", "with", "on", "do", "say", "they", "at", "but", "we", "from", "not", "by", "she", "or", "as", "go", "can", "who", "get", "if", "would", "make", "about", "know", "will", "up", "one", "time", "year", "so", "think", "when", "them", "me", "people", "take", "out", "into", "just", "see", "him", "come", "could", "now", "than", "like", "how", "then", "two", "want", "way", "look", "first", "also", "new", "because", "day", "use", "man", "find", "here", "thing", "give", "well", "only", "tell", "very", "even", "back", "any", "good", "woman", "through", "us", "life", "child", "work", "down", "may", "after", "should", "call", "world", "over", "school", "still", "try", "last", "ask", "need"
};

// Filters the bag of words by removing irrelevant words and concatenating
// the words back into a description.
std::string filter_irrelevancy(const std::string& token)
{
    std::string new_word;
    new_word = token;
    
    // Transform word to lowercase for easy comparison
    std::transform(new_word.begin(), new_word.end(), new_word.begin(), ::tolower);
    
    for(const auto& determiner : Filter_Vectors::determiners)
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
    
    // filter_irrelevancy(bag_of_words);
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
    
    CSV_Parser csv_parser;
    CSV_FIELDS output_fields;
    STR line;
    bool status;
    
    // Open the test case CSV file
    std :: ifstream test_file("Data/data.csv");
    if(test_file.is_open())
    {
        while(getline(test_file, line))
        {
            status = csv_parser.parse_line(line, output_fields);
            
            if(status)
            {
                tokenise_description(output_fields);
                // display_vector_contents(line,output_fields);
                output_fields.clear();
            }
            else
            {
                std :: cout << "Error encountered while parsing the input line\n";
            }
        }
    }
    
    // Ignore the header and parse the information into an output map
    line = "description";
    CSV_FIELDS header;
    
    // Populate the header
    header.push_back("description");
    KEY_VAL_FIELDS output_map;
    status = csv_parser.parse_line(line, header, output_map);
    if(status)
    {
        // Print contents to the screen
        // display_map_contents(line, output_map);
    }
    else
    {
        std :: cout << "Error encountered while parsing the input line\n";
    }
    return 0;
}
