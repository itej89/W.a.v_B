#pragma once

#include <string>

#include "nlohmann/json.hpp"

using jsonObject = nlohmann::json;

namespace fmMotionData
{

class AnimationTransition
{
public:
      virtual std::string Json();

   virtual void parseJson(jsonObject json);
};

} // namespace fmMotionData