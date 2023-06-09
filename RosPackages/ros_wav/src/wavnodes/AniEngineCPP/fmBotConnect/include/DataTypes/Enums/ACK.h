#pragma once

#include <string>
#include <map>

namespace fmBotConnect
{
    class ACK
    {
        public:
        enum CODE
        {
             OK,
             ERROR,
             WRONG_CLIENT_ID,
             INVALID_CATEGORY,
             INVALID_DATA,
             INVALID_COMMAND,
             CONNECTION_DENIED,
             MD5_MISMATCH,
             PART_MISSING,
             NA
        };

         
        std::map<CODE, std::string> CODE_TO_STRING = {
            {OK, "OK"},
            {ERROR, "ERROR"},
            {WRONG_CLIENT_ID, "WRONG_CLIENT_ID"},
            {INVALID_CATEGORY, "INVALID_CATEGORY"},
            {INVALID_DATA, "INVALID_DATA"},
            {INVALID_COMMAND, "INVALID_COMMAND"},
            {CONNECTION_DENIED, "CONNECTION_DENIED"},
            {MD5_MISMATCH, "MD5_MISMATCH"},
            {MD5_MISMATCH, "MD5_MISMATCH"},
            {PART_MISSING, "PART_MISSING"},
            {NA, "NA"}
        };

        std::map<std::string, CODE> STRING_TO_CODE = {
            {"OK", OK},
            {"ERROR", ERROR},
            {"WRONG_CLIENT_ID", WRONG_CLIENT_ID},
            {"INVALID_CATEGORY", INVALID_CATEGORY},
            {"INVALID_DATA", INVALID_DATA},
            {"INVALID_COMMAND", INVALID_COMMAND},
            {"CONNECTION_DENIED", CONNECTION_DENIED},
            {"MD5_MISMATCH", MD5_MISMATCH},
            {"MD5_MISMATCH", MD5_MISMATCH},
            {"PART_MISSING", PART_MISSING},
            {"NA", NA}
        };

        ACK();

    };
}