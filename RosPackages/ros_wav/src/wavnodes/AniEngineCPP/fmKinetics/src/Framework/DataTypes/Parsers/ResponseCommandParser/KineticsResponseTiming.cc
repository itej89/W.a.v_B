#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTiming.h"

namespace fmKinetics
{
   KineticsResponseTiming::KineticsResponseTiming(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::TMG)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));

                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        Timing = std::stoi(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
             }
}