#include <string.h>
#include <unistd.h>
#include <functional>
#include <iostream>



#include "Framework/TransportLayer/UDPListen.h"
#include "Framework/TransportLayer/Helpers/RecievedData.h"
#include "Framework/TransportLayer/Helpers/TransportLayerHelper.h"
#include "Framework/DOIPLayer/DOIPSession.h"

namespace fmBoip
 {

    std::unique_ptr<UDPListen> UDPListen::Instance(new UDPListen());

    void UDPListen::UDPRxLoop()
    {
         RecievedData _RecievedData;
        if(RecieveWithTimeout(10, _RecievedData) && UDPClientConvey != nullptr)
        {
            UDPClientConvey->DataRecieved(_RecievedData);
        } 

    }

    /** \brief Initialize a UDP server object.
     *
     * This function initializes a UDP server object making it ready to
     * receive messages.
     *
     * The server address and port are specified in the constructor so
     * if you need to receive messages from several different addresses
     * and/or port, you'll have to create a server for each.
     *
     * The address is a string and it can represent an IPv4 or IPv6
     * address.
     *
     * Note that this function calls connect() to connect the socket
     * to the specified address. To accept data on different UDP addresses
     * and ports, multiple UDP servers must be created.
     *
     * \note
     * The socket is open in this process. If you fork() or exec() then the
     * socket will be closed by the operating system.
     *
     * \warning
     * We only make use of the first address found by getaddrinfo(). All
     * the other addresses are ignored.
     *
     * \exception udp_client_server_runtime_error
     * The udp_client_server_runtime_error exception is raised when the address
     * and port combinaison cannot be resolved or if the socket cannot be
     * opened.
     *
     * \param[in] addr  The address we receive on.
     * \param[in] port  The port we receive from.
     */
    void UDPListen::StartListening()
    {
        TransportLayerHelper _TransportLayerHelper;
        std::string _IP = _TransportLayerHelper.getWiFiAddress();
        //std::string _IP = "255.255.255.255";

        char decimal_port[16];
        snprintf(decimal_port, sizeof(decimal_port), "%d", DOIPSession::Instance->LOCAL_UDP_PORT);
        decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        int r(getaddrinfo(_IP.c_str(), decimal_port, &hints, &f_addrinfo));

        std::cout << "IP : " << _IP << "\n Port : " << DOIPSession::Instance->LOCAL_UDP_PORT << std::endl;

        if(r != 0 || f_addrinfo == NULL)
        {
            throw client_server_runtime_error(("invalid address or port for UDP socket: \"" + _IP + ":" + decimal_port + "\"").c_str());
        }

        f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM, IPPROTO_UDP);

        int broadcastPermission = 1;
        if(setsockopt(f_socket,SOL_SOCKET,SO_BROADCAST,&broadcastPermission,sizeof(broadcastPermission)) < 0)
        {
            throw client_server_runtime_error("could not set setsockopt for broadcast");
        }

        if(f_socket == -1)
        {
            freeaddrinfo(f_addrinfo);
            throw client_server_runtime_error(("could not create UDP socket for: \"" + _IP + ":" + decimal_port + "\"").c_str());
        }

        r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
       
        if(r != 0)
        {
            freeaddrinfo(f_addrinfo);
            close(f_socket);
            throw client_server_runtime_error(("could not bind UDP socket with: \"" + _IP + ":" + decimal_port + "\"").c_str());
        }

        std::function<void(void)>  looper = std::bind(&UDPListen::UDPRxLoop ,this);
        UDPRxLooper.Start(looper, 10);
    }



    /** \brief Clean up the UDP server.
     *
     * This function frees the address info structures and close the socket.
     */
    void UDPListen::StopListening()
    {
        UDPRxLooper.Stop();
        freeaddrinfo(f_addrinfo);
        close(f_socket);
    }

    /** \brief The socket used by this UDP server.
     *
     * This function returns the socket identifier. It can be useful if you are
     * doing a select() on many sockets.
     *
     * \return The socket of this UDP server.
     */
    int UDPListen::get_socket() const
    {
        return f_socket;
    }

    /** \brief Wait on a message.
     *
     * This function waits until a message is received on this UDP server.
     * There are no means to return from this function except by receiving
     * a message. Remember that UDP does not have a connect state so whether
     * another process quits does not change the status of this UDP server
     * and thus it continues to wait forever.
     *
     * Note that you may change the type of socket by making it non-blocking
     * (use the get_socket() to retrieve the socket identifier) in which
     * case this function will not block if no message is available. Instead
     * it returns immediately.
     *
     * \param[in] msg  The buffer where the message is saved.
     * \param[in] max_size  The maximum size the message (i.e. size of the \p msg buffer.)
     *
     * \return The number of bytes read or -1 if an error occurs.
     */
    // int UDPListen::recv(char *msg, size_t max_size)
    // {
    //     return ::recv(f_socket, msg, max_size, 0);
    // }

    /** \brief Wait for data to come in.
     *
     * This function waits for a given amount of time for data to come in. If
     * no data comes in after max_wait_ms, the function returns with -1 and
     * errno set to EAGAIN.
     *
     * The socket is expected to be a blocking socket (the default,) although
     * it is possible to setup the socket as non-blocking if necessary for
     * some other reason.
     *
     * This function blocks for a maximum amount of time as defined by
     * max_wait_ms. It may return sooner with an error or a message.
     *
     * \param[in] msg  The buffer where the message will be saved.
     * \param[in] max_size  The size of the \p msg buffer in bytes.
     * \param[in] max_wait_ms  The maximum number of milliseconds to wait for a message.
     *
     * \return -1 if an error occurs or the function timed out, the number of bytes received otherwise.
     */
    bool UDPListen::RecieveWithTimeout(int max_wait_ms, RecievedData &recievedData)
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
         

            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(clientAddr.sin_addr), ip, INET_ADDRSTRLEN); 
            std::string strIP(ip);

            std::vector<uint8_t> Frame(Data, Data+recvlen);

            // delete [] Data;

            recievedData.RemoteEndPoint.IPAddress = strIP;
            recievedData.RemoteEndPoint.Port = clientAddr.sin_port;
            recievedData.recvBuffer.insert(recievedData.recvBuffer.end(), Frame.begin(), Frame.end());

            return true;


        }

        // our socket has no data
        errno = EAGAIN;
        return false;
    }


 }