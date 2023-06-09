#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEasingInOut.h"

namespace fmKinetics
{
     
           KineticsResponseEasingInOut::KineticsResponseEasingInOut(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::INO)
                {
                    vector<string> RequestAckParts = DecomposedResponse.at(0);
                    
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));
                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        EasingType = CommandLabels::EasingType().stringtoenum.at(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
        }
}