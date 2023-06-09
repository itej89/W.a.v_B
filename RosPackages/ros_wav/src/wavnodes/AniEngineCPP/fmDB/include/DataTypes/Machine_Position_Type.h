#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class Machine_Position_Type
    {
        public:
            string Name;
            int TURN;
            int LIFT;
            int LEAN;
            int TILT;

            Machine_Position_Type(int ColumnCount, char **data,  char **columns)
            {
                DB_Table_Columns::MACHINE_POSITIONS_COLUMNS ColumnDefinitions;
                for(int i = 0; i<ColumnCount; i++){
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::NAME) == columns[i])
                    {
                        Name = (data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::TURN) == columns[i])
                    {
                        TURN = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::LIFT) == columns[i])
                    {
                        LIFT = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::LEAN) == columns[i])
                    {
                        LEAN = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::TILT) == columns[i])
                    {
                        TILT = atoi(data[i]);
                    }
                }
            }


            Machine_Position_Type()
            {
                
            }

            Machine_Position_Type(string name, int turn, int lift, int lean, int tilt)
            {
                Name = name;
                TURN = turn;
                LIFT = lift;
                LEAN = lean;
                TILT = tilt;
            }

            Machine_Position_Type(string name)
            {
                Name = name;
            }
    };
}