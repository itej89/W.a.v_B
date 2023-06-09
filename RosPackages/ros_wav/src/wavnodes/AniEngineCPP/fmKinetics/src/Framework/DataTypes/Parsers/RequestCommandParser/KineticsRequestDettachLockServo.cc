#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDettachLockServo.h"

namespace fmKinetics
{
  KineticsRequestDettachLockServo::KineticsRequestDettachLockServo(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::LDT)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestDettachLockServo::KineticsRequestDettachLockServo(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::LDT)
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