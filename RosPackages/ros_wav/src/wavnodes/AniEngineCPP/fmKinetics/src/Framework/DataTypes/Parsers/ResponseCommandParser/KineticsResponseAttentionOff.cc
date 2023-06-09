#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttentionOff.h"

namespace fmKinetics
{
            KineticsResponseAttentionOff::KineticsResponseAttentionOff(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::VNO)
                {
                    vector<string> RequestAckParts = DecomposedResponse.at(0);
                    
                    if(RequestAckParts.size() == 2)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(1));
                    }
                }
        }
}