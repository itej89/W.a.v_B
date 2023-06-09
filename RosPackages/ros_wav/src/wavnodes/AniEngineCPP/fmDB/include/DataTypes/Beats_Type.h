#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class Beats_Type
    {
        public:
         int Beat_Id;
         int Act_Id;
         string Action_Data;
         float JOY;
         float SURPRISE;
         float FEAR;
         float SADNESS;
         float ANGER;
         float DISGUST;
         int StartSec;
         int EndSec;

            Beats_Type(int ColumnCount, char **data,  char **columns)
            {
                DB_Table_Columns::BEATS_COLUMNS ColumnDefinitions;
                for(int i = 0; i<ColumnCount; i++)
                {
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::BEAT_ID) == columns[i])
                    {
                        Beat_Id = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::ACT_ID) == columns[i])
                    {
                        Act_Id = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::ACTION_DATA) == columns[i])
                    {
                        Action_Data = (data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::JOY) == columns[i])
                    {
                        JOY = atof(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::SURPRISE) == columns[i])
                    {
                        SURPRISE = atof(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::FEAR) == columns[i])
                    {
                        FEAR = atof(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::SADNESS) == columns[i])
                    {
                        SADNESS = atof(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::ANGER) == columns[i])
                    {
                        ANGER = atof(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::DISGUST) == columns[i])
                    {
                        DISGUST = atof(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::StartSec) == columns[i])
                    {
                        StartSec = atoi(data[i]);
                    }
                    else
                    if(ColumnDefinitions.toString.at(DB_Table_Columns::BEATS_COLUMNS::EndSec) == columns[i])
                    {
                        EndSec = atoi(data[i]);
                    }
                }
            }

         Beats_Type(int act_Id, int beat_ID, string action_Data, float joy, float surprise, float fear, float sadness, float anger, float disgust, int startSec, int endSec)
        {
            Act_Id = act_Id;
            Beat_Id = beat_ID;
            Action_Data = action_Data;
            JOY = joy;
            SURPRISE = surprise;
            FEAR = fear;
            SADNESS = sadness;
            ANGER = anger;
            DISGUST = disgust;
            StartSec = startSec;
            EndSec = endSec;
        }
    };
}