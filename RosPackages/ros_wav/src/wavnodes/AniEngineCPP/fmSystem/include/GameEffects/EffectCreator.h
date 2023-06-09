#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"


using namespace fmKinetics;


namespace fmSystem
{
    class EffectCreator
    {
    private:
        float CurrentUniformZoomedRange;
        
    public:
        int Play_referance_Lift_Angle; //Lift Angle when Game is loaded in PWM
        int Play_referance_Lean_Angle; //Lean Angle when Game is loaded in PWM
        int ShutDown_Lift_Angle;       //Lift Nap Angle in PWM
        int ShutDown_Lean_Angle;       //Lean Nap Angle in PWM
        float MaxUniformZoomRange;

        int Play_referance_Tilt_Angle; //Tilt Angle when Game is loaded in PWM
        int Shutdown_Tilt_Angle;       //Tilt Nap Angle in PWM
        float MaxTiltRange; //Max Left/Right Tilt Range in PWM

        //Negative or positive sign for PWM from Play referance to Shutdown referance
        int ShutDown_Lift_Sign; 
        int ShutDown_Lean_Sign;
        int ShutDown_Tilt_Sign;

        EffectCreator();
        void CreateContext();
        std::vector<KineticsRequest> UniformZoom(int percent);
        std::vector<KineticsRequest> UniformZoomOut();
        std::vector<KineticsRequest> UniformZoomIn();
    };
} // namespace fmSystem
