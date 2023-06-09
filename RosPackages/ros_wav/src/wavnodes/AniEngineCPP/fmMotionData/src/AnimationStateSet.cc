

#include "AnimationStateSet.h"



namespace fmMotionData
{
  void AnimationStateSet::parseJson(jsonObject json)
    {
        try
        {
            jsonObject dictionary = json["AnimationStateSet"].get<jsonObject>();

            std::map<AnimationObject::etype, std::unique_ptr<AnimationState>>::iterator it = StateSet.begin();
            AnimationObject animationObject;
            while (it != StateSet.end())
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

    string AnimationStateSet::Json()
    {

        string json = "";

        json = json.append("{ \"AnimationStateSet\" : {");

        std::map<AnimationObject::etype, std::unique_ptr<AnimationState>>::iterator it = StateSet.begin();
        AnimationObject animationObject;
        while (it != StateSet.end())
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