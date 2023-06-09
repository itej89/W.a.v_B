#pragma once

#include <string>

#include "Framework/DataTypes/Extras/IPEndPoint.h"

namespace fmBoip
{
    class DOIPContextResultConvey
    {
        public:
            virtual void  InitializeResultNotify(int result) = 0;
            virtual void  UDSSendResultNotify(int result) = 0;
            virtual void  LinkDisconnected() = 0;
            virtual void  LinkConnected(IPEndPoint EndPoint) = 0;
    };
}