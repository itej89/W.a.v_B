
#include "AnimationTransition.h"
#include "AnimationTransitionSet.h"



namespace fmMotionData
{

void AnimationTransitionSet::parseJson(jsonObject json)
{
    try
    {
        jsonObject dictionary = json["AnimationTransitionSet"].get<jsonObject>();

        std::map<AnimationObject::etype, std::unique_ptr<AnimationTransition>>::iterator it = TransitionSet.begin();
        AnimationObject animationObject;
        while (it != TransitionSet.end())
        {
            jsonObject dictionaryProperty = dictionary[animationObject.enumtostring.at(it->first)].get<jsonObject>();
            it->second->parseJson(dictionaryProperty);
            it++;
        }
    }
    catch (int e)
    {
    }
}

string AnimationTransitionSet::Json()
{
    string json = "";

    json = json.append("{ \"AnimationTransitionSet\" : {");

    std::map<AnimationObject::etype, std::unique_ptr<AnimationTransition>>::iterator it = TransitionSet.begin();
    AnimationObject animationObject;
    while (it != TransitionSet.end())
    {
        json = json.append(" \"" + animationObject.enumtostring.at(it->first) + "\" : " + it->second->Json() + " ,");
        it++;
    }

    json.pop_back();

    json = json.append("}");
    json = json.append("}");

    return json;
}

}