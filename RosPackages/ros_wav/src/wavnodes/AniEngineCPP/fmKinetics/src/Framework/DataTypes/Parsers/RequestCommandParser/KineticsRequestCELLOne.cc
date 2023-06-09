#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestCELLOne.h"

namespace fmKinetics
{
     KineticsRequestCELLOne::KineticsRequestCELLOne()
     : KineticsRequest(CommandLabels::CommandTypes::CELL1)
    {
         vector<string> s {};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestCELLOne::KineticsRequestCELLOne(string command)
     : KineticsRequest(CommandLabels::CommandTypes::CELL1)
    {
        
        command =  removeDelimiters(command);
    }
}