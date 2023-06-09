#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoEasing.h"

namespace fmKinetics
{
    KineticsResponseServoEasing::KineticsResponseServoEasing(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::EAS)
                {
                   vector<string> RequestAckParts = DecomposedResponse.at(0);
            
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));

                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        EasingFunction = CommandLabels::EasingFunction().stringtoenum.at(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
             }
}