#include "categorisation_algorithms/data_mapper.h"
#include "pre-processing_algorithms/data_analyser.h"

void print_usage()
{
    std::cerr 
		      << "\nUsage: ./data_parser\n\n"
		      << "--p\tPre-Process Data\n" 
		      << "--c\tCategorise Data\n" 
		      << "\t\tNote: Ensure Data has been pre-processed first\n"
		      << "--pc\tPre-Process and Categorise Data\n"; 
}

// Main function
// @return: int denoting state of application
int main(int argc, char **argv)
{
    if(argc < 2 || argc > 2)
    {
        print_usage();
    }
    else
    {
        std::vector<std::string> arguments(argv+1,argv+argc);
        
        if(arguments[0].compare("--p") == 0)
        {
            std::cout << "Pre-Processing Data\tPlease Wait..." << std::endl;
            // Begin running pre-processing algorithms
            begin_analysis();
            std::cout << "Pre-Processing Data\tComplete" << std::endl;
        }
        else if(arguments[0].compare("--c") == 0)
        {
            std::cout << "Categorising Data\tPlease Wait..." << std::endl;
            // Begin running categorisation algorithms
            begin_categorisation();
            std::cout << "Categorising Data\tComplete" << std::endl;
        }
        else if(arguments[0].compare("--pc") == 0)
        {
            std::cout << "Pre-Processing Data\tPlease Wait..." << std::endl;
            // Begin running pre-processing algorithms
            begin_analysis();
            std::cout << "Pre-Processing Data\tComplete" << std::endl;
            std::cout << "Categorising Data\tPlease Wait..." << std::endl;
            // Begin running categorisation algorithms
            begin_categorisation();
            std::cout << "Categorising Data\tComplete" << std::endl;
        }
    }

    return 0;
}