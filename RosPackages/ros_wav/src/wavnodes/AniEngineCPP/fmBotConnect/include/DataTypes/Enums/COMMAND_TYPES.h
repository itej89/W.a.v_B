#pragma once

#include <string>
#include <map>

namespace fmBotConnect
{
    class COMMAND_TYPES
    {
        public:
        enum CODE
        {
             PLAY_EMSYNTH,
             STOP_EMSYNTH,
             PLAY_CHOREOGRAM,
             STOP_CHOREOGRAM,
             PLAY_TELTALE,
             STOP_TELTALE,
             NA
        };

        std::map<CODE, std::string> CODE_TO_STRING = {
            {PLAY_EMSYNTH, "PLAY_EMSYNTH"},
            {STOP_EMSYNTH, "STOP_EMSYNTH"},
            {PLAY_CHOREOGRAM, "PLAY_CHOREOGRAM"},
            {STOP_CHOREOGRAM, "STOP_CHOREOGRAM"},
            {PLAY_TELTALE, "PLAY_TELTALE"},
            {STOP_TELTALE, "STOP_TELTALE"},
            {NA, "NA"}
        };

        std::map<std::string, CODE> STRING_TO_CODE = {
                {"PLAY_EMSYNTH", PLAY_EMSYNTH},
                {"STOP_EMSYNTH", STOP_EMSYNTH},
                {"PLAY_CHOREOGRAM", PLAY_CHOREOGRAM},
                {"STOP_CHOREOGRAM", STOP_CHOREOGRAM},
                {"PLAY_TELTALE", PLAY_TELTALE},
                {"STOP_TELTALE", STOP_TELTALE},
                {"NA", NA}
        };

        COMMAND_TYPES();
    };
}