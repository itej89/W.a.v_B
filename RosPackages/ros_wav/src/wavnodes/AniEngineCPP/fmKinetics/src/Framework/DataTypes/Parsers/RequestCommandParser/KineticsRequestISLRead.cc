#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLRead.h"

namespace fmKinetics
{

        KineticsRequestISLRead::KineticsRequestISLRead(int noOfBytes, int address)
        : KineticsRequest(CommandLabels::CommandTypes::ISLR)
        {
            NoOfBytes = noOfBytes;
            Address = address;

            vector<string> c {  std::to_string(Address), std::to_string(NoOfBytes)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestISLRead::KineticsRequestISLRead(string command)
        : KineticsRequest(CommandLabels::CommandTypes::ISLR)
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