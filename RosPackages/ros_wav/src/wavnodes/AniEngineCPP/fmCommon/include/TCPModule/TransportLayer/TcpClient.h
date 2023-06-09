#pragma once

#include <stdint-gcc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <memory>

#include "Timer.h"
#include "ThreadX.h"

#include "TCPModule/DataTypes/Extras/IPEndPoint.h"
#include "TCPModule/TransportLayer/Helpers/TransportLayerHelper.h"
#include "TCPModule/DataTypes/Delegates/TransportClientConvey.h"


namespace fmCommon
{

    class TcpClient 
    {
        private:
            std::function<void(void)>  RxLooper;
            fmCommon::Timer TimeOut;
        

            int                 f_socket = -1, f_conn = -1;
            struct addrinfo *   f_addrinfo;

    
            fmCommon::ThreadX TCPRxLooper;
        public:
            IPEndPoint RemoteEndPoint;

            int _TimeInterval = 0;
            int Timeout_return_code = 0;
            static std::unique_ptr<TcpClient> Instance;
            std::shared_ptr<TransportClientConvey> ClientConvey = nullptr;


        bool Validate();

        bool ValidateBeforeSend();

        void TcpClientInit(std::string IP, int port);

        void TCPRxLoop();

        bool TryConnect(IPEndPoint endpoint);

        bool IsTCPConnected();

        bool RecieveWithTimeout(int max_wait_ms, RecievedData &recievedData);

        void Disconnect();

        void SendData(std::vector<uint8_t> Frame);

        void Timeout_Elapsed();

        void StartListeningTimeOut();
    
        ~TcpClient();
    };


}