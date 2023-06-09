#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestCELLTwo.h"

namespace fmKinetics
{
     KineticsRequestCELLTwo::KineticsRequestCELLTwo()
     : KineticsRequest(CommandLabels::CommandTypes::CELL2)
    {
         vector<string> s {};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestCELLTwo::KineticsRequestCELLTwo(string command)
     : KineticsRequest(CommandLabels::CommandTypes::CELL2)
    {
        
        command =  removeDelimiters(command);
    }
}