#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestProximityRead.h"

namespace fmKinetics
{
      KineticsRequestProximityRead::KineticsRequestProximityRead(Actuator::etype actuatorType)
        : KineticsRequest(CommandLabels::CommandTypes::PRX)
        {
            ActuatorType = actuatorType;

            vector<string> c {  std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestProximityRead::KineticsRequestProximityRead(string command)
        : KineticsRequest(CommandLabels::CommandTypes::PRX)
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