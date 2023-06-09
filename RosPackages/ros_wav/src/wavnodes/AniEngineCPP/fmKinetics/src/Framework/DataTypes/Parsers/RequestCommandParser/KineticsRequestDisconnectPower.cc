#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDisconnectPower.h"

namespace fmKinetics
{
    KineticsRequestDisconnectPower::KineticsRequestDisconnectPower( Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::DPW)
        {
            ActuatorType = actuatorType;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestDisconnectPower::KineticsRequestDisconnectPower(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::DPW)
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