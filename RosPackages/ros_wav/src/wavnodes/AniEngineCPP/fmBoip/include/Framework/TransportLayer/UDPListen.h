#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <memory>

#include "ThreadX.h"

#include "Framework/Validation/interface/IValidation.h"
#include "Framework/DataTypes/Extras/IPEndPoint.h"
#include "Framework/TransportLayer/Helpers/RecievedData.h"
#include "Framework/DataTypes/Extras/TransportClientConvey.h"

namespace fmBoip
{


class UDPListen  : public IValidation
{
    public:
        static std::unique_ptr<UDPListen> Instance;
        std::shared_ptr<TransportClientConvey> UDPClientConvey = nullptr;
        int                 get_socket() const;

        // int                 recv(char *msg, size_t max_size);
        // int                 timed_recv(char *msg, size_t max_size, int max_wait_ms);

        void StartListening();
        void StopListening();
        // void StartListeningTimeOut();
        // bool Validate();

    private:
        int                 f_socket;
        struct addrinfo *   f_addrinfo;

        fmCommon::ThreadX UDPRxLooper;
        bool RecieveWithTimeout(int max_wait_ms, RecievedData &recievedData);
    
        void UDPRxLoop();
};

} 