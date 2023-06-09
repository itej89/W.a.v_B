#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTrigger.h"

namespace fmKinetics
{

     KineticsRequestTrigger::KineticsRequestTrigger()
     : KineticsRequest(CommandLabels::CommandTypes::TRG)
    {
        vector<string> s;
         string Command  = formCommand(s);
        Request = addDelimiters(Command);
    }
    
     KineticsRequestTrigger::KineticsRequestTrigger(string command)
     : KineticsRequest(CommandLabels::CommandTypes::TRG)
    {
        
        command =  removeDelimiters(command);
    }
}