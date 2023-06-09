#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLThree.h"

namespace fmKinetics
{
       KineticsResponseCELLThree::KineticsResponseCELLThree(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::CELL3)
                {
                    vector<string> RequestParts = DecomposedResponse.at(0);
                    vector<string> ResponseParts = DecomposedResponse.at(1);

                    if(RequestParts.size() == 2)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestParts.at(1));
                    }
                    
                    if(RequestRecievedAck != NULL && RequestRecievedAck == KineticsResponseAcknowledgement::OK)
                    {
                        if(ResponseParts.size() == 2)
                        {
                            ADC = std::stoi(ResponseParts.at(1));
                        }
                    }
                }
        }

}