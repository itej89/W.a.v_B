#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttentionOn.h"

namespace fmKinetics
{
   KineticsResponseAttentionOn::KineticsResponseAttentionOn(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::VEN)
                {
                    vector<string> RequestAckParts = DecomposedResponse.at(0);
                    
                    if(RequestAckParts.size() == 2)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(1));
                    }
                }
        }
}