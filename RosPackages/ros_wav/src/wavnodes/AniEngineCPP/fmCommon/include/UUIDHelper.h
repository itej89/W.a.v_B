#pragma once

#include <sstream>
#include <random>
#pragma once

#include <string>

using std::string;
using std::vector;

namespace fmCommon
{

class UUIDHelper
{
    public:
        unsigned int random_char();

        std::string generate_hex(const unsigned int len);
    };
}
