#pragma once

#include <string>

#include "../Constants/MachineCommsStates.h"
#include "../../../Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "../Machine.h"

using std::string;

namespace fmKinetics
{
    class  KineticsParameterUpdatesConvey
    {
        public:
            virtual void ParameterUpdated(KineticsRequest request) = 0;

            virtual void ParametersSetSuccessfully() = 0;
    };
}