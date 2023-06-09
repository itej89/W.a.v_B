#pragma once

#include <vector>
#include <memory>

#include "Framework/DataTypes/Extras/TransportClientConvey.h"
#include "Framework/DOIPAccess.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DoIPTesterContext.h"
#include "Framework/DataTypes/Extras/DOIPContextConvey.h"
#include "Framework/DataTypes/Extras/DOIPContextResultConvey.h"

namespace fmBoip
{
    
class DOIPAccessImplementation : public DoIPTesterContext//, public DOIPAccess
{
    public: 
    
        static std::shared_ptr<DOIPAccessImplementation> Instance;

        DOIPEntity ConnectingEntity;
        
        bool Initialize(DOIPContextConvey* ContextConvey, DOIPContextResultConvey* ResultConvey);

        void Uninitialize();
        
        bool SendScan();
        
        bool Connect(DOIPEntity Entity);
        
        void Disconnect();
        
        bool Send(std::vector<uint8_t> Data);
    
};

}