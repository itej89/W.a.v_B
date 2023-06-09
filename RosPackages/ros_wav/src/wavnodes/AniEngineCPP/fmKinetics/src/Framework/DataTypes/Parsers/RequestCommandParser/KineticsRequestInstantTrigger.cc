#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestInstantTrigger.h"

namespace fmKinetics
{
     KineticsRequestInstantTrigger::KineticsRequestInstantTrigger()
     : KineticsRequest(CommandLabels::CommandTypes::ITRG)
    {
        vector<string> s;
         string Command  = formCommand(s);
        Request = addDelimiters(Command);
    }
    
     KineticsRequestInstantTrigger::KineticsRequestInstantTrigger(string command)
     : KineticsRequest(CommandLabels::CommandTypes::ITRG)
    {
        
        command =  removeDelimiters(command);
    }
}