#include "Framework/DataTypes/Constants/ProximityStateSymbols.h"

namespace fmKinetics
{
string ProximityStateSymbols::toString()
{
    switch (Value)
    {
    case MOUNTED:
        return "1";
    case NotMounted:
        return "0";
    }
}

ProximityStateSymbols::etype ProximityStateSymbols::ConvertFromString(string s)
{
    if (s == "1")
        return MOUNTED;
    if (s == "0")
        return NotMounted;
}

} // namespace fmKinetics