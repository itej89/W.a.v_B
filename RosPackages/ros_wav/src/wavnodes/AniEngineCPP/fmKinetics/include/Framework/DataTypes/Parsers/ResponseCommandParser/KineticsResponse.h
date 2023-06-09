#pragma once 

#include <algorithm>
#include <string>
#include <vector>
#include <memory>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "Framework/DataTypes/Constants/KineticsResponseAcknowledgement.h"
#include "StringX.h"



using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{
     class KineticsResponse
{
    public:
     CommandLabels::CommandTypes::etype ResponseType;
     KineticsResponseAcknowledgement::etype RequestRecievedAck;
     vector<vector<string>> DecomposedResponse;

 

     KineticsResponse();

     KineticsResponse(string response);


    string removeDelimiters(string command);
    
    private:
     vector<string> decomposeCommand(string command);
    
   
    public:
      std::unique_ptr<KineticsResponse> GetResponseObject(string response);
    

    
     virtual ~KineticsResponse(){}
};

}