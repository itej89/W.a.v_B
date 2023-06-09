#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEasing.h"

namespace fmKinetics
{
     KineticsRequestServoEasing::KineticsRequestServoEasing(CommandLabels::EasingFunction::etype easing, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::EAS)
        {
            EasingFunction = easing;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(actuatorType)->Address), CommandLabels::EasingFunction().enumtostring.at(EasingFunction)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestServoEasing::KineticsRequestServoEasing(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::EAS)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
              
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    EasingFunction =  CommandLabels::EasingFunction().stringtoenum.at(contents.at(2));
                
            }
        }
}