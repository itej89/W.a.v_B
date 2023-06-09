#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDelay.h"

namespace fmKinetics
{
      KineticsRequestDelay::KineticsRequestDelay(int delay, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::DEL)
        {
            Delay = delay;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(Delay)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestDelay::KineticsRequestDelay(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::DEL)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
               
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    Delay = std::stoi(contents.at(2));
                
            }
        }
}