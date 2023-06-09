#pragma once 

namespace fmKinetics
{
     class ActuatorMotionParameters
    {
        public:
            enum etype : int
            {        
                ANGLE,
                TIME,
                DELAY,
                EASING_FUNCTION,
                EASING_TYPE,
                VELOCITY,
                DAMPING,
                FREQUENCY,
                UNKNOWN
            };

            etype Value = UNKNOWN;
    };
};