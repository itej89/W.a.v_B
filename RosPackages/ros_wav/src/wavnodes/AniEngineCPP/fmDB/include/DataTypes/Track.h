#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class Track
    {
        public:
            int ID;
            char *_Track;

            Track(){}
            Track(int _ID, char* _track)
            {
                ID = _ID;
                _Track = _track;
            }
    };
}