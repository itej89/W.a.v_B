#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttentionOff.h"
namespace fmKinetics
{
   KineticsRequestAttentionOff::KineticsRequestAttentionOff()
     : KineticsRequest(CommandLabels::CommandTypes::VNO)
    {
         vector<string> s {};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestAttentionOff::KineticsRequestAttentionOff(string command)
     : KineticsRequest(CommandLabels::CommandTypes::VNO)
    {
        
        command =  removeDelimiters(command);
    }
}