#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestConnectPower.h"

namespace fmKinetics
{
      KineticsRequestConnectPower::KineticsRequestConnectPower( Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::CPW)
        {
            ActuatorType = actuatorType;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestConnectPower::KineticsRequestConnectPower(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::CPW)
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