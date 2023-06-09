#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "KineticsRequest.h"

using std::string;
using std::vector;
using std::remove;


namespace fmKinetics
{

 class KineticsRequestCELLThree : public KineticsRequest
{
   public:
     KineticsRequestCELLThree();
    
     KineticsRequestCELLThree(string command);
};

}