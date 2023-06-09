#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class Expressions_Type
    {
        public:
            int ID;
            string Name;
            string Action_Data;
            float JOY;
            float SURPRISE;
            float FEAR;
            float SADNESS;
            float ANGER;
            float DISGUST;

           

            Expressions_Type(string name, string action_Data, float joy, float surprise, float fear, float sadness, float anger, float disgust)
            {
                Name = name;
                Action_Data = action_Data;
                JOY = joy;
                SURPRISE = surprise;
                FEAR = fear;
                SADNESS = sadness;
                ANGER = anger;
                DISGUST = disgust;
            }

            Expressions_Type(int id, string name, string action_Data, float joy, float surprise, float fear, float sadness, float anger, float disgust)
            {
                ID = id;
                Name = name;
                Action_Data = action_Data;
                JOY = joy;
                SURPRISE = surprise;
                FEAR = fear;
                SADNESS = sadness;
                ANGER = anger;
                DISGUST = disgust;
            }
    };
}