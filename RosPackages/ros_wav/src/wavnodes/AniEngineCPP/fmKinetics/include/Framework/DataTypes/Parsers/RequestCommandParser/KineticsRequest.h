#pragma once 

#include <algorithm>
#include <string>
#include <vector>


#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "StringX.h"

using std::string;
using std::vector;
using std::remove;

using fmCommon::StringX;

namespace fmKinetics
{
    class KineticsRequest {
    public:
        CommandLabels::CommandTypes::etype RequestType;
        
        string Request;
            
        KineticsRequest(CommandLabels::CommandTypes::etype requestType);
        
        string addDelimiters(string command);
        
        string formCommand(vector<string> items);
        
        string removeDelimiters(string command);

        vector<string> decomposeCommand(string command);
};
}