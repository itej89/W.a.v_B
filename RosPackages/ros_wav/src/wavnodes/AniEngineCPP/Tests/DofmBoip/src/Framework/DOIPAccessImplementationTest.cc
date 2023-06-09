#include <functional>

#include "Framework/DOIPAccessImplementationTest.h"
#include "Framework/DOIPLayer/DOIPStateMachines/DoIPTesterContext.h"



DOIPAccessImplementationTest::DOIPAccessImplementationTest()
{

}

TEST_F(DOIPAccessImplementationTest, DOIPAccessImplementationTest) {

   // static std::shared_ptr<DOIPAccessImplementation> _DOIPAccessImplementation(new DOIPAccessImplementation);

    _DOIPContextConveyTest = std::make_shared<DOIPContextConveyTest>();
    _DOIPContextResultConveyTest = std::make_shared<DOIPContextResultConveyTest>();

    if( DOIPAccessImplementation::Instance->Initialize(_DOIPContextConveyTest.get(), _DOIPContextResultConveyTest.get()))
    {
        _DOIPContextConveyTest->StartScan();
    }

      while(true)
      {
        usleep(3000000);
      }
}