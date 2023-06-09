#pragma once 

#include <string>

using std::string;

namespace fmKinetics
{
     class KineticsResponseAcknowledgement
    {
        public:
            enum etype : int
            {        
                NOP = 2,
                OK = 1,
                Error = 0
            };

            etype Value = Error;
             KineticsResponseAcknowledgement(){}
          

            etype ConvertFromString(string s);
    };
}