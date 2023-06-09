#pragma once

#include<iostream>
#include<tuple>
#include<vector>
#include<string>
#include<memory>


#include "nlohmann/json.hpp"

#include "DataTypes/Constants/AnimationTypes.h"
#include "DataTypes/Constants/CircularPathDirection.h"
#include "AnimationObject.h"
#include "AnimationState.h"

using namespace std;

using jsonObject = nlohmann::json;



namespace fmMotionData
{
class ImageAnimationState : public AnimationState
{
public:
    AnimationTypes::eType AnimationKind = AnimationTypes::NA;

    AnimationObject::etype TargetObject = AnimationObject::NA;

    class TransformMatrix
    {
    public:
        std::tuple<double, bool> a = std::make_tuple(0.0, false);
        std::tuple<double, bool> b = std::make_tuple<>(0.0, false);
        std::tuple<double, bool> c = std::make_tuple<>(0.0, false);
        std::tuple<double, bool> d = std::make_tuple<>(0.0, false);

        std::tuple<double, bool> tx = std::make_tuple<>(0.0, false);
        std::tuple<double, bool> ty = std::make_tuple<>(0.0, false);
    };

    class CircularCurve
    {
    public:
        std::tuple<double, bool> MidX = std::make_tuple<>(0.0, false);
        std::tuple<double, bool> MidY = std::make_tuple<>(0.0, false);
        std::tuple<double, bool> Radius = std::make_tuple<>(0.0, false);
        std::tuple<double, bool> StartAngle = std::make_tuple<>(0.0, false);

        std::tuple<double, bool> EndAngle = std::make_tuple<>(0.0, false);
        std::tuple<CircularPathDirection::eType, bool> Direction = std::make_tuple<>(CircularPathDirection::clockwise, false);
    };

    TransformMatrix Matrix;
    CircularCurve CircularPath;

    std::tuple<double, bool> opacity = std::make_tuple<>(0.0, false);
    std::tuple<double, bool> centreX = std::make_tuple<>(0.0, false);
    std::tuple<double, bool> centreY = std::make_tuple<>(0.0, false);
    std::tuple<double, bool> AnchorX = std::make_tuple<>(0.0, false);
    std::tuple<double, bool> AnchorY = std::make_tuple<>(0.0, false);

    void parseJson(jsonObject json);

    std::string Json();

    ImageAnimationState();

    ImageAnimationState(AnimationObject::etype _TargetObject,
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
                        std::tuple<double, bool> _anchorY);
};
} // namespace fmMotionData