#pragma once

#include<map>
#include<string>


using namespace std;



namespace fmMotionData
{
class AnimationTypes
{
public:
    enum eType
    {
        Tranformation = 0,
        CircularPath = 1,
        Identity = 2,
        TransformOverlay = 3,
        NA = 4
    };

     const map<string, eType> stringtoenum{{"Tranformation", Tranformation}, 
                                            {"CircularPath", CircularPath}, {"Identity", Identity}, 
                                            {"TransformOverlay", TransformOverlay}, {"NA", NA}};

    const map<eType, string> enumtostring{{Tranformation, "Tranformation"}, 
                                            {CircularPath, "CircularPath"}, {Identity, "Identity"}, 
                                            {TransformOverlay, "TransformOverlay"}, {NA, "NA"}};

};

} // namespace  fmMotionData
