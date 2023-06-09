
#include "Framework/TransportLayer/Helpers/RecievedData.h"

namespace fmBoip
 {
    RecievedData::RecievedData(IPEndPoint _RemoteEndPoint, std::vector<uint8_t> _recvBuffer)
    {
        RemoteEndPoint = _RemoteEndPoint;
        recvBuffer = _recvBuffer;
    }

     RecievedData::RecievedData(){}
}