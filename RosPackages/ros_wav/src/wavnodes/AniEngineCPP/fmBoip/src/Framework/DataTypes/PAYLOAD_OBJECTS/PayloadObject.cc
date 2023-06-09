
#include <bits/stdc++.h> 

#include "Framework/DataTypes/PAYLOAD_OBJECTS/PayloadObject.h"

namespace fmBoip
 {
     uint32_t PayloadObject::Max_DOIP_PAYLOAD_SIZE = 0;

      uint64_t PayloadObject::DOIPPayloadMinimumLengthInBytes()
    {
        uint64_t ValidData_Length = 0;
        
        for (std::map<TAG, Payload_Item_Type>::iterator it = Payload.begin(); it != Payload.end(); ++it)
        {
            if(it->second.IsItemLengthNotDefined())
            {
                Minimum_Payload_Length_In_Bytes = ValidData_Length;
                Maximum_Payload_Length_In_Bytes = std::numeric_limits<uint64_t>::max();
                return ValidData_Length;
            }
            else
            {
                ValidData_Length += it->second.Length_ISO_13400;
            }
        }

        
        Minimum_Payload_Length_In_Bytes = ValidData_Length;
        Maximum_Payload_Length_In_Bytes = ValidData_Length;
        
        return ValidData_Length;
    }
    
    uint64_t PayloadObject::TotalNumberOfBytesInPayload()
    {
        uint64_t ValidData_Length = 0;
        
        for (std::map<TAG, Payload_Item_Type>::iterator it = Payload.begin(); it != Payload.end(); ++it)
        {
            if(it->second.RawData.size() != 0)
            {
                ValidData_Length = ValidData_Length + it->second.RawData.size();
            }
        }
        
        return ValidData_Length;
    }
    
    void PayloadObject::ExtractPayload(std::vector<uint8_t> DOIPPayload)
    {
                fmCommon::VectorX vecX;
        for (std::map<TAG, Payload_Item_Type>::iterator it = Payload.begin(); it != Payload.end(); ++it)
       {
            if(it->second.IsItemLengthNotDefined())
            {
                //This assignment will extract Payload Items whose length is not fixed
                if(DOIPPayload.size() > it->second.Position)
                {   
                    it->second.RawData.clear();
                    std::vector<uint8_t> subVec = vecX.subvector(DOIPPayload, it->second.Position, DOIPPayload.size()-1);
                    it->second.RawData.insert(it->second.RawData.end(), subVec.begin(), subVec.end()); 
                }
            }
            else
            {
                int EndIndex = (it->second.Position + (it->second.Length_ISO_13400) - 1);
                if(DOIPPayload.size() > EndIndex)
                {
                    it->second.RawData.clear();
                    std::vector<uint8_t> subVec = vecX.subvector(DOIPPayload, it->second.Position, EndIndex);
                    it->second.RawData.insert(it->second.RawData.end(), subVec.begin(), subVec.end()); 
                }
            }
        }
    }
    
    
    
    void PayloadObject::Decode_Payload(std::vector<uint8_t> DOIPPayload)
    {
        if(DOIPPayload.size() == 0)
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY, "PayloadObject:Decode_Payload", ""));
            
            return;
        }
        
        Minimum_Payload_Length_In_Bytes = DOIPPayloadMinimumLengthInBytes();
        
        if(DOIPPayload.size() >= Minimum_Payload_Length_In_Bytes)
        {
            ExtractPayload(DOIPPayload);
        }
        else
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::INCORRECT_LENGTH,  "PayloadObject:Decode_Payload", ""));
        }
    }
    

    std::vector<uint8_t> PayloadObject::Make_Payload()
    {
        uint64_t Required_Payload_Length = TotalNumberOfBytesInPayload();
        
        if(Required_Payload_Length != 0)
        {
            std::vector<uint8_t> DOIP_Payload;

            // Declare vector of pairs 
            std::vector<std::pair<TAG, Payload_Item_Type>> sortedPayload; 
        
            // Copy key-value pair from Map 
            // to vector of pairs 
            for (auto& it : Payload) { 
                sortedPayload.push_back(it); 
            } 
        
            // Sort using comparator function 
            std::sort(sortedPayload.begin(), sortedPayload.end(),  
            [](std::pair<TAG, Payload_Item_Type>& a, 
                std::pair<TAG, Payload_Item_Type>& b) -> bool
            { 
               return a.second.Position < b.second.Position; 
            }); 
        
            // Print the sorted value 
            for (auto& it : sortedPayload) { 
               DOIP_Payload.insert(DOIP_Payload.end(), it.second.RawData.begin(), it.second.RawData.end());
            } 

            return DOIP_Payload;
        }
        
        return std::vector<uint8_t>();
    }


      void PayloadObject::initialize_PayloadItems()
      {
          //No implementation
      }
}