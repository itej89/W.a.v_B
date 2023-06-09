#include "Framework/DataTypes/Constants/ActuatorMotionSymbols.h"

namespace fmKinetics
{

string ActuatorMotionSymbols::toString()
{
    switch (Value)
    {
    case MOVING:
        return "1";
    case NotMoving:
        return "0";
    }
}

ActuatorMotionSymbols::etype ActuatorMotionSymbols::ConvertFromString(string s)
{
    if (s == "1")
        return MOVING;
    if (s == "0")
        return NotMoving;
}

} // namespace fmKinetics