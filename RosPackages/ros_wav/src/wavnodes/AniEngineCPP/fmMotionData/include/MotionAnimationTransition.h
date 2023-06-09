#pragma once

#include<iostream> 
#include<tuple>
#include<vector>
#include<string>
#include<memory>



#include "nlohmann/json.hpp"

#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTiming.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDelay.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestFrequency.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestVelocity.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestDamp.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEasing.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEasingInOut.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"

#include "AnimationTransition.h"
#include "AnimationObject.h"


using jsonObject = nlohmann::json;

using namespace fmKinetics;

namespace fmMotionData
{

    class MotionAnimationTransition: public AnimationTransition {
        public:

        int Timing = 0;
        int Delay = 0;
        int Frequency = 0;
        int Damp = 0;
        int Velocity = 0;
        CommandLabels::EasingFunction::etype EasingFunction = CommandLabels::EasingFunction::LIN;
        CommandLabels::EasingType::etype EasingType = CommandLabels::EasingType::IN;

        bool setKineticsTransition(std::unique_ptr<KineticsRequest> request);

         std::vector<KineticsRequest> GetTransitionCommandString(Actuator::etype actuator);

        void parseJson(jsonObject json);

        std::string Json();

        MotionAnimationTransition();

        MotionAnimationTransition(
            int _Timing,
            int _Delay,
            int _Frequency,
            int _Damp,
            CommandLabels::EasingFunction::etype _EasingFunction,
            CommandLabels::EasingType::etype _EasingType);
    };
}