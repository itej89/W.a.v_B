#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestCELLThree.h"
namespace fmKinetics
{
     KineticsRequestCELLThree::KineticsRequestCELLThree()
     : KineticsRequest(CommandLabels::CommandTypes::CELL3)
    {
         vector<string> s {};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestCELLThree::KineticsRequestCELLThree(string command)
     : KineticsRequest(CommandLabels::CommandTypes::CELL3)
    {
        
        command =  removeDelimiters(command);
    }
}