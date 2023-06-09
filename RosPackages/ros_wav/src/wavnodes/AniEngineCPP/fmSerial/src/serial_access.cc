

#include <unistd.h>
#include <cstdio>

#include <sstream>  // std::ostringstream
#include <algorithm>    // std::copy
#include <iterator> // std::ostream_iterator
#include <iostream>
#include <thread>

// #include "core/reference.h"

#include "FrameworkInterface/PublicTypes/CommsConvey.h"
#include "FrameworkInterface/PublicTypes/Constants/CommsStates.h"
#include "FrameworkInterface/PublicTypes/Device.h"
#include "FrameworkInterface/PublicTypes/serial_access.h"
#include "serial/serial.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::vector;

using fmSerial::CommsConvey;
using fmSerial::CommsStates;
using fmSerial::Device;
using fmSerial::Serial_Access;


/* #region  Private Methods */
bool Serial_Access::ConnectToDevice(string DeviceID) {

	// std::wstring ws = DeviceID.c_str();
	// std::string s(ws.begin(), ws.end());
	if(mSerial == nullptr)
	{
		mSerial.reset(new serial::Serial(DeviceID, 115200, serial::Timeout::simpleTimeout(10)));
		if (mSerial != nullptr) {
			dataReadThread.reset(new std::thread(&Serial_Access::ReadDataLoop, this));

			return true;
		}
	}
	return false;
}

struct free_delete
{
    void operator()(void* x) { free(x); }
};

void Serial_Access::ReadDataLoop() {
	try {
            int sleep_delay = 1000;
		while (mSerial->isOpen()) {
		if(mSerial->available() > 0)
		{
			std::string strData = ReadString();
			if(!(strData == ""))
			{
				notifyCommsConvey->stringRecieved(strData);
			}
		}
		usleep(sleep_delay);
		}
	} catch (exception x) {
	}
}
/* #endregion */
//


/* #region  Public Methods */
Serial_Access::Serial_Access()
{

}

Serial_Access::Serial_Access(std::shared_ptr<serial::Serial> _serial)
{
	mSerial = _serial;
}


bool Serial_Access::InitializeComms() {
	//return	ConnectToDevice("/dev/ttyACM0");
	return	ConnectToDevice("/dev/ttyUSB0");
}

void Serial_Access::SetCommsDelegate(std::shared_ptr<CommsConvey> delegate)
{
	notifyCommsConvey = delegate;
}

bool Serial_Access::IsConnectedToPeripheral() {
	if (mSerial != nullptr) {
		if (mSerial->isOpen()) {
			return true;
		}
	}
	return false;
}

bool Serial_Access::DisconnectDevice() {
	if (mSerial != nullptr) {
		if (mSerial->isOpen()) {
			mSerial->close();

			if(dataReadThread != nullptr)
			{
				if (dataReadThread->joinable())
					dataReadThread->join();
			}

			
		}
	}
	return true;
}

std::string Serial_Access::ReadString()
{
	size_t dataLen = mSerial->available();
	uint8_t* data((uint8_t*)malloc(sizeof(uint8_t)*dataLen));

	size_t length = mSerial->readToBuffer(data, dataLen);

	
	std::ostringstream ss;
    std::copy(data, data+length, std::ostream_iterator<uint8_t>(ss, ""));

	
	free(data);

	return ss.str();
}

size_t Serial_Access::SendString(string Data) {
	if (mSerial != nullptr) {
		if (mSerial->isOpen()) {
			// std::wstring ws = Data.c_str();
			// std::string s(ws.begin(), ws.end());
			std::vector<uint8_t> myVector(Data.begin(), Data.end());
			uint8_t *p = &myVector[0];
			return mSerial->write(p, Data.length());
		}
	}
	return -1;
}
/* #endregion */























void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds); // 100 ms
#else
	usleep(milliseconds * 1000); // 100 ms
#endif
}

// String Serial_Access::enumerate()
// {

// vector<serial::PortInfo> devices_found = serial::list_ports();

// 	vector<serial::PortInfo>::iterator iter = devices_found.begin();

// 	while( iter != devices_found.end() )
// 	{
// 		serial::PortInfo device = *iter++;

// 		print_line( String(device.port.c_str())+String(device.description.c_str())+String(device.hardware_id.c_str()));
// 	}

//       return "";
// }

// void Serial_Access::run()
// {
//       serial::Serial my_serial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));

//       print_line("Is the serial port open?");
//       if(my_serial.isOpen())
//       print_line(" Yes.");
//       else
//       print_line(" No.");

//       // Get the Test string
//       int count = 0;
//       string test_string;

//       test_string = "Testing.";

//       // Test the timeout, there should be 1 second between prints
//       print_line("Timeout == 1000ms, asking for 1 more byte than written.");
//       size_t bytes_wrote = my_serial.write("~VEN:");
//       while (count < 10) {
//       size_t bytes_wrote = my_serial.write(test_string);

//       string result = my_serial.read(test_string.length()+1);

//       print_line("Iteration: "+itos(count)+", Bytes written: "+itos(bytes_wrote)+", Bytes read: "+itos(result.length())+", String read: "+result.c_str());

//       count += 1;
//       }

//       Test the timeout at 250ms
//       my_serial.setTimeout(serial::Timeout::max(), 250, 0, 250, 0);
//       count = 0;
//       print_line("Timeout == 250ms, asking for 1 more byte than written.");
//       while (count < 10) {
//       size_t bytes_wrote = my_serial.write(test_string);

//       string result = my_serial.read(test_string.length()+1);

//       print_line("Iteration: "+itos(count)+", Bytes written: "+itos(bytes_wrote)+", Bytes read: "+itos(result.length())+", String read: "+result.c_str());

//       count += 1;
//       }

//       Test the timeout at 250ms, but asking exactly for what was written
//       count = 0;
//       print_line("Timeout == 250ms, asking for exactly what was written.");
//       while (count < 10) {
//       size_t bytes_wrote = my_serial.write(test_string);

//       string result = my_serial.read(test_string.length());

//       print_line("Iteration: "+itos(count)+", Bytes written: "+itos(bytes_wrote)+", Bytes read: "+itos(result.length())+", String read: "+result.c_str());

//       count += 1;
//       }

//       Test the timeout at 250ms, but asking for 1 less than what was written
//       count = 0;
//       cout << "Timeout == 250ms, asking for 1 less than was written." << endl;
//       while (count < 10) {
//       size_t bytes_wrote = my_serial.write(test_string);

//       string result = my_serial.read(test_string.length()-1);

//       print_line("Iteration: "+itos(count)+", Bytes written: "+itos(bytes_wrote)+", Bytes read: "+itos(result.length())+", String read: "+result.c_str());

//       count += 1;
//       }

// }
