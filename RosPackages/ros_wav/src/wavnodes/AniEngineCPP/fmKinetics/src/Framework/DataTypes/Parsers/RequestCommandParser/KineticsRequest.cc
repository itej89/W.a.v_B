#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
namespace fmKinetics
{
        KineticsRequest::KineticsRequest(CommandLabels::CommandTypes::etype requestType)
        {
            RequestType = requestType;
        }

        
        string KineticsRequest::addDelimiters(string command)
        {
            return "~"+command+":";
        }
        
        string KineticsRequest::formCommand(vector<string> items)
        {
            CommandLabels::CommandTypes ctypes;
            string command =  ctypes.enumtostring.at(RequestType);
            
            for(std::vector<string>::iterator it = items.begin(); it != items.end(); ++it) {
                    command = command + "#" + *it;
            }
            return command;
        }
        
        string KineticsRequest::removeDelimiters(string command)
        {
            StringX stringX;
            command = stringX.removeDelimiter(command, '~', ':');

             return command;
        }



        vector<string> KineticsRequest::decomposeCommand(string command)
        {
             StringX stringX;
            vector<string> data;
            
            vector<string> parts = stringX.split(command, '#');
            if(parts.size() > 0)
            {
                RequestType = CommandLabels::CommandTypes().stringtoenum.at(parts.at(0));
                if(RequestType != CommandLabels::CommandTypes::UNKNOWN && parts.size() > 1)
                {
                    for(int i=1; i<parts.size();i++)
                    {
                        data.push_back(parts.at(i));
                    }
                }
            }
            
            return data;
        }

}