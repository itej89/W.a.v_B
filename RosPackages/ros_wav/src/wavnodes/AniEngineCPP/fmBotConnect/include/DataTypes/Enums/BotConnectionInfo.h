#pragma once

namespace fmBotConnect
{
    class BotConnectionInfo
    {
        public:
        enum CODE
        {
            CONNECTION_TIMEOUT,
            CONNECTED,
            DISCONNECTED,
            ERROR,
            CATEGORY_ACK,
            REQUP_ACK,
            SENDDATA_ACK,
            EXREQ_ACK,
            COMMAND_ACK,
            LINK_ACK,
            STREAM_ACK
        };

        BotConnectionInfo();
    };
}