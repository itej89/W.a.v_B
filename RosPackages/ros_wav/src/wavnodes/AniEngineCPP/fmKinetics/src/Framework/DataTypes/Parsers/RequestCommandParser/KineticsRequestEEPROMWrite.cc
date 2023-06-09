#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEEPROMWrite.h"

namespace fmKinetics
{
        KineticsRequestEEPROMWrite::KineticsRequestEEPROMWrite(EEPROMDetails memoryLocation, int value)
        : KineticsRequest(CommandLabels::CommandTypes::EEPW)
        {
            Value = value;

            vector<string> c {  std::to_string(memoryLocation.Address), std::to_string(memoryLocation.NoOfBytes), std::to_string(Value) };

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestEEPROMWrite::KineticsRequestEEPROMWrite(string command)
        : KineticsRequest(CommandLabels::CommandTypes::EEPW)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 3)
            {
                int Address = std::stoi(contents.at(1));
                int NoOfBytes = std::stoi(contents.at(2));
                Value = std::stoi(contents.at(3));
                MemoryLocation = new EEPROMDetails(Address, NoOfBytes);
            }
        }
}