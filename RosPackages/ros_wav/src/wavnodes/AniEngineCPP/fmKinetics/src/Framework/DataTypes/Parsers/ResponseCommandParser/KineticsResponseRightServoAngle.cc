#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseRightServoAngle.h"

namespace fmKinetics
{
    KineticsResponseRightServoAngle::KineticsResponseRightServoAngle(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::RLK)
                {
                    vector<string> RequestAckParts = DecomposedResponse.at(0);
                    
                    if(RequestAckParts.size() == 4)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));
                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        Angle = std::stoi(RequestAckParts.at(2));
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(3));
                    }
                }
        }
}