#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseInstantTrigger.h"

namespace fmKinetics
{
   KineticsResponseInstantTrigger::KineticsResponseInstantTrigger(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::ITRG)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 2)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(1));
                    }
                }
             }
}