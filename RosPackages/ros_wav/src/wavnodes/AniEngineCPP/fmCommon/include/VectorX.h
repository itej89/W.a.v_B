#pragma once

#include <vector>

#include "UUIDHelper.h"

namespace fmCommon
{
    // template<typename T>
    class VectorX
    {
        public:
           std::vector<uint8_t> subvector(std::vector<uint8_t> const &v, int m, int n);
           bool contains(std::vector<std::vector<uint8_t>> const &v, std::vector<uint8_t>& a);

    };
    
}