#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class DataContext
    {
        public:
            string KEY;
            string VALUE;

            DataContext(string key, string value)
            {
                KEY = key;
                VALUE = value;
            }
    };
}