#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDettachServo.h"

namespace fmKinetics
{
    KineticsResponseDettachServo::KineticsResponseDettachServo(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::DTC)
                {
                    vector<string> RequestAckParts = DecomposedResponse.at(0);
                    
                    if(RequestAckParts.size() == 3)
                    {
                        int Address = std::stoi(RequestAckParts.at(1));
                        ActuatorType = MachineConfig::Instance.getActuatorWith(Address);
                        RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestAckParts.at(2));
                    }
                }
        }
}