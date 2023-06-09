#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestFrequency.h"

namespace fmKinetics
{
     KineticsRequestFrequency::KineticsRequestFrequency(int frequency, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::FRQ)
        {
            Frequency = frequency;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(Frequency)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestFrequency::KineticsRequestFrequency(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::FRQ)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
                
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    Frequency = std::stoi(contents.at(2));
                
            }
        }
}