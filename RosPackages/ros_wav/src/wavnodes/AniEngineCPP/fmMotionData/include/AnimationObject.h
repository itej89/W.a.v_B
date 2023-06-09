#pragma once

#include <map>
#include <string>

using namespace std;

namespace fmMotionData
{

 

class AnimationObject
{
public:
    enum etype
    {
        Image_EyeBrowRight=20,
        Image_EyeBrowLeft=15,
        Image_EyeBallRight=17,
        Image_EyeBallLeft=12,
        Image_EyeRight=16,
        Image_EyeLeft=11,
        Image_EyePupilRight=18,
        Image_EyePupilLeft=13,
        Image_EyeLidRight=19,
        Image_EyeLidLeft=14,
        Motor_Turn=21,
        Motor_Lift=22,
        Motor_Lean=23,
        Motor_Tilt=24,
        NA=-1
    };

 const map<std::string, etype> stringtoenum{
         { "Image_EyeBrowRight", Image_EyeBrowRight}, 
         { "Image_EyeBrowLeft", Image_EyeBrowLeft}, 
         { "Image_EyeBallRight", Image_EyeBallRight}, 
         { "Image_EyeBallLeft", Image_EyeBallLeft}, 
         { "Image_EyeRight", Image_EyeRight}, 
         { "Image_EyeLeft", Image_EyeLeft}, 
         { "Image_EyePupilRight", Image_EyePupilRight}, 
         { "Image_EyePupilLeft", Image_EyePupilLeft}, 
         { "Image_EyeLidRight", Image_EyeLidRight}, 
         { "Image_EyeLidLeft", Image_EyeLidLeft}, 


         { "Motor_Turn", Motor_Turn}, 
         { "Motor_Lift", Motor_Lift}, 
         { "Motor_Lean", Motor_Lean}, 
         { "Motor_Tilt", Motor_Tilt}, 

         { "NA", NA}
 };


 const map<etype, std::string> enumtostring{
         {Image_EyeBrowRight, "Image_EyeBrowRight"}, 
         {Image_EyeBrowLeft , "Image_EyeBrowLeft"}, 
         {Image_EyeBallRight , "Image_EyeBallRight"}, 
         {Image_EyeBallLeft , "Image_EyeBallLeft"}, 
         {Image_EyeRight , "Image_EyeRight"}, 
         {Image_EyeLeft , "Image_EyeLeft"}, 
         {Image_EyePupilRight , "Image_EyePupilRight"}, 
         {Image_EyePupilLeft , "Image_EyePupilLeft"}, 
         {Image_EyeLidRight , "Image_EyeLidRight"}, 
         {Image_EyeLidLeft , "Image_EyeLidLeft"}, 

         {Motor_Turn , "Motor_Turn"}, 
         {Motor_Lift , "Motor_Lift"}, 
         {Motor_Lean , "Motor_Lean"}, 
         {Motor_Tilt , "Motor_Tilt"},


         {NA , "NA"}
 };

};

} // namespace fmMotionData