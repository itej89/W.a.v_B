#include "Framework/Validation/VALIDATION_ERROR_CODES.h"

namespace fmBoip
 {
        VALIDATION_ERROR_CODES::VALIDATION_ERROR_CODES()
        {
            enumtostring.insert(std::make_pair<eType, std::string>(FAIL, "FAIL"));
            enumtostring.insert(std::make_pair<eType, std::string>(EMPTY, "EMPTY"));
            enumtostring.insert(std::make_pair<eType, std::string>(INCORRECT_LENGTH, "INCORRECT_LENGTH"));
            enumtostring.insert(std::make_pair<eType, std::string>(INVALID_DATA, "INVALID_DATA"));
            enumtostring.insert(std::make_pair<eType, std::string>(NO_PAYLOAD_ITEMS_FOUND, "NO_PAYLOAD_ITEMS_FOUND"));
            enumtostring.insert(std::make_pair<eType, std::string>(NETWORK_DISCONN, "NETWORK_DISCONN"));
            enumtostring.insert(std::make_pair<eType, std::string>(EMPTY_SOCKET, "EMPTY_SOCKET"));
            enumtostring.insert(std::make_pair<eType, std::string>(REMOTE_SOCKET_DISCONN, "REMOTE_SOCKET_DISCONN"));
            enumtostring.insert(std::make_pair<eType, std::string>(REMOTE_SOCKET_REFUSED_CONN, "REMOTE_SOCKET_REFUSED_CONN"));
            enumtostring.insert(std::make_pair<eType, std::string>(NO_PREVIOUS_DIAGNOSTIC_DATA, "NO_PREVIOUS_DIAGNOSTIC_DATA"));
            enumtostring.insert(std::make_pair<eType, std::string>(NO_SOURCE_ADDRESS, "NO_SOURCE_ADDRESS"));
        }
 }