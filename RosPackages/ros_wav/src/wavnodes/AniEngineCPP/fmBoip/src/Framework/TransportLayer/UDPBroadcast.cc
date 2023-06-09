
#include <string.h>

#include <arpa/inet.h>  /* for sockaddr_in */

#include "Framework/Configuration/DOIPParameters.h"
#include "Framework/TransportLayer/UDPBroadcast.h"

namespace fmBoip
 {

    std::unique_ptr<UDPBroadcast> UDPBroadcast::Instance(new UDPBroadcast());
    
    void UDPBroadcast::UDPBroadcastPacket(std::vector<uint8_t> Frame)
    {

        struct sockaddr_in s;

        if(UDPListen::Instance->get_socket() < 0)
            return;

        memset(&s, '\0', sizeof(struct sockaddr_in));
        s.sin_family = AF_INET;
        s.sin_port = htons(DOIPParameters::Instance->DOIP_ENTITY_UDP_DISCOVER);
        s.sin_addr.s_addr = htonl(INADDR_BROADCAST);

        sendto(UDPListen::Instance->get_socket(), (const char *)&Frame[0], Frame.size(), 0, (struct sockaddr *)&s, sizeof(s));

    }

 }