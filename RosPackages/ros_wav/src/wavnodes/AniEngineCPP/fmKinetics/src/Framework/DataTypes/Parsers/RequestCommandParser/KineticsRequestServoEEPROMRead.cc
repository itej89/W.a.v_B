#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEEPROMRead.h"

namespace fmKinetics
{
        KineticsRequestServoEEPROMRead::KineticsRequestServoEEPROMRead(Actuator::etype actuator , EEPROMDetails memoryLocation)
        : KineticsRequest(CommandLabels::CommandTypes::SEPR)
        {
             ActuatorType = actuator;
            NoOfBytes = memoryLocation.NoOfBytes;
            EEPROMAddress = memoryLocation.Address;


            vector<string> c { std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(EEPROMAddress), std::to_string(NoOfBytes)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestServoEEPROMRead::KineticsRequestServoEEPROMRead(string command)
        : KineticsRequest(CommandLabels::CommandTypes::SEPR)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 3)
            {
                int address = std::stoi(contents.at(0));
        
                ActuatorType = MachineConfig::Instance.getActuatorWith(address);
            
            EEPROMAddress = std::stoi(contents.at(1));
            NoOfBytes = std::stoi(contents.at(2));

            MemoryLocation = new EEPROMDetails(EEPROMAddress, NoOfBytes);
            }
        }
}