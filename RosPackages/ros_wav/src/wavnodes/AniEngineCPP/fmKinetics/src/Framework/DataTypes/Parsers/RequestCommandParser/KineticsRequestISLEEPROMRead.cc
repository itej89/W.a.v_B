#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLEEPROMRead.h"

namespace fmKinetics
{
       KineticsRequestISLEEPROMRead::KineticsRequestISLEEPROMRead(int noOfBytes, int address)
        : KineticsRequest(CommandLabels::CommandTypes::ISLER)
        {
            NoOfBytes = noOfBytes;
            Address = address;

            vector<string> c {  std::to_string(Address), std::to_string(NoOfBytes)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestISLEEPROMRead::KineticsRequestISLEEPROMRead(string command)
        : KineticsRequest(CommandLabels::CommandTypes::ISLER)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                Address = std::stoi(contents.at(1));
                NoOfBytes = std::stoi(contents.at(2));
            }
        }
}