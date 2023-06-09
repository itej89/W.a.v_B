#include <unistd.h>
#include <limits.h>


#include "memory"
#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>

#include "mock_serial.h"
#include "serial_access_test.h"

using ::testing::Return;
using json = nlohmann::json;

ACTION_TEMPLATE(SetArgNPointeeTo, HAS_1_TEMPLATE_PARAMS(unsigned, uIndex), AND_2_VALUE_PARAMS(pData, uiDataSize))
{
    std::memcpy(std::get<uIndex>(args), pData, uiDataSize);
}


    uint8_t rcvBuffer[] = "TMG#6#1000#O:";
    size_t bufferSize = sizeof("TMG#6#1000#O:");

serial_access_test::serial_access_test()
{
    // ON_CALL(*m_serial,isOpen()).WillByDefault(Return(true));

    // EXPECT_CALL( *m_serial, readToBuffer( testing::_, testing::_) )
    // .WillRepeatedly( testing::DoAll(
    //     SetArgNPointeeTo<0>(std::begin(rcvBuffer), bufferSize),
    //     testing::Return( 13  ) ) );

}

TEST_F(serial_access_test, PortOpenCloseSequence) {
    Serial_Access serial_access;
    serial_access.SetCommsDelegate(m_serial_access_notify);
    EXPECT_EQ(serial_access.InitializeComms(), true);
    EXPECT_EQ(serial_access.IsConnectedToPeripheral(), true);

    // char exec_path_buff[PATH_MAX];
    // ssize_t len = ::readlink("/proc/self/exe", exec_path_buff, sizeof(exec_path_buff)-1);
    // string exec_path(exec_path_buff); 
    // std::ifstream Command_file(exec_path.substr(0,exec_path.find_last_of("//"))+"/CommandList.txt");
     

    // if(Command_file.good()) 
    //     std::cout << "true" << std::endl;

    // json j;
    // Command_file >> j; 


    //  for (int i=0; i<2; i++)
    //  {
    //      string Tx = j["Commands"][i]["Tx"].get<string>();
    //     EXPECT_EQ(serial_access.SendString(Tx), Tx.size());
    //     string Rx = j["Commands"][i]["Rx"].get<string>();
    //     EXPECT_CALL(*m_serial_access_notify, stringRecieved(Rx)); // << "i is : " << i << std::endl;
    //     usleep(100000);
       
    //  }

    

    EXPECT_EQ(serial_access.DisconnectDevice(), true);
}

