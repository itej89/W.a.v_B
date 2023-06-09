#pragma once

#include <string>
#include <map>

namespace fmBotConnect
{
    class ANIMSG
    {
        public:
        enum CODE
        {
            CATEGORY_ACK,
            DATA_ACK,
            COMMAND_ACK,
            REQEST_UPLOAD_ACK,
            UPLOAD_END_ACK,
            LINK_ACK,
            BIND,
            UNBIND,
            STREAM_ACK,
            REQUEST,
            NA
        }; 

          
        std::map<CODE, std::string> CODE_TO_STRING = {
            {CATEGORY_ACK, "CATEGORY_ACK"},
            {DATA_ACK, "DATA_ACK"},
            {COMMAND_ACK, "COMMAND_ACK"},
            {REQEST_UPLOAD_ACK, "REQEST_UPLOAD_ACK"},
            {UPLOAD_END_ACK, "UPLOAD_END_ACK"},
            {LINK_ACK, "LINK_ACK"},
            {BIND, "BIND"},
            {UNBIND, "UNBIND"},
            {STREAM_ACK, "STREAM_ACK"},
            {REQUEST, "REQUEST"},
            {NA, "NA"}
        };

        std::map<std::string, CODE> STRING_TO_CODE = {
            {"CATEGORY_ACK", CATEGORY_ACK},
            {"DATA_ACK", DATA_ACK},
            {"COMMAND_ACK", COMMAND_ACK},
            {"REQEST_UPLOAD_ACK", REQEST_UPLOAD_ACK},
            {"UPLOAD_END_ACK", UPLOAD_END_ACK},
            {"LINK_ACK", LINK_ACK},
            {"BIND", BIND},
            {"UNBIND", UNBIND},
            {"STREAM_ACK", STREAM_ACK},
            {"REQUEST", REQUEST},
            {"NA", NA}
        };

        ANIMSG();
    };
}