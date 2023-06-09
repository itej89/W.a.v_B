#include <vector>

#include <stdint-gcc.h>
#include "Framework/DataTypes/Extras/DOIPContextConvey.h"
#include "Framework/DataTypes/Extras/DOIPContextResultConvey.h"
#include "Framework/DataTypes/DOIP_OBJECTS/DOIPEntity.h"

namespace fmBoip
{
     class DOIPAccess
     {
        public:    
         bool Initialize(DOIPContextConvey* ContextConvey, DOIPContextResultConvey* ResultConvey);
        void Uninitialize();
        bool SendScan();
        bool Connect(DOIPEntity Entity);
        void Disconnect();
        bool Send(std::vector<uint8_t> Data);
    };  
}