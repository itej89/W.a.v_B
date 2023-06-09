#pragma once

#include <string>


namespace fmBoip
{
    class IPEndPoint
    {
    public:
        std::string IPAddress;
        int Port;
        
        IPEndPoint();
        
        IPEndPoint(std::string _IPAddress, int _Port);
    };
}