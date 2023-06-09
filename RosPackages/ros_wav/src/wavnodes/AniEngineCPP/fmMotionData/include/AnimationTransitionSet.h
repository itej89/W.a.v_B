#pragma once

#include <string>
#include <map>

#include "nlohmann/json.hpp"

#include "AnimationObject.h"
#include "AnimationTransition.h"
#include "ImageAnimationTransition.h"
#include "MotionAnimationTransition.h"

using jsonObject = nlohmann::json;

using namespace std;

namespace fmMotionData
{

class AnimationTransitionSet
{
    public:
        map<AnimationObject::etype, std::unique_ptr<AnimationTransition>> TransitionSet;

            AnimationTransitionSet()
            {
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeBrowRight, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeBrowLeft, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeRight, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeLeft, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeBallRight, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeBallLeft, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyePupilRight, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyePupilLeft, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeLidLeft, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Image_EyeLidRight, std::unique_ptr<AnimationTransition>(new ImageAnimationTransition())));


                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Motor_Tilt, std::unique_ptr<AnimationTransition>(new MotionAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Motor_Turn, std::unique_ptr<AnimationTransition>(new MotionAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Motor_Lift, std::unique_ptr<AnimationTransition>(new MotionAnimationTransition())));
                TransitionSet.insert(std::make_pair<AnimationObject::etype, std::unique_ptr<AnimationTransition>>(AnimationObject::Motor_Lean, std::unique_ptr<AnimationTransition>(new MotionAnimationTransition())));

            }

            void parseJson(jsonObject json);

            string Json();
};

} // namespace fmMotionData