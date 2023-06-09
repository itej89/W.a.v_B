#include "Framework/DataTypes/Constants/KineticsResponseAcknowledgement.h"

namespace fmKinetics
{
KineticsResponseAcknowledgement::etype KineticsResponseAcknowledgement::ConvertFromString(string s)
{
    if (s == "E")
        return Error;
    if (s == "O")
        return OK;

        return NOP;
}

} // namespace fmKinetics