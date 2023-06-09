
#include <tuple>

#include "ImageAnimationTransition.h"

namespace fmMotionData
{

     static __inline__ double atof(const char *nptr)
    {
        return (strtod(nptr, NULL));
    }


void ImageAnimationTransition::parseJson(jsonObject json)
{
    try
    {
        jsonObject dictionary = json["Transition"].get<jsonObject>();

        Duration = std::atoi(dictionary["Duration"].get<string>().c_str());
        Delay = std::atoi(dictionary["Delay"].get<string>().c_str());
        Amplitude = atof(dictionary["Amplitude"].get<string>().c_str());
        Damping = atof(dictionary["Damping"].get<string>().c_str());

        AnimationEasingTypes animationEasingTypes;
        KeyframeAnimation_EasingFunction = animationEasingTypes.stringtoenum.at(dictionary["KeyframeAnimation_EasingFunction"].get<string>());

        AnimationFillModes animationFillModes;
        KeyframeAnimation_FillMode = animationFillModes.stringtoenum.at(dictionary["KeyframeAnimation_FillMode"].get<string>());

        UIElementAnimationOptions uiElementAnimationOptions;


        for (auto it = dictionary["AnimationCurveType"].begin(); it != dictionary["AnimationCurveType"].end(); ++it)
        {
            AnimationCurveType.push_back(uiElementAnimationOptions.stringtoenum.at(it.value()));
        }
    }
    catch (int e)
    {
    }
}

string ImageAnimationTransition::Json()
{

    string json = "";

    json = json.append("{ \"Transition\" : {");

    json = json.append(" \"Duration\" : \"" + to_string(Duration) + "\" ,");

    json = json.append(" \"Delay\" : \"" + to_string(Delay) + "\" ,");

    json = json.append(" \"Damping\" : \"" + to_string(Damping) + "\" ,");

    json = json.append(" \"Amplitude\" : \"" + to_string(Amplitude) + "\" ,");

    AnimationEasingTypes animationEasingTypes;
    json = json.append(" \"KeyframeAnimation_EasingFunction\" : \"" + animationEasingTypes.AnimationEasingTypesToCAMediaTimingFunction.at(KeyframeAnimation_EasingFunction) + "\" ,");

    AnimationFillModes animationFillModes;
    json = json.append(" \"KeyframeAnimation_FillMode\" : \"" + animationFillModes.AnimationEasingTypesToCAMediaTimingFunction.at(KeyframeAnimation_FillMode) + "\" ,");
    json = json.append(" \"AnimationCurveType\" : {");

    int i = 0;

    UIElementAnimationOptions uiElementAnimationOptions;
    while (i < uiElementAnimationOptions.count)
    {

        if (std::find(AnimationCurveType.begin(), AnimationCurveType.end(), static_cast<UIElementAnimationOptions::eType>(i)) != AnimationCurveType.end())
            ;
        {
            json = json.append(" \"key\" : \"" + uiElementAnimationOptions.enumtostring.at(static_cast<UIElementAnimationOptions::eType>(i)) + "\" ,");
        }

        i = i + 1;
    }

    //remove ending ','
    json.pop_back();

    json = json.append(" } ");

    json = json.append("}}");

    return json;
}

ImageAnimationTransition::ImageAnimationTransition()
{
}

ImageAnimationTransition::ImageAnimationTransition(TransitionType _ImageTransitionType,
                                                   int _Duration, int _Delay, vector<UIViewAnimationOptions::Options> _AnimationCurveType, double _Damping, double _Amplitude)
{
    ImageTransitionType = _ImageTransitionType;
    Duration = _Duration;
    Delay = _Delay;
    AnimationCurveType = _AnimationCurveType;
    Damping = _Damping;
    Amplitude = _Amplitude;
}
} // namespace fmMotionData