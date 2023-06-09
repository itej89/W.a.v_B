
#include "Framework/DOIPAccessImplementation.h"


namespace fmBoip
 {  

    std::shared_ptr<DOIPAccessImplementation> DOIPAccessImplementation::Instance(new DOIPAccessImplementation());

    bool DOIPAccessImplementation::Initialize(DOIPContextConvey* ContextConvey, DOIPContextResultConvey* ResultConvey)
    {
        int16_t result =  _Initialize(ContextConvey, ResultConvey);
        if(result == DIAGNOSTIC_STATUS::SUCCESS)
        {
            return true;
        }
        else
        {
             return false;
        }
    }
    
    void DOIPAccessImplementation::Uninitialize()
    {
        _UnInitialize();
    }
    
    bool DOIPAccessImplementation::SendScan()
    {
        int result =  AnnounceDiscover();
        if(result == DIAGNOSTIC_STATUS::SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    
    bool DOIPAccessImplementation::Connect(DOIPEntity Entity)
    {
        ConnectingEntity = Entity;  
        int result =   RoutingActivation(Entity);
        if(result == DIAGNOSTIC_STATUS::SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void DOIPAccessImplementation::Disconnect()
    {
        FinalizeDiag();
        DOIPSession::Instance->ResetSession();
        ConnectingEntity = DOIPEntity();
    }
    
    bool DOIPAccessImplementation::Send(std::vector<uint8_t> Data)  {
        
        int result = SendData(Data);
        if(result == DIAGNOSTIC_STATUS::SUCCESS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
 }