#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTiming.h"

namespace fmKinetics
{
  KineticsRequestTiming::KineticsRequestTiming(int timing, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::TMG)
        {
            Timing = timing;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(Timing)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestTiming::KineticsRequestTiming(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::TMG)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
             
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    Timing = std::stoi(contents.at(2));
                
            }
        }
}