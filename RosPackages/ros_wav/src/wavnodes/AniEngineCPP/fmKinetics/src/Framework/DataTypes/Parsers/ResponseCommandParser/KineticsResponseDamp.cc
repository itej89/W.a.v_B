#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDamp.h"

namespace fmKinetics
{
    KineticsResponseDamp::KineticsResponseDamp(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::DMP)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));

                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        Damping = std::stoi(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
             }
}