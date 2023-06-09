#pragma once

#include<map>
#include<string>


#include "UIViewAnimationOptions.h"

using fmCommon::UIViewAnimationOptions;

using namespace std;

namespace fmMotionData
{
class UIElementAnimationOptions
{
public:
    enum eType
    {
         autoreverse = 0,
        beginFromCurrentState = 1,
        curveEaseIn = 2,
        curveEaseInOut = 3,
        curveEaseOut = 4,
        curveLinear = 5,
        showHideTransitionViews = 6,
        transitionCrossDissolve = 7,
        transitionCurlDown = 8,
        transitionCurlUp = 9,
        transitionFlipFromBottom = 10,
        transitionFlipFromLeft = 11,
        transitionFlipFromRight = 12,
        transitionFlipFromTop = 13,
        allowUserInteraction = 14
    };

    
    
    int count = 15;

     const map<string, UIViewAnimationOptions::Options> stringtoenum{
         {"autoreverse", UIViewAnimationOptions::Options::autoreverse}, 
        {"beginFromCurrentState", UIViewAnimationOptions::Options::beginFromCurrentState}, 
        {"curveEaseIn", UIViewAnimationOptions::Options::curveEaseIn}, 
        {"curveEaseInOut", UIViewAnimationOptions::Options::curveEaseInOut}, 
        {"curveEaseOut", UIViewAnimationOptions::Options::curveEaseOut}, 
        {"curveLinear", UIViewAnimationOptions::Options::curveLinear}, 
        {"showHideTransitionViews", UIViewAnimationOptions::Options::showHideTransitionViews}, 
        {"transitionCrossDissolve", UIViewAnimationOptions::Options::transitionCrossDissolve}, 
        {"transitionCurlDown", UIViewAnimationOptions::Options::transitionCurlDown}, 
        {"transitionCurlUp", UIViewAnimationOptions::Options::transitionCurlUp}, 
        {"transitionFlipFromBottom", UIViewAnimationOptions::Options::transitionFlipFromBottom}, 
        {"transitionFlipFromLeft", UIViewAnimationOptions::Options::transitionFlipFromLeft}, 
        {"transitionFlipFromRight", UIViewAnimationOptions::Options::transitionFlipFromRight}, 
        {"transitionFlipFromTop", UIViewAnimationOptions::Options::transitionFlipFromTop}, 
        {"allowUserInteraction", UIViewAnimationOptions::Options::allowUserInteraction}};



     const map<UIElementAnimationOptions::eType, string> enumtostring{
         { UIElementAnimationOptions::autoreverse, "autoreverse"}, 
        { UIElementAnimationOptions::beginFromCurrentState, "beginFromCurrentState"}, 
        { UIElementAnimationOptions::curveEaseIn, "curveEaseIn"}, 
        { UIElementAnimationOptions::curveEaseInOut, "curveEaseInOut"}, 
        { UIElementAnimationOptions::curveEaseOut, "curveEaseOut"}, 
        { UIElementAnimationOptions::curveLinear, "curveLinear"}, 
        { UIElementAnimationOptions::showHideTransitionViews, "showHideTransitionViews"}, 
        { UIElementAnimationOptions::transitionCrossDissolve, "transitionCrossDissolve"}, 
        { UIElementAnimationOptions::transitionCurlDown, "transitionCurlDown"}, 
        { UIElementAnimationOptions::transitionCurlUp, "transitionCurlUp"}, 
        { UIElementAnimationOptions::transitionFlipFromBottom, "transitionFlipFromBottom"}, 
        { UIElementAnimationOptions::transitionFlipFromLeft, "transitionFlipFromLeft"}, 
        { UIElementAnimationOptions::transitionFlipFromRight, "transitionFlipFromRight"}, 
        { UIElementAnimationOptions::transitionFlipFromTop, "transitionFlipFromTop"}, 
        { UIElementAnimationOptions::allowUserInteraction, "allowUserInteraction"}
        };

};

} // namespace  fmMotionData
