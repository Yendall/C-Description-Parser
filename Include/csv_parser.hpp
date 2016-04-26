/*
    A Simple CSV Parser
    Inspired by - The Practice of Programming by Rob Pike and Brian Kernighan
*/

#ifndef __CSV_PARSER_HPP
#define __CSV_PARSER_HPP

// Define your header files here
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

// Place to put your constants
#define CSV_DELIMITER ","
#define CSV_QUOTE '"'

// Place for type definitions
typedef std :: string STR;
typedef std :: vector < STR > CSV_FIELDS;
typedef std :: map < STR, STR > KEY_VAL_FIELDS;
typedef std :: pair < STR, STR > MAP_ENTRY;
typedef std :: vector < STR > :: iterator VECTOR_ITR;
typedef std :: vector < STR > :: const_iterator CONST_VECTOR_ITR;
typedef std :: map < STR, STR > :: iterator MAP_ITR;
typedef std :: map < STR, CSV_FIELDS > :: iterator MAP_ITR_VEC;
typedef std :: map <int,std::map<STR,int> > :: iterator MAP_ITR_MAP;
typedef std :: map < STR, int > :: iterator MAP_ITR_STRINT;
typedef std :: map < STR, STR > :: const_iterator CONST_MAP_ITR;
typedef std :: map < int, STR > :: const_iterator CONST_MAP_ITR_INT;
typedef std :: map < STR, int > :: const_iterator CONST_MAP_ITR_STRINT;

class CSV_Parser
{
    public:
        CSV_Parser() {};
        ~CSV_Parser() {};
        bool parse_line(const STR&, CSV_FIELDS&);
        bool parse_line(const STR&, CSV_FIELDS&, KEY_VAL_FIELDS&);
        

    private:
        bool parse(const STR&, CSV_FIELDS&);
        int parse_quoted_fields(const STR&, STR&, int&);
        int parse_normal_fields(const STR&, STR&, int&);
};

#endif
