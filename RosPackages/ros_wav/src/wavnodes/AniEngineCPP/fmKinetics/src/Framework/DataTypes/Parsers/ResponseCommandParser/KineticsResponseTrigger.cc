#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTrigger.h"

namespace fmKinetics
{
  KineticsResponseTrigger::KineticsResponseTrigger(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::TRG)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 2)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(1));
                    }
                }
             }
}