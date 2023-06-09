#pragma once

namespace fmKinetics
{
    class MachineRequests
    {
        public:
            enum etype
            {
                POWER_BUTTON_PRESSED,
                POWER_BUTTON_DOUBLE_PRESSED,
                POWER_BUTTON_LONG_PRESS,

                ATTENTION_BUTTON_PRESSED,
                ATTENTION_BUTTON_DOUBLE_PRESSED,
                ATTENTION_BUTTON_LONG_PRESS,

                LOW_BATTERY_SAFE_SHUT_DOWN,
                UNKNOWN
            };

            etype Value = UNKNOWN;
    };
}
