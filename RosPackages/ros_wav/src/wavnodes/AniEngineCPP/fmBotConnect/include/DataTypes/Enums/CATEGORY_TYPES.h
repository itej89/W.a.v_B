#pragma once

#include <string>
#include <map>

namespace fmBotConnect
{
    class CATEGORY_TYPES
    {
        public:
        enum CODE
        {
             EMSYNTH,
             CHOREOGRAM,
             TELTALE,
             NA
        };

        std::map<CODE, std::string> CODE_TO_STRING = {
            {EMSYNTH, "EMSYNTH"},
            {CHOREOGRAM, "CHOREOGRAM"},
            {TELTALE, "TELTALE"},
            {NA, "NA"}
        };

        std::map<std::string, CODE> STRING_TO_CODE = {
                {"EMSYNTH", EMSYNTH},
                {"CHOREOGRAM", CHOREOGRAM},
                {"TELTALE", TELTALE},
                {"NA", NA}
        };

        CATEGORY_TYPES();
    };
}