#pragma once

#include <string>
#include <vector> 

#include "Constants/DB_Table_Columns.h"

#include "Servo_Calibration_Type.h"

using std::string;
using std::vector;

namespace fmDB
{
    class Servo_Data_Type
    {
        public:
            string Name;
            int Address;
            int Min_Angle;
            int Max_Angle;
            vector<Servo_Calibration_Type> SERVO_CALIBRATED_DATA;

            Servo_Data_Type(int ColumnCount, char **data,  char **columns)
            {
                DB_Table_Columns::SERVO_DATA_COLUMNS ColumnDefinitions;
                for(int i = 0; i<ColumnCount; i++){
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::NAME) == columns[i])
                    {
                        Name = data[i];
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::ADDRESS) == columns[i])
                    {
                        Address = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::MIN_ANGLE) == columns[i])
                    {
                        Min_Angle = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::MAX_ANGLE) == columns[i])
                    {
                        Max_Angle = atoi(data[i]);
                    }
                }
            }

            Servo_Data_Type(string name, int address, int min_Angle, int max_Angle)
            {
                Name = name;
                Address = address;
                Min_Angle = min_Angle;
                Max_Angle = max_Angle;
            }
    };
}