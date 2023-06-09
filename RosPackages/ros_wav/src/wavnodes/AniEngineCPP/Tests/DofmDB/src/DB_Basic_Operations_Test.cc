#include <unistd.h>
#include <iostream>
#include <limits.h>

#include "DataTypes/Column_Definition.h"

#include "DB_Basic_Operations_Test.h"

using namespace fmDB;


DB_Basic_Operations_Test::DB_Basic_Operations_Test()
{

}

TEST_F(DB_Basic_Operations_Test, DB_Basic_Operations_Test) {

 char exec_path_buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exec_path_buff, sizeof(exec_path_buff)-1);
    string exec_path(exec_path_buff); 
    DB_Basic_Operations *m_DB_Basic_Operations  = new DB_Basic_Operations(exec_path.substr(0,exec_path.find_last_of("//"))+"/CommandStore.db");

    m_DB_Basic_Operations->InitializeDB();
    EXPECT_EQ(m_DB_Basic_Operations->IsOpen(), true);

    std::cout << (exec_path.substr(0,exec_path.find_last_of("//"))+"/CommandStore.db") << std::endl;

    vector<Column_Definition> columns;
    columns.push_back(Column_Definition("COL1", "INT"));
    columns.push_back(Column_Definition("COL2", "CHAR"));
    m_DB_Basic_Operations->CreateTable("TestTable", columns);

    m_DB_Basic_Operations->EmptyTable("CAPTURED_COMMANDS");

    vector<vector<string>>* DataTable = m_DB_Basic_Operations->ReadDataFromTable("SELECT * from EXPRESSIONS");

    printf("command count: %s : ", (DataTable->at(3))[2].c_str());

    m_DB_Basic_Operations->CloseDBConnection();
    // KineticsRequest *m_KineticsRequest = new KineticsRequest(CommandTypes::ANG);
    //     const char *vinit[] = {"6", "1500"};
    //     vector<string> items(vinit, std::end(vinit));
    // EXPECT_EQ(m_KineticsRequest->formCommand(items), "ANG#6#1500");

    // KineticsRequestAngle *m_KineticsRequestAngle = new KineticsRequestAngle(90, fmKinetics::Actuator::TURN);
    // EXPECT_EQ(m_KineticsRequestAngle->Request, "~ANG#6#1444:");
}