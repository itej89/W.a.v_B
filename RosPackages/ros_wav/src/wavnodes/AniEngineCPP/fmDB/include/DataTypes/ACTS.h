#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class ACTS
    {
        public:
        int ID;
        string Name;
        string Audio;

        ACTS(int ColumnCount, char **data,  char **columns)
        {
            DB_Table_Columns::ACTS_COLUMNS ColumnDefinitions;
            for(int i = 0; i<ColumnCount; i++){
                if(ColumnDefinitions.toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_NAME) == columns[i])
                {
                    Name = (data[i]);
                }
                else
                if(ColumnDefinitions.toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_AUDIO) == columns[i])
                {
                    Audio = (data[i]);
                }
            }
        }

        ACTS(string name, int id)
        {
            Name = name;
            ID = id;
            Audio = "";
        }

        ACTS(string name, int id, string audio)
        {
            ID = id;
            Name = name;
            Audio = audio;
        }
    };
}