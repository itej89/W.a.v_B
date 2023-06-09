#pragma once 

namespace fmKinetics
{
     class Actuator
    {
        public:
            enum etype : int
            {        
                TURN = 21,
                LIFT = 22,
                LEAN = 23,
                TILT = 24,
                LOCK_RIGHT = 25,
                LOCK_LEFT = 26,
                UNKNOWN = -2
            };

            etype Value = UNKNOWN;
            
            Actuator();
              
            Actuator(int value);

            int getValue();
    };
}