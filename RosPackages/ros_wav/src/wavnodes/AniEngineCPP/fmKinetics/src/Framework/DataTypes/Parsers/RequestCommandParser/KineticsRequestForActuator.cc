#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestForActuator.h"

namespace fmKinetics
{
    KineticsRequestForActuator::KineticsRequestForActuator(CommandLabels::CommandTypes::etype requestType)
     : KineticsRequest(requestType)
    {
    }
}