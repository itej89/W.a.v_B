#include <unistd.h>
#include <iostream>
#include <limits.h>

#include "SystemFlowManagerTest.h"

using namespace fmSystem;

SystemFlowManagerTest::SystemFlowManagerTest()
{

}

TEST_F(SystemFlowManagerTest, SystemFlowManagerTest) {
    std::shared_ptr<SystemFlowManager> systemFlowManagerTest{new SystemFlowManager()};
    systemFlowManagerTest->InitializeKineticsEngine();
    //systemFlowManagerTest->BindMachine();
    systemFlowManagerTest->AttenstionON();
    //systemFlowManagerTest->DisconnectKineticsEngine();


     while(true)
  {
usleep(3000000);

  }
}