#include "Framework/DataTypes/Constants/ActuatorSignalStatusSymbols.h"

namespace fmKinetics
{
string ActuatorSignalStatusSymbols::toString()
{
    switch (Value)
    {
    case ATTACHED:
        return "1";
    case DETTACHED:
        return "0";
    }
}

ActuatorSignalStatusSymbols::etype ActuatorSignalStatusSymbols::ConvertFromString(string s)
{
    if (s == "1")
        return ATTACHED;
    if (s == "0")
        return DETTACHED;
}

} // namespace fmKinetics