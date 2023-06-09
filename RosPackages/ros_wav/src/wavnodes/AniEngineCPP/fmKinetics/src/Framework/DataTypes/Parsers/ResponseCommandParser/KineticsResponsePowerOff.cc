#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOff.h"

namespace fmKinetics
{

       KineticsResponsePowerOff::KineticsResponsePowerOff(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::POFF)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 2)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(1));
                    }
                }
             }
}