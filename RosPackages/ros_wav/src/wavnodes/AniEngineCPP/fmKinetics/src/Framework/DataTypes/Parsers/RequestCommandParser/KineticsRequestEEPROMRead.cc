#include  "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEEPROMRead.h"

namespace fmKinetics
{
     KineticsRequestEEPROMRead::KineticsRequestEEPROMRead(EEPROMDetails memoryLocation)
        : KineticsRequest(CommandLabels::CommandTypes::EEPR)
        {
            NoOfBytes = memoryLocation.NoOfBytes;
            Address = memoryLocation.Address;

            vector<string> c {  std::to_string(Address), std::to_string(NoOfBytes)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestEEPROMRead::KineticsRequestEEPROMRead(string command)
        : KineticsRequest(CommandLabels::CommandTypes::EEPR)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                Address = std::stoi(contents.at(1));
                NoOfBytes = std::stoi(contents.at(2));
            
                MemoryLocation = new EEPROMDetails(Address, NoOfBytes);
            }
        }
}