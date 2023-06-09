#include <math.h>

#include "DB_Local_Store.h"
#include "DataTypes/Expressions_Type.h"

#include "nlohmann/json.hpp"

#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTiming.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEasing.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEasingInOut.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestInstantTrigger.h"
#include "Framework/DataTypes/MachineCommandHelper.h"
#include "FrameworkImplementation/KineticsAccess.h"

#include "AnimationObject.h"
#include "MotorAnimationState.h"
#include "AnimationPositions.h"

#include "GameEffects/EffectCreator.h"


using namespace fmDB;
using jsonObject = nlohmann::json;
using namespace fmKinetics;
using namespace fmMotionData;

namespace fmSystem
{

    EffectCreator::EffectCreator()
    {
    }

    void EffectCreator::CreateContext()
    {
         DB_Local_Store dbHAndler;
          Expressions_Type Expression = dbHAndler.readExpression("Play_Straight");
          jsonObject jObject = jsonObject::parse(Expression.Action_Data);
          AnimationPositions Position;
          Position.parseJson(jObject);

          Play_referance_Lift_Angle = MachineConfig::Instance.MachineActuatorList.at(Actuator::LIFT)->RefPosition +
                                        get<0>(static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Lift).get())->Angle);
          Play_referance_Lean_Angle = MachineConfig::Instance.MachineActuatorList.at(Actuator::LEAN)->RefPosition + 
                                        get<0>(static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Lean).get())->Angle);

          Play_referance_Tilt_Angle = MachineConfig::Instance.MachineActuatorList.at(Actuator::TILT)->RefPosition + 
                                        get<0>(static_cast<MotorAnimationState*>(Position.State.StateSet.at(AnimationObject::Motor_Tilt).get())->Angle);


          ShutDown_Lift_Angle = MachineConfig::Instance.MachineActuatorList.at(Actuator::LIFT)->RefPosition + 
                                  MachineConfig::Instance.MachineActuatorList.at(Actuator::LIFT)->ShutdownDeltaAngle;
          ShutDown_Lean_Angle = MachineConfig::Instance.MachineActuatorList.at(Actuator::LEAN)->RefPosition + 
                                  MachineConfig::Instance.MachineActuatorList.at(Actuator::LEAN)->ShutdownDeltaAngle;
                                  
          Shutdown_Tilt_Angle = MachineConfig::Instance.MachineActuatorList.at(Actuator::TILT)->RefPosition + 
                                  MachineConfig::Instance.MachineActuatorList.at(Actuator::TILT)->ShutdownDeltaAngle;


          ShutDown_Lift_Sign = signbit(MachineConfig::Instance.MachineActuatorList.at(Actuator::LIFT)->ShutdownDeltaAngle) == 1 ? -1 : 1;
          ShutDown_Lean_Sign = signbit(MachineConfig::Instance.MachineActuatorList.at(Actuator::LEAN)->ShutdownDeltaAngle) == 1 ? -1 : 1;
          ShutDown_Tilt_Sign = signbit(MachineConfig::Instance.MachineActuatorList.at(Actuator::TILT)->ShutdownDeltaAngle) == 1 ? -1 : 1;

          MachineCommandHelper machineCommandHelper;
          

          //Find allowed Zoom range for device in PWM
          int Lift_Max_Swing_Range = abs(machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lift_Angle)  - machineCommandHelper.ConvertAngleToPWMValue(ShutDown_Lift_Angle));
          int Lean_Max_Swing_RAnge = abs(machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lean_Angle) - machineCommandHelper.ConvertAngleToPWMValue(ShutDown_Lean_Angle));

          MaxUniformZoomRange = min(Lift_Max_Swing_Range, Lean_Max_Swing_RAnge);


          MaxTiltRange = 2 * abs(machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Tilt_Angle) - machineCommandHelper.ConvertAngleToPWMValue(Shutdown_Tilt_Angle));


          CurrentUniformZoomedRange = 0;
    }


    std::vector<KineticsRequest> EffectCreator::UniformZoom(int percent)
    {
         std::vector<KineticsRequest> ZoomSet;

          int Zoom = (int)(MaxUniformZoomRange*percent/100);
          
              MachineCommandHelper machineCommandHelper;

                int LiftPWM;
                int LeanPWM;
                if(percent > 0)
                {

                 LiftPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lift_Angle) + (ShutDown_Lift_Sign * MaxUniformZoomRange);
                 LeanPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lean_Angle) + (ShutDown_Lean_Sign * MaxUniformZoomRange);
                }
                else
                {
                    LiftPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lift_Angle);
                    LeanPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lean_Angle) ;
                  
                }
                
              
                ZoomSet.push_back(KineticsRequestAngle(Actuator::LIFT, LiftPWM));
                ZoomSet.push_back(KineticsRequestAngle(Actuator::LEAN, LeanPWM));

                // int Timing = (3500/MaxUniformZoomRange)*abs(Zoom - CurrentUniformZoomedRange);
                // Timing = Timing > 400? Timing : 400;
                // if(percent == 0)
                // {
                //   Timing = 3500;
                // }

                int Timing = 3500;
                ZoomSet.push_back(KineticsRequestTiming(Timing, Actuator::LEAN));
                ZoomSet.push_back(KineticsRequestTiming(Timing, Actuator::LIFT));


                ZoomSet.push_back(KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::LIFT));
                ZoomSet.push_back(KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::LEAN));


              CurrentUniformZoomedRange = Zoom;


          return ZoomSet;
    }

     std::vector<KineticsRequest> EffectCreator::UniformZoomIn()
     {  
         std::vector<KineticsRequest> ZoomSet;
          
          if(CurrentUniformZoomedRange + 5 < MaxUniformZoomRange)
          {
              CurrentUniformZoomedRange = CurrentUniformZoomedRange + 5;
              MachineCommandHelper machineCommandHelper;

                int LiftPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lift_Angle) + (ShutDown_Lift_Sign * CurrentUniformZoomedRange);
                int LeanPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lean_Angle) + (ShutDown_Lean_Sign * CurrentUniformZoomedRange);
              
                ZoomSet.push_back(KineticsRequestAngle(Actuator::LIFT, LiftPWM));
                ZoomSet.push_back(KineticsRequestAngle(Actuator::LEAN, LeanPWM));

                ZoomSet.push_back(KineticsRequestTiming(250, Actuator::LEAN));
                ZoomSet.push_back(KineticsRequestTiming(250, Actuator::LIFT));


                ZoomSet.push_back(KineticsRequestServoEasing(CommandLabels::EasingFunction::SIN, Actuator::LIFT));
                ZoomSet.push_back(KineticsRequestServoEasing(CommandLabels::EasingFunction::SIN, Actuator::LEAN));


          }

          return ZoomSet;
     }


     std::vector<KineticsRequest> EffectCreator::UniformZoomOut()
     {  
         std::vector<KineticsRequest> ZoomSet;
          
          if(CurrentUniformZoomedRange - 5 > 0)
          {
              CurrentUniformZoomedRange = CurrentUniformZoomedRange - 5;
              MachineCommandHelper machineCommandHelper;

                int LiftPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lift_Angle) + (ShutDown_Lift_Sign * CurrentUniformZoomedRange);
                int LeanPWM = machineCommandHelper.ConvertAngleToPWMValue(Play_referance_Lean_Angle) + (ShutDown_Lean_Sign * CurrentUniformZoomedRange);
              
                ZoomSet.push_back(KineticsRequestAngle(Actuator::LIFT, LiftPWM));
                ZoomSet.push_back(KineticsRequestAngle(Actuator::LEAN, LeanPWM));

                ZoomSet.push_back(KineticsRequestTiming(250, Actuator::LEAN));
                ZoomSet.push_back(KineticsRequestTiming(250, Actuator::LIFT));


                ZoomSet.push_back(KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::LIFT));
                ZoomSet.push_back(KineticsRequestServoEasing(CommandLabels::EasingFunction::LIN, Actuator::LEAN));


          }

          return ZoomSet;
     }

}