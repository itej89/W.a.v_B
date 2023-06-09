#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEasingInOut.h"

namespace fmKinetics
{
        KineticsRequestEasingInOut::KineticsRequestEasingInOut(CommandLabels::EasingType::etype easingType, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::INO)
        {
            EasingType = easingType;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(actuatorType)->Address), CommandLabels::EasingType().enumtostring.at(EasingType)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestEasingInOut::KineticsRequestEasingInOut(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::INO)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
                
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    EasingType =  CommandLabels::EasingType().stringtoenum.at(contents.at(2));
                
            }
        }
}