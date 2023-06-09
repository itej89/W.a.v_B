#pragma once

namespace fmSerial
{
    enum CommsStates {
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
};