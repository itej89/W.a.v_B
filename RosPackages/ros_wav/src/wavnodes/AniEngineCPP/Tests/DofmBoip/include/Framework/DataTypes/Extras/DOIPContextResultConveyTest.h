#pragma once

#include <memory>

#include "Framework/DataTypes/Extras/DOIPContextResultConvey.h"


using namespace fmBoip;

class DOIPContextResultConveyTest: public DOIPContextResultConvey
{
    public:
        void  InitializeResultNotify(int result);
        void  UDSSendResultNotify(int result);
        void  LinkDisconnected();
        void  LinkConnected(IPEndPoint EndPoint);
};