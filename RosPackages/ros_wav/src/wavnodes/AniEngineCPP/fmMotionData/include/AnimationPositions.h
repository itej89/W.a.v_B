#pragma once

#include <string>
#include <map>

#include "nlohmann/json.hpp"

#include "AnimationObject.h"
#include "AnimationStateSet.h"
#include "AnimationTransitionSet.h"

using jsonObject = nlohmann::json;

using namespace std;

namespace fmMotionData
{



class AnimationPositions
{
public:
    AnimationStateSet State;
    AnimationTransitionSet Transition;
    string sentance = "";
    string audio = "";
    int StartSec = 0;
    int EndSec = 0;
    double volume = 0.2;

    void parseJson(jsonObject json);
    string Json();
};

} // namespace fmMotionData