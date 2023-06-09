#include <iostream>

#include "FrameworkInterface/PublicTypes/serial_access.h"

using namespace std;

using namespace fmSerial;

int main()
{
    Serial_Access serialPort;
    if(serialPort.InitializeComms())
    {
        cout << "port opened" << endl;
        if(serialPort.DisconnectDevice())
        {
             cout << "port closed" << endl;

             return 0;
        }
    }
        
        cout << "port error" << endl;

}