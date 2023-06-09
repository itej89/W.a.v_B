#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLockPowerStatus.h"

namespace fmKinetics
{
   KineticsResponseLockPowerStatus::KineticsResponseLockPowerStatus(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::LPW)
                {
                   vector<string> RequestParts = DecomposedResponse.at(0);
                   vector<string> ResponseParts = DecomposedResponse.at(1);
            
                   if(RequestParts.size() == 3)
                    {
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestParts.at(2));
                    }
                    
                    if(RequestRecievedAck != NULL && RequestRecievedAck == KineticsResponseAcknowledgement::OK)
                    {
                        if(ResponseParts.size() == 3)
                        {
                            int Address = std::stoi(ResponseParts.at(1));

                            ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                            
                            ResponseErrorCondition = KineticsResponseAcknowledgement().ConvertFromString(ResponseParts.at(2));
                            
                            if(ResponseErrorCondition == KineticsResponseAcknowledgement::NOP)
                            {
                                PowerState = ActuatorPowerStatusSymbols().ConvertFromString(ResponseParts.at(2));
                            }
                            
                        }
                    }
                }
             }
}