#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDelay.h"

namespace fmKinetics
{
     
            KineticsResponseDelay::KineticsResponseDelay(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::DEL)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));

                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        Delay = std::stoi(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
             }
}