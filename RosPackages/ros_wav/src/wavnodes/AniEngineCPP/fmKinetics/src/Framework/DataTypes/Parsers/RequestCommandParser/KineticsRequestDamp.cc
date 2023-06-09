#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDamp.h"

namespace fmKinetics
{
        KineticsRequestDamp::KineticsRequestDamp(int damping, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::DMP)
        {
            Damping = damping;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(Damping)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestDamp::KineticsRequestDamp(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::DMP)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
              
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    Damping = std::stoi(contents.at(2));
                
            }
        }
}