#pragma once

#include <string>
#include <map>

namespace fmBotConnect
{
    class ANSTMSG
    {
        public:
        enum CODE
        {
             CATEGORY,
             DATA,
             COMMAND,
             REQEST_UPLOAD,
             UPLOAD_END,
             LINK,
             STREAM,
             REQUEST_ACK,
             NA
        };

         std::map<CODE, std::string> CODE_TO_STRING = {
            {CATEGORY, "CATEGORY"},
            {DATA, "DATA"},
            {COMMAND, "COMMAND"},
            {REQEST_UPLOAD, "REQEST_UPLOAD"},
            {UPLOAD_END, "UPLOAD_END"},
            {LINK, "LINK"},
            {STREAM, "STREAM"},
            {REQUEST_ACK, "REQUEST_ACK"},
            {NA, "NA"}
        };

        std::map<std::string, CODE> STRING_TO_CODE = {
                {"CATEGORY", CATEGORY},
                {"DATA", DATA},
                {"COMMAND", COMMAND},
                {"REQEST_UPLOAD", REQEST_UPLOAD},
                {"UPLOAD_END", UPLOAD_END},
                {"LINK", LINK},
                {"STREAM", STREAM},
                {"REQUEST_ACK", REQUEST_ACK},
                {"NA", NA}
        };

      ANSTMSG();
      
    };
}