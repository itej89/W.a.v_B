#pragma once 

#include <string>

using std::string;

namespace fmKinetics
{
     class ActuatorMotionSymbols
    {
        public:
            enum etype : int
            {        
                MOVING = 1,
                NotMoving = 0
            };

        etype Value = NotMoving;
        
        ActuatorMotionSymbols(){}
              
        string toString();

        etype ConvertFromString(string s);
    };
}