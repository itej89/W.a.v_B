#include <string.h>
#include <functional>

#include "Framework/TransportLayer/TcpClient.h"
#include "Framework/Validation/DIAGNOSTIC_STATUS.h"

namespace fmBoip
 {


    std::unique_ptr<TcpClient> TcpClient::Instance(new TcpClient());

    bool TcpClient::Validate()
    {
        if(DOIPSession::Instance->RemoteEndPoint.IPAddress == "" || DOIPSession::Instance->RemoteEndPoint.Port == -1)
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY, "Remote end point empty", ""));
        }
        if(!TransportLayerHelper::NetworkAvailable())
        {
            ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::NETWORK_DISCONN, "Network disconnected", ""));
        }
        if(ValidationErrors.Messages.size() > 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }


        bool TcpClient::ValidateBeforeSend()
        {
            if(DOIPSession::Instance->RemoteEndPoint.IPAddress == "" || DOIPSession::Instance->RemoteEndPoint.Port == -1)
            {
                ValidationErrors.add(ValidationRuleMessage(VALIDATION_ERROR_CODES::EMPTY,  "Remote end point empty",  ""));
            }
            if(!TransportLayerHelper::NetworkAvailable())
            {
                ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::NETWORK_DISCONN,  "Networkk disconnected",  ""));
            }
             if(f_socket != 0)
            {
                ValidationErrors.add( ValidationRuleMessage( VALIDATION_ERROR_CODES::REMOTE_SOCKET_DISCONN,  "Socket disconnected",  ""));
            }

            if(ValidationErrors.Messages.size() > 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }


        void TcpClient::TcpClientInit()
        {
            if(Validate())
            {
                _TimeInterval = DOIPParameters::Instance->DOIP_TCP_RESPONSE_WAIT_TIME;
                 Timeout_return_code = DIAGNOSTIC_STATUS::TCP_TIMEOUT;
            }
        }



        void TcpClient::TCPRxLoop()
        {
            RecievedData _RecievedData;

            if(RecieveWithTimeout(10, _RecievedData) && ClientConvey != nullptr)
            {
                ClientConvey->DataRecieved(_RecievedData);
            }
        }


        void TcpClient::Disconnect()
        { 
            if(f_socket != -1)
            {
                close(f_socket);
            }

            f_socket = -1; f_conn = -1;
        }


        bool TcpClient::TryConnect(IPEndPoint endpoint)
        {

            if(f_conn == 0)
                return true;

            // DOIPSession::Instance->RemoteEndPoint.IPAddress = "192.168.0.170";
            //  DOIPSession::Instance->RemoteEndPoint.Port = 13400;
             
            f_socket = socket(AF_INET, SOCK_STREAM, 0);

            //Conver for printing
            char decimal_port[16];
            snprintf(decimal_port, sizeof(decimal_port), "%d",endpoint.Port);
            decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';



            if(f_socket == -1)
            {
                freeaddrinfo(f_addrinfo);
                throw client_server_runtime_error(("could not create TCP socket for: \"" + endpoint.IPAddress + ":" + decimal_port + "\"").c_str());
            }


            struct sockaddr_in servaddr, cli;

             // assign IP, PORT 
            servaddr.sin_family = AF_INET; 
            servaddr.sin_addr.s_addr = inet_addr(endpoint.IPAddress.c_str()); 
            servaddr.sin_port = htons(endpoint.Port); 
        
            // connect the client socket to server socket 
            f_conn = connect(f_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
            
             if(f_conn != 0)
            {

                close(f_socket);
                throw client_server_runtime_error(("could not connect to TCP server for: \"" + endpoint.IPAddress + ":" + decimal_port + "\"").c_str());
            }


            RemoteEndPoint = IPEndPoint(endpoint.IPAddress, endpoint.Port);
            return true;


        }



      bool TcpClient::RecieveWithTimeout(int max_wait_ms, RecievedData &recievedData)
        {
            try
            {
                fd_set s;
                FD_ZERO(&s);
                FD_SET(f_socket, &s);
                struct timeval timeout;
                timeout.tv_sec = max_wait_ms / 1000;
                timeout.tv_usec = (max_wait_ms % 1000) * 1000;
                int retval = select(f_socket + 1, &s, NULL, NULL, &timeout);
                if(retval == -1)
                {
                    // select() set errno accordingly
                    return false;
                }
                if(retval > 0)
                {

                    char* Data = new char[1000];

                    struct sockaddr_in clientAddr;
                    socklen_t clientAddrLen = sizeof(clientAddr); 

                    // our socket has data
                    int recvlen = recvfrom(f_socket, Data, 1000, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
                
                    if(recvlen > 0)
                    {
                        TimeOut.stop();
                        char ip[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &(clientAddr.sin_addr), ip, INET_ADDRSTRLEN); 
                        std::string strIP(ip);


                        IPEndPoint _RemoteEndPoint(RemoteEndPoint.IPAddress, RemoteEndPoint.Port);

                        std::vector<uint8_t> Frame(Data, Data+recvlen);
                        delete [] Data;

                        recievedData.RemoteEndPoint = _RemoteEndPoint;
                        recievedData.recvBuffer = Frame;

                        return  true;
                    }
                    else
                    {
                        delete [] Data;
                        return  false;
                    }

                }

                // our socket has no data
                errno = EAGAIN;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            return false;
        }


        bool TcpClient::IsTCPConnected()
        {
             unsigned char buf;
             int err = recv(f_socket, &buf,1,MSG_PEEK | MSG_DONTWAIT);
           
            if(err ==  0)
            {
                f_conn= -1;  f_socket=-1;
                return false;
            }

            return true;
        }


        void TcpClient::SendData(std::vector<uint8_t> Frame)
        {
            if(ValidateBeforeSend())
            { 
                RxLooper = std::bind(&TcpClient::TCPRxLoop ,this);
               
                write(f_socket, (const char *)&Frame[0], Frame.size());
                TCPRxLooper.Start(RxLooper, 10);
               // StartListeningTimeOut();
            }
        }

        void TcpClient::Timeout_Elapsed() {
            TCPRxLooper.Stop();
            if(ClientConvey != nullptr)
            {
                ClientConvey->Timeout(Timeout_return_code);
            }
        }

        void TcpClient::StartListeningTimeOut()
        {

            std::function<void(void)>  looper = std::bind(&TcpClient::Timeout_Elapsed ,this);
            TimeOut.setTimeoutTimer(looper, _TimeInterval);
        }
    
        TcpClient::~TcpClient()
        {

        }

 }