#include <iostream>

#include "Framework/DOIPAccessImplementationTest.h"
#include "Framework/DataTypes/Extras/DOIPContextConveyTest.h"


void DOIPContextConveyTest::FoundDOIPEntity(DOIPEntity Entity)
{
    tSendScan.Stop();
    DOIPAccessImplementation::Instance->Connect(Entity);
}

void DOIPContextConveyTest::StartScan()
{
    std::function<void(void)>  looper = std::bind(&DOIPContextConveyTest::Scan ,this);
    tSendScan.Start(looper, 3000);
}

void DOIPContextConveyTest::Scan()
{
    DOIPAccessImplementation::Instance->SendScan();
}

void DOIPContextConveyTest::UDSResponseRecieved(std::vector<uint8_t> response)
{

}