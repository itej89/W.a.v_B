#pragma once 

#include <string>

using std::string;

namespace fmKinetics
{
     class ProximityStateSymbols
    {
        public:
            enum etype : int
            {        
                MOUNTED = 1,
                NotMounted = 0
            };

            etype Value = NotMounted;
            ProximityStateSymbols(){}
              
            string toString();

            etype ConvertFromString(string s);
    };
}