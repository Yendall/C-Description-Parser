#include <algorithm>
#include <string>
#include <vector>

#include "include/filter_vectors.hpp"
#include <boost/tokenizer.hpp>

using namespace boost;

// Vector of label names
std::vector <STR> label_vector;
// Top 100 words vector
std::vector <STR> top_100_words;
// Description identity map
std::map <int,STR> descriptions_map;
// Map of labels
std::map <STR,std::vector<STR> > label_map;
// Map of descriptions and map of frequencies
std::map <int,std::map<STR,int> > frequency_vector;

void display_frequency()
{
    MAP_ITR_MAP it = frequency_vector.begin();
	std::cout << frequency_vector.size() << std::endl;
	for(; it != frequency_vector.end(); ++it)
	{
		std::cout << "Description : " << descriptions_map[it->first] << std::endl;
		CONST_MAP_ITR_STRINT it_map = it->second.begin();
		for(; it_map != it->second.end(); ++it_map)
		{
			std::cout << "Label: " << it_map->first << " Frequency: " << it_map->second << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
		}
	}
}

// Remove punctuation from string and return
/* STR& remove_punctuation(STR& string)
{
    char punctuation[] = "()-,:;.!?+'\% ";
    
    for(const auto& mark : punctuation)
    {
        string.erase(std::remove(string.begin(), string.end(), mark), string.end());
    }
    
    return string;
} */

// Generates frequency of occuring words in certain tags
void category_frequency(int index_ptr, STR& sentence_construct)
{
    char_separator<char> sep(TEXT_DELIMITER);
    tokenizer<char_separator<char> > tokens(sentence_construct,sep);
	
	MAP_ITR_VEC it = label_map.begin();
	
    
	// Loop through label vector and compare the sentence tokens to each word
	// and update frequency
	for (; it != label_map.end(); ++it)
	{	
		for(const auto& label_word : it->second)
		{
			for(const auto& token : tokens)
			{
                
                // token = remove_punctuation(token);
                // std::cout << "Reaches here with token: " << token << std::endl;
				if(token.compare(label_word) == 0)
				{
					// std::cout << "Tokens are: " << token << std::endl;
					frequency_vector[index_ptr][it->first] += 1;
                    std::cout << "Label Word: " << label_word << std::endl;
                    std::cout << frequency_vector[index_ptr][it->first] << std::endl;
				}
			}
		}
	}
}

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
bool tokenise_data()
{
    // Identifier for description map
	int index_ptr;
    // Define sentence construct and filtered word return strings
    std::string sentence_construct;
    std::string filtered_word;
	
	// Constant map <int, string> interator
    CONST_MAP_ITR_INT it = descriptions_map.begin();

	// Loop through the descriptions map
    for (; it != descriptions_map.end(); ++it)
    {
		// Set index pointer
		index_ptr = it->first;
		// Separate the sentence into tokens and filter irrelevant words
        char_separator<char> sep(TEXT_DELIMITER);
        tokenizer<char_separator<char> > tokens(it->second,sep);
        
        for (const auto& token : tokens)
        {
            filtered_word = filter_irrelevancy(token);
            if(filtered_word.compare("") != 0)
            {
                sentence_construct = sentence_construct + " " + filtered_word;
            }
        }

		category_frequency(index_ptr, sentence_construct);
		sentence_construct.clear();
    }
    
    return false;
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

void parse_data()
{
    // Declare Parser and vector/map variables
    STR 		line;
	bool 		status;
	int			index_ptr;
	CSV_Parser 	csv_parser;
    CSV_FIELDS 	descriptions;
	
	index_ptr = 0;
	
    // Open the description CSV file (subset of descriptions)
    std :: ifstream description_file("Data/Description_Set.csv");
    if(description_file.is_open())
    {
        while(getline(description_file, line))
        {
            status = csv_parser.parse_line(line, descriptions);
            
            if(!status)
            {
				std :: cout << "Error encountered while parsing the input line\n";
            }
        }
    }
	
	// Create descriptions_map
	for(const auto& sentence : descriptions)
	{
		descriptions_map[index_ptr] = sentence;
		index_ptr++;
	}
	
	// Begin tokenising
    tokenise_data();
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
	parse_data();
    display_frequency();
	
    return 0;
}