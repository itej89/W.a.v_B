#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLWrite.h"

namespace fmKinetics
{
    
 KineticsResponseISLWrite::KineticsResponseISLWrite(string response) 
            : KineticsResponse(response)
            {
                if(ResponseType == CommandLabels::CommandTypes::ISLW)
                {
                        vector<string> RequestParts = DecomposedResponse.at(0);
                        vector<string> ResponseParts = DecomposedResponse.at(1);
                        
                        if(RequestParts.size() == 3)
                        {
                            RequestRecievedAck =  KineticsResponseAcknowledgement().ConvertFromString(RequestParts.at(2));
                        }
                        
                        if(RequestRecievedAck != NULL && RequestRecievedAck == KineticsResponseAcknowledgement::OK)
                        {
                            if(ResponseParts.size() >= 3)
                            {
                                int Address = std::stoi(ResponseParts.at(1));
                                int ByteCount = std::stoi(ResponseParts.at(2));
                                
                                if(ByteCount > 0){
                                    MemoryLocation = new EEPROMDetails(Address, ByteCount);
                                    
                                    if(MemoryLocation->NoOfBytes > 0 && ResponseParts.size() == 3+MemoryLocation->NoOfBytes)
                                    {
                                        for(int index=0; index< MemoryLocation->NoOfBytes; index++)
                                        {
                                            //EEPROM return value will be in hex String format
                                            Data.push_back(std::stoi(ResponseParts.at(3 + index)));
                                        }
                                    }
                                }
                            }
                        }
                }
        }
}