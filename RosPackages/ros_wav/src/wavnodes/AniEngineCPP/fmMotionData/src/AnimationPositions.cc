

#include "AnimationPositions.h"



namespace fmMotionData
{

 
    static __inline__ double atof(const char *nptr)
    {
        return (strtod(nptr, NULL));
    }

      void AnimationPositions::parseJson(jsonObject json)
    {
        try
        {

            jsonObject dictionary = json["AnimationPositions"].get<jsonObject>();

            jsonObject dictionaryProperty = dictionary["State"].get<jsonObject>();

             State.parseJson(dictionaryProperty);

            dictionaryProperty = dictionary["Transition"].get<jsonObject>();

            Transition.parseJson(dictionaryProperty);

            audio = dictionary["audio"].get<string>();
            volume = atof(dictionary["volume"].get<string>().c_str());
        }
        catch (int e)
        {
        }
    }

    string AnimationPositions::Json()
    {

        string json = "";

        json = json.append("{ \"AnimationPositions\" : {");

        json = json.append(" \"State\" : " + State.Json() + " , ");
        json = json.append(" \"Transition\" : " + Transition.Json() + " , ");

        json = json.append(" \"audio\" : \"" + audio + "\" , ");
        json = json.append(" \"volume\" : \"" + to_string(volume) + "\"  ");

        json = json.append("}}");

        return json;
    }
}