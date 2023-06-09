#include <unistd.h>
#include <iostream>
#include <limits.h>

#include "DataTypes/Column_Definition.h"

#include "DB_Local_Store_Test.h"

using namespace fmDB;


DB_Local_Store_Test::DB_Local_Store_Test()
{

}

TEST_F(DB_Local_Store_Test, DB_Local_Store_Test) {
    char exec_path_buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exec_path_buff, sizeof(exec_path_buff)-1);
    string exec_path(exec_path_buff); 
    DB_Local_Store *m_DB_Local_Store  = new DB_Local_Store(exec_path.substr(0,exec_path.find_last_of("//"))+"/CommandStore.db");
    vector<Servo_Calibration_Type> servo_Calib =  m_DB_Local_Store->ReadServoCalibrationData("SERVO_TURN");
    Expressions_Type expressions_Type =  m_DB_Local_Store->readExpression("fear");
    expressions_Type = m_DB_Local_Store->readExpressionByEmotion(0.9, 0,0,0,0,0);
    Machine_Position_Type machinePosition = m_DB_Local_Store->ReadMachinePositionByName("DENAP_POSITION");
    printf("Action Data : %d : Action End", machinePosition.TILT);
    m_DB_Local_Store->CloseDBConnection();
}