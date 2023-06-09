#pragma once

#include <string>
#include <vector>
#include <memory>

#include "DataTypes/BotDetails.h"
#include "DataTypes/Enums/BotConnectionInfo.h"
#include "DataTypes/Enums/LINK_ANCHORS.h"

namespace fmBotConnect
{
    class BotConnectConvey
    {
        public:
        virtual void DiscoveredBots(std::vector<std::shared_ptr<BotDetails>> Bots);
        
        virtual void BotConnected(std::string _ID);
        virtual void BotDisconnected(std::string _ID);
        
        virtual void BotLowStorage();
        virtual void BotError(BotConnectionInfo::CODE Error);
        
        virtual void BrokerConenctionChanged(bool  Status);

        virtual void BotStartLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS);
        virtual void BotStopLinkStream(LINK_ANCHORS::CODE _LINK_ANCHORS);

        virtual void BotRequest(LINK_ANCHORS::CODE, std::string _REQUEST_DATA);
    };

}