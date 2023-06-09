#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <memory>

#include "UIViewAnimationOptions.h"
#include "DataTypes/Constants/AnimationEasingTypes.h"
#include "DataTypes/Constants/AnimationFillModes.h"
#include "DataTypes/Constants/UIElementAnimationOptions.h"

#include "nlohmann/json.hpp"

#include "AnimationTransition.h"

#include "AnimationObject.h"

using fmCommon::UIViewAnimationOptions;
using namespace std;

using jsonObject = nlohmann::json;

namespace fmMotionData
{
class ImageAnimationTransition: public AnimationTransition
{
public:
    enum TransitionType
    {
        NA,
        Transition,
        Identity
    };
    TransitionType ImageTransitionType = TransitionType::Transition;

    int Duration = 1000;
    int Delay = 0;
    vector<UIViewAnimationOptions::Options> AnimationCurveType{UIViewAnimationOptions::allowUserInteraction};

    double Amplitude = 0.0;
    double Damping = 0.0;

    AnimationEasingTypes::eType KeyframeAnimation_EasingFunction = AnimationEasingTypes::linear;
    AnimationFillModes::eType KeyframeAnimation_FillMode = AnimationFillModes::Removed;

    void parseJson(jsonObject json);

    string Json();

    ImageAnimationTransition();

    ImageAnimationTransition(TransitionType _ImageTransitionType,
                             int _Duration, int _Delay, vector<UIViewAnimationOptions::Options> _AnimationCurveType, double _Damping, double _Amplitude);
};

} // namespace fmMotionData