#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestLockSignalStatus.h"

namespace fmKinetics
{
     KineticsRequestLockSignalStatus::KineticsRequestLockSignalStatus(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::LSA)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestLockSignalStatus::KineticsRequestLockSignalStatus(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::LSA)
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