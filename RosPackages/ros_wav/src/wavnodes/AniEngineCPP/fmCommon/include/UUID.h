#pragma once

#include <sstream>
#include <random>
#include <string>

#include "UUIDHelper.h"

using std::string;
using std::vector;

namespace fmCommon
{

    class UUID
    {
        public:
            string stringValue = "";
            UUID()
            {
                UUIDHelper _UUIDHelper;
                stringValue = _UUIDHelper.generate_hex(5);
                stringValue += "-"+_UUIDHelper.generate_hex(4);
                stringValue += "-"+_UUIDHelper.generate_hex(5);
                stringValue += "-"+_UUIDHelper.generate_hex(7);
                stringValue += "-"+_UUIDHelper.generate_hex(4);
            }
    };

}
