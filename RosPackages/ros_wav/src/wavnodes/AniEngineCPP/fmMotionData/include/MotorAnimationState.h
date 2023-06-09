#pragma once

#include<iostream> 
#include<tuple>
#include<vector>
#include<string>
#include<memory>



#include "nlohmann/json.hpp"

#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "AnimationState.h"



using jsonObject = nlohmann::json;

#include "AnimationObject.h"

using namespace fmKinetics;

namespace fmMotionData
{

    class MotorAnimationState : public AnimationState 
    {
        public:

            AnimationObject::etype TargetObject = AnimationObject::NA;

            bool IsDeltaAngle = false;

            std::tuple<int, bool> Angle = std::make_tuple(0, false);


            bool setKineticsState(std::unique_ptr<KineticsRequestAngle> request);


            std::vector<KineticsRequest> GetStateCommandString(Actuator::etype actuator);


            void parseJson(jsonObject json);

             std::string Json();


            MotorAnimationState();


            MotorAnimationState(AnimationObject _TargetObject,
                                std::tuple<int, bool> _Angle);
    };

} // namespace fmMotionData