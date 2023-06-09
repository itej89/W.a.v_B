#pragma once

#include <string>
#include <zlib.h>


class ZlibHelper
{
private:
    /* data */
public:
std::vector<char> compress(const std::string& str,
                            int compressionlevel= Z_BEST_COMPRESSION);

    std::string compress_string(const std::string& str,
                            int compressionlevel = Z_BEST_COMPRESSION);

    std::string decompress_string(const std::string& str);
};
