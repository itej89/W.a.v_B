#pragma once

#include <string>
#include <map>

namespace fmBotConnect
{
    class LINK_ANCHORS
    {
        public:
        enum CODE
        {
             JOY,
             HEART_MONITOR,
             NAVIGATION,
             NA
        }; 

          
        std::map<CODE, std::string> CODE_TO_STRING = {
            {JOY, "JOY"},
            {HEART_MONITOR, "HEART_MONITOR"},
            {NAVIGATION, "NAVIGATION"},
            {NA, "NA"}
        };

        std::map<std::string, CODE> STRING_TO_CODE = {
            {"JOY", JOY},
            {"HEART_MONITOR", HEART_MONITOR},
            {"NAVIGATION", NAVIGATION},
            {"NA", NA}
        };

        LINK_ANCHORS();
    };
}