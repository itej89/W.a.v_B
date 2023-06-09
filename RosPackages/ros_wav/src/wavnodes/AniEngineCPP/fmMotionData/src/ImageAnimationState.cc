
#include<tuple>

#include "StringX.h"

#include "ImageAnimationState.h"


using namespace fmCommon;

namespace fmMotionData
{

    static __inline__ double atof(const char *nptr)
    {
        return (strtod(nptr, NULL));
    }

    void ImageAnimationState::parseJson(jsonObject json)
    {
        try
        {

            StringX Xstr;

            jsonObject dictionary = json["AnimationState"].get<jsonObject>();

            AnimationTypes animationTypes;
            AnimationKind = animationTypes.stringtoenum.at(
                dictionary["AnimationKind"]);

            jsonObject dictionaryProperty = dictionary["a"].get<jsonObject>();

            Matrix.a = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["b"].get<jsonObject>();

            Matrix.b = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["c"].get<jsonObject>();

            Matrix.c = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["d"].get<jsonObject>();

            Matrix.d = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["tx"].get<jsonObject>();

            Matrix.tx = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["ty"].get<jsonObject>();

            Matrix.ty = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty =  dictionary["MidX"].get<jsonObject>();

            CircularPath.MidX = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["MidY"].get<jsonObject>();

            CircularPath.MidY = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["Radius"].get<jsonObject>();

            CircularPath.Radius = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["StartAngle"].get<jsonObject>();

            CircularPath.StartAngle = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["EndAngle"].get<jsonObject>();

            CircularPath.EndAngle = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["Direction"].get<jsonObject>();


            CircularPathDirection circularPathDirection;
            CircularPath.Direction = std::make_tuple<>(circularPathDirection.stringtoenum.at(dictionaryProperty["key"]),  Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["opacity"].get<jsonObject>();

            opacity = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["centreX"].get<jsonObject>();

            centreX = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["centreY"].get<jsonObject>();

            centreY = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty = dictionary["AnchorX"].get<jsonObject>();

            AnchorX = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));

            dictionaryProperty =  dictionary["AnchorY"].get<jsonObject>();

            AnchorY = std::make_tuple<>(atof(dictionaryProperty["key"].get<string>().c_str()),
                                         Xstr.to_bool(dictionaryProperty["value"].get<string>()));
        }
        catch (int e)
        {
        }
    }

    std::string ImageAnimationState::Json()
    {

        std::string json = "";

        json = json.append("{ \"AnimationState\" : {");

        AnimationTypes animationTypes;
        json = json.append(" \"AnimationKind\" : \"" + animationTypes.enumtostring.at(AnimationKind) + "\" , ");

        json = json.append(" \"a\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(Matrix.a)) + "\" , " + " \"value\" : \"" + to_string(get<1>(Matrix.a)) + "\"  },");

        json = json.append(" \"b\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(Matrix.b)) + "\" , " + " \"value\" : \"" + to_string(get<1>(Matrix.b))  + "\"  },");

        json = json.append(" \"c\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(Matrix.c)) + "\" , " + " \"value\" : \"" + to_string(get<1>(Matrix.c))  + "\"  },");

        json = json.append(" \"d\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(Matrix.d)) + "\" , " + " \"value\" : \"" + to_string(get<1>(Matrix.d))  + "\"  },");

        json = json.append(" \"tx\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(Matrix.tx)) + "\" , " + " \"value\" : \"" + to_string(get<1>(Matrix.tx))  + "\"  },");

        json = json.append(" \"ty\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(Matrix.ty)) + "\" , " + " \"value\" : \"" + to_string(get<1>(Matrix.ty))  + "\"  },");

        json = json.append(" \"MidX\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(CircularPath.MidX)) + "\" , " + " \"value\" : \"" +to_string(get<1>(CircularPath.MidX))  + "\"  },");

        json = json.append(" \"MidY\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(CircularPath.MidY)) + "\" , " + " \"value\" : \"" + to_string(get<1>(CircularPath.MidY)) + "\"  },");

        json = json.append(" \"StartAngle\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(CircularPath.StartAngle)) + "\" , " + " \"value\" : \"" + to_string(get<1>(CircularPath.StartAngle)) + "\"  },");

        json = json.append(" \"EndAngle\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(CircularPath.EndAngle)) + "\" , " + " \"value\" : \"" + to_string(get<1>(CircularPath.EndAngle)) + "\"  },");

        json = json.append(" \"Radius\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(CircularPath.Radius))  + "\" , " + " \"value\" : \"" + to_string(get<1>(CircularPath.Radius)) + "\"  },");

        CircularPathDirection circularPathDirection;
        json = json.append(" \"Direction\" : {");
        json = json.append(" \"key\" : \"" + circularPathDirection.enumtostring.at(get<0>(CircularPath.Direction))  + "\" , " + " \"value\" : \"" + std::to_string(get<1>(CircularPath.Direction)) + "\"  },");

        json = json.append(" \"opacity\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(opacity)) + "\" , " + " \"value\" : \"" + to_string(get<1>(opacity)) + "\"  },");

        json = json.append(" \"centreX\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(centreX)) + "\" , " + " \"value\" : \"" +to_string(get<1>(centreX)) + "\"  },");

        json = json.append(" \"centreY\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(centreY))  + "\" , " + " \"value\" : \"" + to_string(get<1>(centreY)) + "\"  },");

        json = json.append(" \"AnchorX\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(AnchorX)) + "\" , " + " \"value\" : \"" + to_string(get<1>(AnchorX)) + "\"  },");

        json = json.append(" \"AnchorY\" : {");
        json = json.append(" \"key\" : \"" + to_string(get<0>(AnchorY)) + "\" , " + " \"value\" : \"" + to_string(get<1>(AnchorY)) + "\"  }");

        json = json.append(" }");

        json = json.append("}");

        return json;
    }

    ImageAnimationState::ImageAnimationState() {}

    ImageAnimationState::ImageAnimationState(AnimationObject::etype _TargetObject,
                        std::tuple<double, bool> _a,
                        std::tuple<double, bool> _b,
                        std::tuple<double, bool> _c,
                        std::tuple<double, bool> _d,
                        std::tuple<double, bool> _tx,
                        std::tuple<double, bool> _ty,
                        std::tuple<double, bool> _opacity,
                        std::tuple<double, bool> _centreX,
                        std::tuple<double, bool> _centreY,
                        std::tuple<double, bool> _anchorX,
                        std::tuple<double, bool> _anchorY)
    {
        TargetObject = _TargetObject;
        Matrix.a = _a;
        Matrix.b = _b;
        Matrix.c = _c;
        Matrix.d = _d;
        Matrix.tx = _tx;
        Matrix.ty = _ty;
        opacity = _opacity;
        centreX = _centreX;
        centreY = _centreY;
        AnchorX = _anchorX;
        AnchorY = _anchorY;
    }
}