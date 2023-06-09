#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/DOIPLayer/DOIPSession.h"

namespace fmBoip
{

    std::unique_ptr<DOIPSession> DOIPSession::Instance(new DOIPSession());

   

    uint8_t  DOIPSession::InverseProtocolVersion()
    {
        return ProtocolVersion ^ 0xFF;
    }
    
      std::vector<std::vector<uint8_t>> DOIPSession::getInvalidAddresses() 
    {
        InvalidAddresses = {{0xE0, 0x00}, {0x0F, 0xFF}};
        return InvalidAddresses;
    }
    
    std::vector<uint8_t>  DOIPSession::getValidProtocolVersions()
    {
        ValidProtocolVersions = {0xFF, 0x01, 0x02};
        return ValidProtocolVersions;
    }

    std::vector<uint8_t>  DOIPSession::getValidFurtherActions()
    {
        ValidFurtherActions = {0x01, 0x0F};
        return ValidFurtherActions;
    }
    
    uint8_t  DOIPSession::DefaultInverseProtocolVersion()
    {
        return DefaultProtocolVersion ^ 0xFF;
    }

   void DOIPSession::ResetSession()
    {
        RemoteEndPoint.IPAddress = DOIPParameters::Instance->DOIP_Entity_IPAddress;
        RemoteEndPoint.Port = DOIPParameters::Instance->DOIP_ENTITY_UDP_DISCOVER;
        
        LOCAL_UDP_PORT = DOIPParameters::Instance->TESTER_UDP_PORT;
        
        LOCAL_TCP_PORT = 13400;
    }
}
