

#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "StringX.h"
#include "Framework/DataTypes/Parsers/RemoteCommandToMachineRequest.h"


using fmCommon::StringX;

namespace fmKinetics
{
    MachineRequests::etype RemoteCommandToMachineRequest::Convert(string data)
    {
        StringX stringX;
        vector<string> parts = stringX.split(data, '#'); 
        if(parts.size() > 0)
        {
            CommandLabels::RemoteCommandTypes::etype CommadType = CommandLabels::RemoteCommandTypes().stringtoenum.at(parts.at(0));
           
                switch(CommadType)
                {
                    case CommandLabels::RemoteCommandTypes::etype::PBTN:
                        if(parts.size() == 3 && parts.at(2) == "O")
                        {
                            if(parts.at(1) == "0")
                                return MachineRequests::POWER_BUTTON_PRESSED;
                            if(parts.at(1) == "1")
                                return MachineRequests::POWER_BUTTON_DOUBLE_PRESSED;
                            if(parts.at(1) == "2")
                                return MachineRequests::POWER_BUTTON_LONG_PRESS;
                        }
                        break;

                    case CommandLabels::RemoteCommandTypes::etype::VBTN:
                        if(parts.size() == 3 && parts.at(2) == "O")
                        {
                           
                            if(parts.at(1) == "0")
                                return MachineRequests::ATTENTION_BUTTON_PRESSED;
                            if(parts.at(1) == "1")
                                return MachineRequests::ATTENTION_BUTTON_DOUBLE_PRESSED;
                            if(parts.at(1) == "2")
                                return MachineRequests::ATTENTION_BUTTON_LONG_PRESS;
                            
                        }
                        break;
                }
        }
        return MachineRequests::UNKNOWN;
    }
}