
#pragma once

#include "gmock/gmock.h"

#include "serial/serial.h"

using  serial::Serial;

class mock_serial: public Serial
{
    public:

    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(size_t, available, (), (override));
    MOCK_METHOD(size_t, readToBuffer, (uint8_t *buffer, size_t size), (override));
    MOCK_METHOD(size_t, write, (const uint8_t *data, size_t size), (override));


}; 