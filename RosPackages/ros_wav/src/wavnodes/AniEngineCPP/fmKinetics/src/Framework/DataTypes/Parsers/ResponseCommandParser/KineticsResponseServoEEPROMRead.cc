#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoEEPROMRead.h"

namespace fmKinetics
{
       KineticsResponseServoEEPROMRead::KineticsResponseServoEEPROMRead(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::SEPR)
                {
                        vector<string> RequestParts = DecomposedResponse.at(0);
                        vector<string> ResponseParts = DecomposedResponse.at(1);
                        
                        if(RequestParts.size() == 4)
                        {
                            RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestParts.at(3));
                        }
                        
                        if(RequestRecievedAck != NULL && RequestRecievedAck == KineticsResponseAcknowledgement::OK)
                        {

                            if(ResponseParts.size() >= 4)
                            {
                                int Address = std::stoi(ResponseParts.at(2));
                                int ByteCount = std::stoi(ResponseParts.at(3));
                                
                                if(ByteCount > 0){
                                    MemoryLocation = new EEPROMDetails(Address, ByteCount);
                                    if(MemoryLocation->NoOfBytes > 0 && ResponseParts.size() == 4+MemoryLocation->NoOfBytes)
                                    {
                                        for(int index=0; index< MemoryLocation->NoOfBytes; index++)
                                        {
                                            //EEPROM return value will be in hex String format
                                            Data.push_back(std::stoi(ResponseParts.at(4 + index),nullptr, 16));
                                        }
                                    }
                                }
                            }
                        }
                }
        }
}