#pragma once

#include <memory>

#include "Framework/DataTypes/Extras/TransportClientConvey.h"


using namespace fmBoip;

class TransportClientConveyTest: public TransportClientConvey
{
    public:
        void DataRecieved(RecievedData recievedData);
        void Disconnected();
        void Timeout(int code);
};