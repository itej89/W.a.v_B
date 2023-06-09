#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttentionOn.h"

namespace fmKinetics
{

     KineticsRequestAttentionOn::KineticsRequestAttentionOn()
     : KineticsRequest(CommandLabels::CommandTypes::VEN)
    {
         vector<string> s {};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestAttentionOn::KineticsRequestAttentionOn(string command)
     : KineticsRequest(CommandLabels::CommandTypes::VEN)
    {
        
        command =  removeDelimiters(command);
    }
}