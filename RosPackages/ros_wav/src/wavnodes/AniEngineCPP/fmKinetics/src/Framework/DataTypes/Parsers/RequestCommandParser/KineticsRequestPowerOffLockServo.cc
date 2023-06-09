#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestPowerOffLockServo.h"

namespace fmKinetics
{

        KineticsRequestPowerOffLockServo::KineticsRequestPowerOffLockServo( Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::LOF)
        {
            ActuatorType = actuatorType;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestPowerOffLockServo::KineticsRequestPowerOffLockServo(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::LOF)
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