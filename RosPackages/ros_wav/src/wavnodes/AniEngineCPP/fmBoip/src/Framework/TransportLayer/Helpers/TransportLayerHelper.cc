
#include "StringX.h"
#include "Framework/TransportLayer/Helpers/TransportLayerHelper.h"

namespace fmBoip
 {
     void TransportLayerHelper::check_host_name(int hostname) { //This function returns host name for local computer
            if (hostname == -1) {
                perror("gethostname");
                exit(1);
            }
        }
        void TransportLayerHelper::check_host_entry(struct hostent * hostentry) { //find host info from host name
            if (hostentry == NULL){
                perror("gethostbyname");
                exit(1);
            }
        }
        void TransportLayerHelper::IP_formatter(char *IPbuffer) { //convert IP string to dotted decimal format
            if (NULL == IPbuffer) {
                perror("inet_ntoa");
                exit(1);
            }
        }

         std::string TransportLayerHelper::LocalIPAddress()
        {
            if(NetworkAvailable() == false)
            {
                return "";
            }
            
            return getWiFiAddress();
        }

         bool TransportLayerHelper::NetworkAvailable()
        {
            if(isConnectedToNetwork())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

         bool TransportLayerHelper::validateIpAddress(const std::string &ipAddress)
        {
            struct sockaddr_in sa;
            int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
            return result != 0;
        }
        
         bool TransportLayerHelper::isConnectedToNetwork()  {
            return validateIpAddress(getWiFiAddress());
        }
        
         std::string TransportLayerHelper::getWiFiAddress()  {

            struct ifaddrs *ifap, *ifa;
            struct sockaddr_in *sa;
            char *addr;

            getifaddrs (&ifap);
            for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
                    sa = (struct sockaddr_in *) ifa->ifa_addr;
                    addr = inet_ntoa(sa->sin_addr);
                    printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
                    fmCommon::StringX strX;
                    if(strX.startsWith( ifa->ifa_name, "wl"))
                    {
                         freeifaddrs(ifap);
                        return addr;
                    }
                }
            }


            freeifaddrs(ifap);

            return "";
    
            // char host[256];
            // char *IP;
            // struct hostent *host_entry;
            // int hostname;
            // hostname = gethostname(host, sizeof(host)); //find the host name

            // check_host_name(hostname);
            // host_entry = gethostbyname(host); //find host information
            // check_host_entry(host_entry);
            // IP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); //Convert into IP string

            // std::string  s
        }

        int TransportLayerHelper::FetchLocalPort()
        {
            int LocalPort = -1;
            srand (time(NULL));
            /* generate secret number between 1 and 10: */
            int iSecret = rand() % 10 + 1;
            LocalPort = iSecret + 13400;
            return LocalPort;
        }

}