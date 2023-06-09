#include "Framework/DataTypes/Constants/ActuatorPowerStatusSymbols.h"

namespace fmKinetics
{
string ActuatorPowerStatusSymbols::toString()
{
    switch (Value)
    {
    case ON:
        return "1";
    case OFF:
        return "0";
    }
}

ActuatorPowerStatusSymbols::etype ActuatorPowerStatusSymbols::ConvertFromString(string s)
{
    if (s == "1")
        return ON;
    if (s == "0")
        return OFF;
}
} // namespace fmKinetics