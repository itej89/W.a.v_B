#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestPowerOnLockServo.h"

namespace fmKinetics
{
      KineticsRequestPowerOnLockServo::KineticsRequestPowerOnLockServo( Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::LON)
        {
            ActuatorType = actuatorType;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestPowerOnLockServo::KineticsRequestPowerOnLockServo(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::LON)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 1)
            {
                int address = std::stoi(contents.at(0));
              
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                
            }
        }
}