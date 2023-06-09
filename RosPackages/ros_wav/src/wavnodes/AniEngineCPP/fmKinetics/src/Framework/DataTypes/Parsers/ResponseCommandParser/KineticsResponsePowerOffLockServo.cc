#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOffLockServo.h"

namespace fmKinetics
{
 KineticsResponsePowerOffLockServo::KineticsResponsePowerOffLockServo(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::LOF)
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