#pragma once

#include <memory>
#include "ThreadX.h"

#include "Framework/DataTypes/Extras/DOIPContextConvey.h"


using namespace fmBoip;

class DOIPContextConveyTest: public DOIPContextConvey
{
    public:

        fmCommon::ThreadX tSendScan;
        void FoundDOIPEntity(DOIPEntity Entity);
        void StartScan();
        void Scan();
        void UDSResponseRecieved(std::vector<uint8_t> response);
};