#include "data_analyser.h"
#include <boost/tokenizer.hpp>

using namespace boost;

// Set Identifier
std::string set_identifier;
// Data Map
std::map <int,STR> data_map;
// Condensed Data Map
std::map <int,STR> condensed_map;
// Combined Set
std::vector <STR> combined_set;
// Determiner Set
std::vector <STR> determiner_set;


// Output the data into new condensed files
// @return: void
void output_data()
{
    // Constant map <int, string> interator
    CONST_MAP_ITR_INT it_con = condensed_map.begin();
    
    // Create the output file based on the set_identifier
    std::ofstream condensed_outputCSV("data/condensed_" + set_identifier + ".csv");
    std::ofstream combined_outputCSV("data/combined_" + set_identifier + ".csv");
    
    for (; it_con != condensed_map.end(); ++it_con)
    {
        condensed_outputCSV << "\"" << it_con->second << "\"" << ",";
    }
    
    for(const auto& word : combined_set)
    {
        combined_outputCSV << "\"" << word << "\"" << ",";
    }
    
    condensed_outputCSV.close();
    combined_outputCSV.close();
    
    condensed_map.clear();
    combined_set.clear();
}

// Checks if string exists in the combined set
// @return: Boolean value denoting existance
bool string_exists(std::string string)
{
    for(auto& word : combined_set)
    {
        if(word.compare(string) == 0)
        {
            return true;
        }
    }
    return false;
}

// Removes punctuation from string
// @return: Filtered sentence as a string
std::string remove_punctuation(std::string string)
{
    // Result string
    std::string result;
    
    // Using remove_copy_if func to remove ispunct occurences
    std::remove_copy_if(string.begin(), string.end(),            
                        std::back_inserter(result),       
                        std::ptr_fun<int, int>(&std::ispunct)  
                       );
    return result;
}

// Filters the bag of words by removing irrelevant words and concatenating
// the words back into a structured sentence
// @return: Filtered sentence as a string
std::string filter_irrelevancy(const std::string& token)
{
    std::string new_word;
    new_word = token;
    
    // Transform word to lowercase for easy comparison
    std::transform(new_word.begin(), new_word.end(), new_word.begin(), ::tolower);
    
    for(const auto& determiner : determiner_set)
    {
        if(new_word.compare(determiner) == 0)
        {
            new_word = "";
        } 
    }
    
    return new_word;
}

// Tokenises strings in a data map, filtering them through a determiner
// map creating a condensed sentence construction
// @return: boolean denoting success status
bool tokenise_data()
{
    // Identifier for description map
	int index_ptr;
    // Define sentence construct and filtered word return strings
    std::string sentence_construct;
    std::string filtered_word;
    std::string new_token;
	// Constant map <int, string> interator
    CONST_MAP_ITR_INT it = data_map.begin();

	// Loop through the descriptions map
    for (; it != data_map.end(); ++it)
    {
		// Set index pointer
		index_ptr = it->first;
        
		// Separate the sentence into tokens and filter irrelevant words
        char_separator<char> sep(TEXT_DELIMITER);
        tokenizer<char_separator<char> > tokens(it->second,sep);
        
        // Check each token against irrelevancy vector and construct a 
        // well formed sentence of relevant words
        for (auto& token : tokens)
        {
            new_token = remove_punctuation(token);
            filtered_word = filter_irrelevancy(new_token);
            if(filtered_word.compare("") != 0)
            {
                if(!string_exists(new_token))
                {
                    combined_set.push_back(new_token);
                }
                sentence_construct = sentence_construct + " " + filtered_word;
            }
        }
        
        condensed_map[index_ptr] = sentence_construct;
		sentence_construct.clear();
    }
    
    // Output the new data to CSV files
    output_data();
    return true;
}

// Parse CSV File given a path
// @return: Vector of CSV data
CSV_FIELDS parse_csv_file(std::string path)
{
	CSV_Parser csv_parser;
	CSV_FIELDS csv_return;
	CSV_FIELDS csv_temp;
	STR line;
	
	bool status;
    // Open determiners file (subset of determiners)
    std :: ifstream csv_file(path);
    if(csv_file.is_open())
    {
        while(getline(csv_file, line))
        {
            status = csv_parser.parse_line(line, csv_temp);
            if(status)
            {
				csv_return = csv_temp;
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

// Initial CSV parsing helper function
// @return: void
void parse_data(std::string file)
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
		data_map[index_ptr] = data;
		index_ptr++;
	}
	
	// Begin tokenising
    tokenise_data();
}

// Main function
// @return: void
void begin_analysis()
{
	// Begin parsing the determiner set
	determiner_set = parse_csv_file("data/determiner_set.csv");
    
	// Parse Description Set
    set_identifier = "description_set";
	parse_data("description_set.csv");
    
    // Parse Title Set
    set_identifier = "title_set";
    parse_data("title_set.csv");
    
    // Parse Activity Set
    set_identifier = "activity_set";
    parse_data("activity_set.csv"); 
}