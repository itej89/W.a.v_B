#pragma once

#include <string>
#include <map>

#include "nlohmann/json.hpp"

#include "AnimationObject.h"
#include "AnimationState.h"
#include "ImageAnimationState.h"
#include "MotorAnimationState.h"

using jsonObject = nlohmann::json;

using namespace std;

namespace fmMotionData
{

class AnimationStateSet
{
public:
    map<AnimationObject::etype, std::unique_ptr<AnimationState>> StateSet;

    AnimationStateSet()
    {
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeBrowRight, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeBrowLeft, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeRight, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeLeft, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeBallRight, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeBallLeft, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyePupilRight, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyePupilLeft, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeLidLeft, std::unique_ptr<AnimationState>(new ImageAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Image_EyeLidRight, std::unique_ptr<AnimationState>(new ImageAnimationState())));

        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Motor_Tilt, std::unique_ptr<AnimationState>(new MotorAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Motor_Turn, std::unique_ptr<AnimationState>(new MotorAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Motor_Lift, std::unique_ptr<AnimationState>(new MotorAnimationState())));
        StateSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationState>>(AnimationObject::Motor_Lean, std::unique_ptr<AnimationState>(new MotorAnimationState())));
    }

    void parseJson(jsonObject json);

    string Json();
};

} // namespace fmMotionData