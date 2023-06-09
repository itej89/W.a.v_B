#pragma once

#include<map>
#include<string>


using namespace std;

namespace fmMotionData
{
class CircularPathDirection
{
public:
    enum eType
    {
        clockwise = 0,
        anitiClockwise = 1
    };

     const map<string, eType> stringtoenum{{"clockwise", clockwise}, 
                                            {"anitiClockwise", anitiClockwise}};

     const map<eType, string> enumtostring{{clockwise, "clockwise"}, 
                                            {anitiClockwise, "anitiClockwise"}};

};

} // namespace  fmMotionData
