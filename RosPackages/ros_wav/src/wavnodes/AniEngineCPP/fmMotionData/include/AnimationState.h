#pragma once

#include <string>

#include "nlohmann/json.hpp"

using jsonObject = nlohmann::json;

namespace fmMotionData
{

class AnimationState
{
public:
   virtual std::string Json();

   virtual void parseJson(jsonObject json);
};

} // namespace fmMotionData