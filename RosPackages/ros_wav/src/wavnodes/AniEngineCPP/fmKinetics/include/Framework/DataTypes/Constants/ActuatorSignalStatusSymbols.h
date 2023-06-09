#pragma once 

#include <string>

using std::string;

namespace fmKinetics
{
     class ActuatorSignalStatusSymbols
    {
        public:
            enum etype : int
            {        
                ATTACHED = 1,
                DETTACHED = 0
            };

            etype Value = DETTACHED;
             ActuatorSignalStatusSymbols(){}
              
           string toString();

            etype ConvertFromString(string s);
    };
}