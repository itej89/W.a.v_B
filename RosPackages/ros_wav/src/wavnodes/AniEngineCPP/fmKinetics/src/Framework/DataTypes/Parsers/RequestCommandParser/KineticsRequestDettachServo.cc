#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDettachServo.h"

namespace fmKinetics
{
    KineticsRequestDettachServo::KineticsRequestDettachServo(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::DTC)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
     KineticsRequestDettachServo::KineticsRequestDettachServo(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::DTC)
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