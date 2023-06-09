#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestVelocity.h"

namespace fmKinetics
{
     KineticsRequestVelocity::KineticsRequestVelocity(int velocity, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::VEL)
        {
            Velocity = velocity;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(Velocity)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestVelocity::KineticsRequestVelocity(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::VEL)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
             
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    Velocity = std::stoi(contents.at(2));
                
            }
        }
}