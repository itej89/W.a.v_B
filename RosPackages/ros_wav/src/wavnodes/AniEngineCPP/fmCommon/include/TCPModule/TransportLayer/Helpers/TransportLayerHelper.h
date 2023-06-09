#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#include <string>
#include <vector>

#include "TCPModule/DataTypes/Extras/IPEndPoint.h"

namespace fmCommon
 {


    class client_server_runtime_error : public std::runtime_error
    {
        public:
            client_server_runtime_error(const char *w) : std::runtime_error(w) {}
    };


    class TransportLayerHelper {

        public:

            static void check_host_name(int hostname);

            static void check_host_entry(struct hostent * hostentry);

            static void IP_formatter(char *IPbuffer);

            static std::string LocalIPAddress();

            static bool NetworkAvailable();

            static bool validateIpAddress(const std::string &ipAddress);
            
            static bool isConnectedToNetwork();
            
            static std::string getWiFiAddress();

            int FetchLocalPort();

    };

}