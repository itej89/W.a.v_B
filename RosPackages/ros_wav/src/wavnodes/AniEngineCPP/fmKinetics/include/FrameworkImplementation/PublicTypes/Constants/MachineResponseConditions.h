#pragma once

namespace fmKinetics
{
    class MachineResponseConditions
    {
        public:
            enum etype
            {
                OK,
                ERROR,
                REPSONSE_NOT_FOUND,
                INVALID_REQUEST_COMMAND,
                INVALID_RESPONSE
            };

            etype Value = ERROR;
    };
}
