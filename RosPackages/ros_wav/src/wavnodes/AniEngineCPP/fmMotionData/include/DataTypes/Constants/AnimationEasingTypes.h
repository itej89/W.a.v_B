#pragma once

#include<iostream>
#include<map>
#include<string>

using namespace std;

namespace fmMotionData
{
class AnimationEasingTypes
{
    public:
        enum eType
        {
            linear = 0,
            easeIN = 1,
            easeOut = 2,
            easeInOut = 3
        };


        const map<string, eType> stringtoenum{{"linear", linear},
                                            {"easeIN", easeIN},
                                            {"easeOut", easeOut},
                                            {"easeInOut", easeInOut}};

                                            

        const string kCAMediaTimingFunctionLinear = "kCAMediaTimingFunctionLinear";
        const string kCAMediaTimingFunctionEaseIn = "kCAMediaTimingFunctionEaseIn";
        const string kCAMediaTimingFunctionEaseOut = "kCAMediaTimingFunctionEaseOut";
        const string kCAMediaTimingFunctionEaseInEaseOut = "kCAMediaTimingFunctionEaseInEaseOut";

        const map<eType, string> AnimationEasingTypesToCAMediaTimingFunction = {
            {linear, kCAMediaTimingFunctionLinear},
            {easeIN, kCAMediaTimingFunctionEaseIn},
            {easeOut, kCAMediaTimingFunctionEaseOut},
            {easeInOut, kCAMediaTimingFunctionEaseInEaseOut}};
};

} // namespace  fmMotionData
