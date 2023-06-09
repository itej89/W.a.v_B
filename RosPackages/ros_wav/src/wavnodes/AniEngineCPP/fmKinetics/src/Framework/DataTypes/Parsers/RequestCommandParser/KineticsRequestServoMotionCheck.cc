#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoMotionCheck.h"

namespace fmKinetics
{
  KineticsRequestServoMotionCheck::KineticsRequestServoMotionCheck(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::SMV)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestServoMotionCheck::KineticsRequestServoMotionCheck(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::SMV)
    {
        
        string _command = removeDelimiters(command);
        vector<string> contents = decomposeCommand( _command);
        
        if(contents.size() == 1)
        {
            int address = std::stoi(contents.at(0));
           
                ActuatorType = MachineConfig::Instance.getActuatorWith( address);
            
        }
    }
}