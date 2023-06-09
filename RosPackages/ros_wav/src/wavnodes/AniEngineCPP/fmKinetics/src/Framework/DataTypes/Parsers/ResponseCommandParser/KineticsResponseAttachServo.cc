#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttachServo.h"
#include <iostream>
namespace fmKinetics
{
    
            KineticsResponseAttachServo::KineticsResponseAttachServo(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::ATC)
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