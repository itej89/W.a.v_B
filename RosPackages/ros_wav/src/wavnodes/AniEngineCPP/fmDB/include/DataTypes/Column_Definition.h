#pragma once

#include <string>

using std::string;

namespace fmDB
{
    class Column_Definition
    {
        public:
            string ColumnName;
            string ColumnType;

            Column_Definition(string columnName, string columnType)
            {
                ColumnName = columnName;
                ColumnType = columnType;
            }
    };
}