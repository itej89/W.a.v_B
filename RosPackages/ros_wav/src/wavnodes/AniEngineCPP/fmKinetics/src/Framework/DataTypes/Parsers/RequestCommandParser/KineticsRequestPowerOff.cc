#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestPowerOff.h"

namespace fmKinetics
{
  KineticsRequestPowerOff::KineticsRequestPowerOff()
     : KineticsRequest(CommandLabels::CommandTypes::POFF)
    {
        vector<string> s;
         string Command  = formCommand(s);
        Request = addDelimiters(Command);
    }
    
     KineticsRequestPowerOff::KineticsRequestPowerOff(string command)
     : KineticsRequest(CommandLabels::CommandTypes::POFF)
    {
        
        command =  removeDelimiters(command);
    }
}