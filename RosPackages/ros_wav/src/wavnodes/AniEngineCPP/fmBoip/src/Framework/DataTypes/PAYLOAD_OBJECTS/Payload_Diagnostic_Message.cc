
#include "Framework/DataTypes/PAYLOAD_OBJECTS/Payload_Diagnostic_Message.h"

namespace fmBoip
 {
     void Payload_Diagnostic_Message::initialize_PayloadItems()
        {
            Payload.insert(std::make_pair<TAG, Payload_Item_Type>(SOURCE_ADDRESS,Payload_Item_Type(0,2)));
            Payload.insert(std::make_pair<TAG, Payload_Item_Type>(TARGET_ADDRESS,Payload_Item_Type(2,2)));
            Payload.insert(std::make_pair<TAG, Payload_Item_Type>(USER_DATA,Payload_Item_Type(4)));
        }
    
     Payload_Diagnostic_Message::Payload_Diagnostic_Message(std::vector<uint8_t> DOIPPayload)
    {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    Payload_Diagnostic_Message::Payload_Diagnostic_Message()
    {
        initialize_PayloadItems();
    }
    
    std::vector<uint8_t> Payload_Diagnostic_Message::GetTargetAddress()
    {
        return Payload.at(TARGET_ADDRESS).RawData;
    }
    
    std::vector<uint8_t> Payload_Diagnostic_Message::GetSourceAddress()
    {
       
        return Payload.at(SOURCE_ADDRESS).RawData;
    }
    
    std::vector<uint8_t>  Payload_Diagnostic_Message::GetUserData()
    {

        std::vector<uint8_t>  userData = Payload.at(USER_DATA).RawData;
        
        if(userData.size() == 0)
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY,  "USerData in Diagnostic Message PAyload"));
        }
        
        return userData;
    }
    
    void Payload_Diagnostic_Message::SetSourceAddress(std::vector<uint8_t> &SA)
    {
        Payload.at(SOURCE_ADDRESS).RawData.clear();
        Payload.at(SOURCE_ADDRESS).RawData.insert(Payload.at(SOURCE_ADDRESS).RawData.end(), SA.begin(), SA.end());
    }
    
    void Payload_Diagnostic_Message::SetTArgetAddress(std::vector<uint8_t> &TA)
    {
        Payload.at(TARGET_ADDRESS).RawData.clear();
        Payload.at(TARGET_ADDRESS).RawData.insert(Payload.at(TARGET_ADDRESS).RawData.end(), TA.begin(), TA.end());
    }
    
    void Payload_Diagnostic_Message::SetUserData(std::vector<uint8_t>&  User_Data)
    {
        if(User_Data.size() > 0)
        {
            //Payload[TAG.USER_DATA]?.RawData = [UInt8](repeating: 0, count: User_Data.count)
            Payload.at(USER_DATA).RawData.clear();
            Payload.at(USER_DATA).RawData.insert(Payload.at(USER_DATA).RawData.end(), User_Data.begin(), User_Data.end());
        }
        else
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY, "Payload_Diagnostic_Message:SetUserData", ""));
        }
    }
}