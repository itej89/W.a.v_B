#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoSignalStatus.h"

namespace fmKinetics
{
   KineticsRequestServoSignalStatus::KineticsRequestServoSignalStatus(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::SAT)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestServoSignalStatus::KineticsRequestServoSignalStatus(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::SAT)
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