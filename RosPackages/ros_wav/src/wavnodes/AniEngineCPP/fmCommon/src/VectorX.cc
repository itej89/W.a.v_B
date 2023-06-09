
#include <algorithm>
#include "VectorX.h"

namespace fmCommon
{
    // template<typename T>
    std::vector<uint8_t> VectorX::subvector(std::vector<uint8_t> const &v, int m, int n) 
    {
        auto first = v.begin() + m;
        auto last = v.begin() + n + 1;
        std::vector<uint8_t> vector(first, last);
        return vector;
    }

    bool VectorX::contains(std::vector<std::vector<uint8_t>> const &v, std::vector<uint8_t>& a)
    {
         return ! (v.empty() ||
              std::find(v.begin(), v.end(), a) == v.end());
    }



}