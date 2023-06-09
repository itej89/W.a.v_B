#pragma once

namespace fmKinetics
{

    class MachineCommsStates
    {

    public:
        enum etype
        {
            READY_TO_SCAN,
            POWERED_ON,
            POWERED_OFF,
            SCANNING,
            SCANNING_TIMEOUT,
            CONNECTING,
            CONNECTION_FAIL,
            CONNECTION_TIMEOUT,
            CONNECTED,
            DISCONNECTING,
            DISCONNECTED,
            UNKNOWN
        };
        
        etype Value = UNKNOWN;
    };

}