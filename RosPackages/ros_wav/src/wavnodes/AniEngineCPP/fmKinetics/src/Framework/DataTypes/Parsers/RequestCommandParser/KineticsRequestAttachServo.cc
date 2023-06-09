#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAttachServo.h"

namespace fmKinetics
{
   KineticsRequestAttachServo::KineticsRequestAttachServo(Actuator::etype actuatorType)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::ATC)
    {
        
        ActuatorType = actuatorType;
         vector<string> s {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

        string Command = formCommand(s);
        
        Request = addDelimiters(Command);
    }
    
    KineticsRequestAttachServo::KineticsRequestAttachServo(string command)
     : KineticsRequestForActuator(CommandLabels::CommandTypes::ATC)
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