#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoDegree.h"

namespace fmKinetics
{
      KineticsRequestServoDegree::KineticsRequestServoDegree(Actuator::etype actuatorType)
        : KineticsRequest(CommandLabels::CommandTypes::DEG)
        {
            ActuatorType = actuatorType;

            vector<string> c {  std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestServoDegree::KineticsRequestServoDegree(string command)
        : KineticsRequest(CommandLabels::CommandTypes::DEG)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 1)
            {
                int address = std::stoi(contents.at(0));
               
                    ActuatorType = MachineConfig::Instance.getActuatorWith( address);
                
            }
        }
}