#pragma once

#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>

using std::string;
using std::vector;

namespace fmCommon
{
    class StringX
    {
        public:
            vector<string> split(const string& s, const char& c);

        
            /*
            std::string split implementation by using delimeter as an another string
            */
            std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter);
           

            void  findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr);
            

                        /*
            *Find all positions of the a SubString in given String
            */
            void findAllOccurances(std::vector<size_t> & vec, std::string data, std::string toSearch);

            size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos);


            string removeEnd(std::string s,  const char& EndDelimiter);

            string removeStart(std::string s,  const char& StartDelimiter);

            string removeDelimiter(std::string& s, const char& StartDelimiter, const char& EndDelimiter);


            bool to_bool(std::string str);

            std::string to_Upper(std::string str);

            std::string to_Lower(std::string str);

            bool startsWith(std::string mainStr, std::string toMatch);
           
                 /*
            * Case Insensitive Implementation of startsWith()
            * It checks if the string 'mainStr' starts with given string 'toMatch'
            */
            bool startsWithCaseInsensitive(std::string mainStr, std::string toMatch);
          
                       /*
            * Case Sensitive Implementation of endsWith()
            * It checks if the string 'mainStr' ends with given string 'toMatch'
            */
            bool endsWith(const std::string &mainStr, const std::string &toMatch);

                       /*
            * Case Insensitive Implementation of endsWith()
            * It checks if the string 'mainStr' ends with given string 'toMatch'
            */
            bool endsWithCaseInsensitive(std::string mainStr, std::string toMatch);
          
           /*
            * Erase all Occurrences of given substring from main string.
            */
            void eraseAllSubStr(std::string & mainStr, const std::string & toErase);
           
    };
    
}