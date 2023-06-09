#pragma once 

#include <string>

using std::string;

namespace fmKinetics
{
     class ActuatorPowerStatusSymbols
    {
        public:
            enum etype : int
            {        
                ON = 1,
                OFF = 0
            };

            etype Value = OFF;
             ActuatorPowerStatusSymbols(){}
              
           string toString();

            etype ConvertFromString(string s);
    };
}