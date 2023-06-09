#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAngle.h"

namespace fmKinetics
{
     KineticsResponseAngle::KineticsResponseAngle(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::ANG)
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