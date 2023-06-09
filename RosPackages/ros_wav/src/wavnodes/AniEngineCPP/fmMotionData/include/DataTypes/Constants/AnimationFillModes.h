#pragma once
#include <map>
#include <string>

namespace fmMotionData
{
class AnimationFillModes
{
public:
    enum eType
    {
        Removed = 0,
        Forward = 1,
        Backward = 2,
        ForwardAndBackWard = 3
    };

     const std::map<std::string, eType> stringtoenum{{"Removed", Removed}, 
                                            {"Forward", Forward}, {"Backward", Backward}, 
                                            {"ForwardAndBackWard", ForwardAndBackWard}};

    
    const std::string kCAFillModeBackwards = "kCAFillModeBackwards";
    const std::string kCAFillModeForwards = "kCAFillModeForwards";
    const std::string kCAFillModeBoth = "kCAFillModeBoth";
    const std::string kCAFillModeRemoved = "kCAFillModeRemoved";

    const std::map<eType, std::string> AnimationEasingTypesToCAMediaTimingFunction = {
        {Backward, kCAFillModeBackwards},
        {Forward, kCAFillModeForwards},
        {ForwardAndBackWard, kCAFillModeBoth},
        {Removed, kCAFillModeRemoved}};


};

} // namespace  fmMotionData
