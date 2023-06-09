
#include "Framework/DataTypes/PAYLOAD_OBJECTS/PAYLOAD_OBJECT_ECU_RESPONSE/Payload_Vehicle_Announcement.h"
#include "Framework/DOIPLayer/DOIPSession.h"

namespace fmBoip
 {
    
    void Payload_Vehicle_Announcement::initialize_PayloadItems()
    {   
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::VIN, Payload_Item_Type(0, 17)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::LOGICAL_ADDRESS, Payload_Item_Type(17, 2)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::EID, Payload_Item_Type(19, 6)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::GID, Payload_Item_Type(25, 6)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::FURTHER_ACTION, Payload_Item_Type(31, 1)));
          Payload.insert(std::make_pair<TAG, Payload_Item_Type>(PayloadObject::VIN_GID, Payload_Item_Type(32)));
    }
    
    Payload_Vehicle_Announcement::Payload_Vehicle_Announcement(std::vector<uint8_t> DOIPPayload)
    {
        initialize_PayloadItems();
        Decode_Payload(DOIPPayload);
    }
    
    std::vector<uint8_t> Payload_Vehicle_Announcement::GetVIN() 
    {
        return Payload.at(VIN).RawData;
    }
    
    std::vector<uint8_t>  Payload_Vehicle_Announcement::GetlogicalAddress()
    {
        std::vector<uint8_t> address;
        address.insert(address.end(), 
        Payload.at(PayloadObject::LOGICAL_ADDRESS).RawData.begin(),
        Payload.at(PayloadObject::LOGICAL_ADDRESS).RawData.end());

        bool Contaitns_Invalid_Address  = false;
        std::vector<std::vector<uint8_t>> invalid_addres_list = DOIPSession::Instance->getInvalidAddresses();
        for(auto& it : invalid_addres_list)
        {
            if(it == address)
            {
                Contaitns_Invalid_Address = true;
                break;
            }
        }

        if(Contaitns_Invalid_Address)
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA, "Vehicle Identification Response Payload Loagical Address"));
            
            return std::vector<uint8_t>();
        }
        return address;
    }
    
    std::vector<uint8_t>  Payload_Vehicle_Announcement::GetEID()
    {
        return Payload.at(EID).RawData;
    }
    
    std::vector<uint8_t>  Payload_Vehicle_Announcement::GetGID() 
    {
        return Payload.at(GID).RawData;
    }
    
   uint8_t Payload_Vehicle_Announcement::GetFurtherAction()
    {
        if(Payload.at(FURTHER_ACTION).RawData.size() > 0)
        {
            uint8_t furtherAction = Payload.at(FURTHER_ACTION).RawData[0];
            if(furtherAction >= DOIPSession::Instance->getValidFurtherActions()[0] && furtherAction <= DOIPSession::Instance->getValidFurtherActions()[1])
            {
                ValidationErrors.add( ValidationRuleMessage(VALIDATION_ERROR_CODES::INVALID_DATA,  "Vehicle IDentification Response further Action code", ""));
                return 0x00;
            }
            else
            {
                return furtherAction;
            }
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY, "Payload_Vehicle_Announcement:GetFurtherAction", ""));
            return 0x00;
        }
    }
    
    uint8_t Payload_Vehicle_Announcement::GetVINGIDSync()
    {
        if(Payload.at(VIN_GID).RawData.size() > 0)
        {
            return Payload.at(VIN_GID).RawData[0];
        }
        else
        {
            ValidationErrors.add( ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY, "Payload_Vehicle_Announcement:GetVINGIDSync", ""));
            return 0x00;
        }
    }
}