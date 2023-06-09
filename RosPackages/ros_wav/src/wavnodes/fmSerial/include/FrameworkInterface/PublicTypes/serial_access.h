#pragma once

#include <string>
#include <thread>
#include <memory>

// #include "core/reference.h"

#include "../../serial/serial.h"
#include "Device.h"
#include "CommsConvey.h"

using std::string;

namespace fmSerial
{
    class Serial_Access
    {

    private:
        std::shared_ptr<serial::Serial> mSerial{nullptr};
        std::unique_ptr<std::thread> dataReadThread{nullptr};
        std::shared_ptr<CommsConvey> notifyCommsConvey{nullptr};

        bool ConnectToDevice(string DeviceID);
        void ReadDataLoop();

    public:
        Serial_Access();
        Serial_Access(std::shared_ptr<serial::Serial> _serial);
        bool InitializeComms();
        bool IsConnectedToPeripheral();
        void SetCommsDelegate(std::shared_ptr<CommsConvey> delegate);
        bool DisconnectDevice();
        string ReadString();
        size_t SendString(string Data);
    };
};