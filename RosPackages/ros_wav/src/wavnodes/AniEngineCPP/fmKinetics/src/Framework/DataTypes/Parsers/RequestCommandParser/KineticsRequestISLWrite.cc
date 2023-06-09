#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestISLWrite.h"

namespace fmKinetics
{
      KineticsRequestISLWrite::KineticsRequestISLWrite(int noOfBytes, int address, int value)
        : KineticsRequest(CommandLabels::CommandTypes::ISLW)
        {
            NoOfBytes = noOfBytes;
            Address = address;
            Value = value;

            vector<string> c {  std::to_string(Address), std::to_string(NoOfBytes), std::to_string(Value) };

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestISLWrite::KineticsRequestISLWrite(string command)
        : KineticsRequest(CommandLabels::CommandTypes::ISLW)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 3)
            {
                int Address = std::stoi(contents.at(1));
                int NoOfBytes = std::stoi(contents.at(2));
                Value = std::stoi(contents.at(3));
            }
        }
}