#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class Captured_Command_Type
    {
        public:
            string Name;
            string Command;

        

            Captured_Command_Type(string name, string command)
            {
                Name = name;
                Command = command;
            }
    };
}