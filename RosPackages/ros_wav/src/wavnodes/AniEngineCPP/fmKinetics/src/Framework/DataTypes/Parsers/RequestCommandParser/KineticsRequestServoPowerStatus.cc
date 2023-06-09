#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoPowerStatus.h"

namespace fmKinetics
{
    KineticsRequestServoPowerStatus::KineticsRequestServoPowerStatus(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::SPW)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestServoPowerStatus::KineticsRequestServoPowerStatus(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::SPW)
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