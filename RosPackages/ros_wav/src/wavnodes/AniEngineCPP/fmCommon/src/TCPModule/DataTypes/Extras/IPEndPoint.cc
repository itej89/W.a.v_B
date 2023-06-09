#include "TCPModule/DataTypes/Extras/IPEndPoint.h"


namespace fmCommon
{
     IPEndPoint::IPEndPoint()
     {
        IPAddress = "";
        Port = -1;
     }
        
    IPEndPoint::IPEndPoint(std::string _IPAddress, int _Port)
    {
        IPAddress = _IPAddress;
        Port = _Port;
    }
}