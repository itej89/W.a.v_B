#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseVelocity.h"

namespace fmKinetics
{
     KineticsResponseVelocity::KineticsResponseVelocity(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::VEL)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));

                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        Velocity = std::stoi(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
             }
}