#pragma once 

#include <string>

#include "FrameworkImplementation/PublicTypes/Constants/MachineRequests.h"

using std::string;


namespace fmKinetics
{

 class RemoteCommandToMachineRequest {

     public:
     MachineRequests::etype Convert(string data);

};

}