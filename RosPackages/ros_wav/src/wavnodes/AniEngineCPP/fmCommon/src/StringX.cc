#include <algorithm>
#include <string>
#include <vector>

#include "StringX.h"

using std::string;
using std::vector;

namespace fmCommon
{
            vector<string> StringX::split(const string& s, const char& c)
            {
                string buff{""};
                vector<string> v;
                
                for(auto n:s)
                {
                    if(n != c) buff+=n; else
                    if(n == c && buff != "") { v.push_back(buff); buff = ""; }
                }

                if(buff != "") v.push_back(buff);
                
                return v;
            }

           


            string removeStart(std::string s,  const char& StartDelimiter)
            {
                while (s[0] == StartDelimiter)
                {
                    s.erase(0,1);
                }
                return s;
            }

            string StringX::removeEnd(std::string s,  const char& EndDelimiter)
            {
                while (s[s.size()-1] == EndDelimiter)
                {
                s.erase(s.size()-1,1);
                }

                return s;
            }

            string StringX::removeDelimiter(std::string& s, const char& StartDelimiter, const char& EndDelimiter)
            {
                while (s[0] == StartDelimiter)
                {
                s.erase(0,1);
                }

                while (s[s.size()-1] == EndDelimiter)
                {
                s.erase(s.size()-1,1);
                }

                return s;
            }

            bool StringX::to_bool(std::string str) {
                std::transform(str.begin(), str.end(), str.begin(), ::tolower);
                std::istringstream is(str);
                bool b;
                is >> std::boolalpha >> b;
                return b;
            }

            std::vector<std::string> StringX::split(std::string stringToBeSplitted, std::string delimeter)
            {
                std::vector<std::string> splittedString;
                int startIndex = 0;
                int  endIndex = 0;
                while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
                {
                    std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
                    splittedString.push_back(val);
                    startIndex = endIndex + delimeter.size();
                }
                if(startIndex < stringToBeSplitted.size())
                {
                    std::string val = stringToBeSplitted.substr(startIndex);
                    splittedString.push_back(val);
                }
                return splittedString;
            }



            void  StringX::findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
            {
                // Get the first occurrence
                size_t pos = data.find(toSearch);
                // Repeat till end is reached
                while( pos != std::string::npos)
                {
                    // Replace this occurrence of Sub String
                    data.replace(pos, toSearch.size(), replaceStr);
                    // Get the next occurrence from the current position
                    pos =data.find(toSearch, pos + replaceStr.size());
                }
            }



                        /*
            *Find all positions of the a SubString in given String
            */
            void StringX::findAllOccurances(std::vector<size_t> & vec, std::string data, std::string toSearch)
            {
                // Get the first occurrence
                size_t pos = data.find(toSearch);
                // Repeat till end is reached
                while( pos != std::string::npos)
                {
                    // Add position to the vector
                    vec.push_back(pos);
                    // Get the next occurrence from the current position
                    pos =data.find(toSearch, pos + toSearch.size());
                }
            }

            size_t StringX::findCaseInsensitive(std::string data, std::string toSearch, size_t pos = 0)
            {
                // Convert complete given String to lower case
                std::transform(data.begin(), data.end(), data.begin(), ::tolower);
                // Convert complete given Sub String to lower case
                std::transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
                // Find sub string in given string
                return data.find(toSearch, pos);
            }


            std::string StringX::to_Upper(std::string str)
            {
                std::for_each(str.begin(), str.end(), [](char & c) {
                    c = ::toupper(c);
                });

                return str;
            }

            std::string StringX::to_Lower(std::string str)
            {

                std::for_each(str.begin(), str.end(), [](char & c) {
                    c = ::tolower(c);
                });

                return str;
            }


            /*
            * Case Sensitive Implementation of startsWith()
            * It checks if the string 'mainStr' starts with given string 'toMatch'
            */
            bool StringX::startsWith(std::string mainStr, std::string toMatch)
            {
                // std::string::find returns 0 if toMatch is found at starting
                if(mainStr.find(toMatch) == 0)
                    return true;
                else
                    return false;
            }
            
            bool StringX::startsWithCaseInsensitive(std::string mainStr, std::string toMatch)
            {
                // Convert mainStr to lower case
                std::transform(mainStr.begin(), mainStr.end(), mainStr.begin(), ::tolower);
                // Convert toMatch to lower case
                std::transform(toMatch.begin(), toMatch.end(), toMatch.begin(), ::tolower);
                if(mainStr.find(toMatch) == 0)
                    return true;
                else
                    return false;
            }

                        /*
            * Case Sensitive Implementation of endsWith()
            * It checks if the string 'mainStr' ends with given string 'toMatch'
            */
            bool StringX::endsWith(const std::string &mainStr, const std::string &toMatch)
            {
                if(mainStr.size() >= toMatch.size() &&
                        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
                        return true;
                    else
                        return false;
            }

                        /*
            * Case Insensitive Implementation of endsWith()
            * It checks if the string 'mainStr' ends with given string 'toMatch'
            */
            bool StringX::endsWithCaseInsensitive(std::string mainStr, std::string toMatch)
            {
                auto it = toMatch.begin();
                return mainStr.size() >= toMatch.size() &&
                        std::all_of(std::next(mainStr.begin(),mainStr.size() - toMatch.size()), mainStr.end(), [&it](const char & c){
                            return ::tolower(c) == ::tolower(*(it++))  ;
                } );
            }

           /*
            * Erase all Occurrences of given substring from main string.
            */
            void StringX::eraseAllSubStr(std::string & mainStr, const std::string & toErase)
            {
                size_t pos = std::string::npos;
                // Search for the substring in string in a loop untill nothing is found
                while ((pos  = mainStr.find(toErase) )!= std::string::npos)
                {
                    // If found then erase it from string
                    mainStr.erase(pos, toErase.length());
                }
            }
         

}