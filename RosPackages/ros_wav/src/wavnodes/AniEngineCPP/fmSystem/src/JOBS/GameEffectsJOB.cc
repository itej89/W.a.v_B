
  //#include <android/log.h>

#include <ctime>

#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTiming.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestServoEasing.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestEasingInOut.h"
#include "Framework/DataTypes/MachineCommandHelper.h"
#include "FrameworkImplementation/KineticsAccess.h"


#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestInstantTrigger.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestTrigger.h"

#include "GameEffects/EffectCreator.h"
#include "JOBS/GameEffectsJOB.h"



 // #define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "FM_KINETICS", __VA_ARGS__);


using namespace fmKinetics;

namespace fmSystem
{
std::shared_ptr<GameEffectsJOB> GameEffectsJOB::getPtr()
{
    return shared_from_this();
}

void GameEffectsJOB::TriggerTimeout()
{
     IsTriggerTimedOut = true;
       IsAckRecieved = true;
}

clock_t TrigTime = clock();
int EffectDelta = 150;
int EffectTiming = 150;
//KineticsResponseConvey
void GameEffectsJOB::CommsLost() {}
void GameEffectsJOB::MachiResponseTimeout(vector<std::unique_ptr<KineticsResponse>> partialResponse, UUID _Acknowledgement) {}
void GameEffectsJOB::MachineResponseRecieved(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement) {
     if (_Acknowledgement.stringValue.compare(WaitingForKineticsRequestAck.stringValue) == 0)
    {
        WaitingForKineticsRequestAck = UUID();

        IsAckRecieved = true;
     if((float(clock() - TrigTime)/CLOCKS_PER_SEC)*1000 > 50)
     {
        EffectDelta = 60;
        EffectTiming = 200;
        DOSTEP();
        TrigTime = clock();
     }
       // 
    }
}
//End of KineticsResponseConvey

//Scheduler Calls
void GameEffectsJOB::TakeOverResources()
{
    KineticsAccess::getInstance()->SetKineticsResposeListener(getPtr());
}
void GameEffectsJOB::Resume(){
    IsTriggerTimedOut = true;
    IsAckRecieved = true;
    effectCreator.CreateContext();
    MachineCommandHelper machineCommandHelper;
    LiftPWM = machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Lift_Angle);
    LeanPWM = machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Lean_Angle);

    printf("Play ref tilt angle : %d", machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle));
    printf("Shutdown tilt angle : %d", machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Shutdown_Tilt_Angle));

    //Start at left end, caz bot tilts left on shutdown
    TiltPWM = machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle) - abs(machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle) - machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Shutdown_Tilt_Angle));

    LastLiftPWM = LiftPWM;
    LastLeanPWM  = LeanPWM;
    LastTiltPWM  = TiltPWM;
    MaxZoomlevel  = - 4 * effectCreator.MaxUniformZoomRange;
    Zoomlevel = MaxZoomlevel;

    MaxTiltlevel = -4 * effectCreator.MaxTiltRange;

}
void GameEffectsJOB::Pause()
{
    KineticsAccess::getInstance()->SetKineticsResposeListener(nullptr);
    KineticsAccess::getInstance()->ResetCommsContext();
}
//End Of Scheduler calls


void GameEffectsJOB::UniformZoom(int ZoomPercent, int TiltPercent)
{
    std::unique_lock<std::mutex> lock_(m_effectLock);
  
    MachineCommandHelper machineCommandHelper;

    InputZoomLevel = MaxZoomlevel + ((float)( 5 * effectCreator.MaxUniformZoomRange) * ((float)ZoomPercent / 100.0));
    InputTiltLevel = MaxTiltlevel + ((float)( 8 * effectCreator.MaxTiltRange) * ((float)TiltPercent / 100.0));
    
    // printf("TiltPercent : %d\n", TiltPercent);
    
    // printf("MaxTiltRange : %f\n", effectCreator.MaxTiltRange);
    
    // printf("MaxTiltlevel : %d\n", MaxTiltlevel);

    // printf("InputTiltLevel : %d\n", InputTiltLevel);

    // if(CURENT_STATE == NA)
    if((float(clock() - TrigTime)/CLOCKS_PER_SEC)*1000 > 50 && IsAckRecieved)
     {

        EffectDelta = 150;
        EffectTiming = 150;
        if(Zoomlevel > InputZoomLevel)
        {
            CURENT_STATE = ZOOM;
            DOSTEP();
        }
        else
        if(Zoomlevel < InputZoomLevel)
        {
            CURENT_STATE = ZOOM;
            DOSTEP();
        }
        else
            if(Tiltlevel < InputTiltLevel)
            {
                CURENT_STATE = ZOOM;
                DOSTEP();
            }
            else
            if(Tiltlevel > InputTiltLevel)
            {
                CURENT_STATE = ZOOM;
                DOSTEP();
            }

            TrigTime = clock();
     }
     else
     {
         
         printf("NAK\n");
     }
    
}

float ZommEffectTimingCopy = 0;
float TiltEffectTimingCopy = 0;

CommandLabels::EasingFunction::etype ZoomEase = CommandLabels::EasingFunction::SIN;
CommandLabels::EasingFunction::etype TiltEase = CommandLabels::EasingFunction::SIN;
void GameEffectsJOB::DOSTEP()
{
    MachineCommandHelper machineCommandHelper;

    bool IsLiftInRange = false;
    bool IsLeanInRange = false;
    bool IsTiltInRange = false;
    std::vector<KineticsRequest> ZoomSet;

    switch (CURENT_STATE)
    {
        case ZOOM:
        {
            int tLiftPWM =0;
            int tLeanPWM = 0;
            int tTiltPWM = 0;
            
            float EffectDeltaCopy = EffectDelta;
            float InputZoomLevelCopy = InputZoomLevel;
            if(Zoomlevel < InputZoomLevelCopy)
            {
                 if(Zoomlevel < MaxZoomlevel)
                {
                    Zoomlevel = MaxZoomlevel;
                }
                else
                {
                    Zoomlevel = Zoomlevel+EffectDeltaCopy;
                    if(Zoomlevel > InputZoomLevelCopy)
                    {
                        Zoomlevel = InputZoomLevelCopy;
                    }
                }
            }
            else
            if(Zoomlevel > InputZoomLevelCopy)
            {
                 if(Zoomlevel > (effectCreator.MaxUniformZoomRange))
                {
                    Zoomlevel = (effectCreator.MaxUniformZoomRange);
                }
                else
                {
                    Zoomlevel = Zoomlevel-EffectDeltaCopy;
                    if(Zoomlevel < InputZoomLevelCopy)
                    {
                        Zoomlevel = InputZoomLevelCopy;
                    }
                }
            }

            float InputTiltLevelCopy = InputTiltLevel;
            if(Tiltlevel < InputTiltLevelCopy)
            {
                if(Tiltlevel < MaxTiltlevel)
                {
                    Tiltlevel = MaxTiltlevel;
                }
                else
                {
                    Tiltlevel = Tiltlevel+EffectDeltaCopy;
                    if(Tiltlevel > InputTiltLevelCopy)
                    {
                        Tiltlevel = InputTiltLevelCopy;
                    }
                }
            }
            else
            if(Tiltlevel > InputTiltLevelCopy)
            {
                 if(Tiltlevel > (effectCreator.MaxTiltRange))
                {
                    Tiltlevel = (effectCreator.MaxTiltRange);
                }
                else
                {
                    Tiltlevel = Tiltlevel-EffectDeltaCopy;
                     if(Tiltlevel < InputTiltLevelCopy)
                    {
                        Tiltlevel = InputTiltLevelCopy;
                    }
                }
            }

            // printf("Tiltlevel : %d\n", Tiltlevel);

            // printf("InputTiltLevel : %d\n", InputTiltLevelCopy);

            
            tLiftPWM = (LiftPWM + (effectCreator.ShutDown_Lift_Sign *  (effectCreator.MaxUniformZoomRange-10) * 1*pow(2, (Zoomlevel-effectCreator.MaxUniformZoomRange)/effectCreator.MaxUniformZoomRange)));
            tLeanPWM = (LeanPWM + (effectCreator.ShutDown_Lean_Sign *  (effectCreator.MaxUniformZoomRange-10) * 1*pow(2, (Zoomlevel-effectCreator.MaxUniformZoomRange)/effectCreator.MaxUniformZoomRange)));
            
            tTiltPWM = (TiltPWM + (effectCreator.ShutDown_Tilt_Sign *  (effectCreator.MaxTiltRange) * 1*pow(2, (Tiltlevel-effectCreator.MaxTiltRange)/effectCreator.MaxTiltRange)));
            
            // printf(": %d\n", tTiltPWM);

            // printf("; %d\n", TiltPWM);

            // if(effectCreator.ShutDown_Lift_Sign  < 0)
            // {
                // if( tTiltPWM < machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle) - machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Shutdown_Tilt_Angle)
                //  && tTiltPWM > machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle) + machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Shutdown_Tilt_Angle))
                // {
                //     IsLiftInRange = true;
                // }
            
            // else if(effectCreator.ShutDown_Lift_Sign  > 0)
            // {
                if( tTiltPWM > machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle) - abs(machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Tilt_Angle) - machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Shutdown_Tilt_Angle))
                 && tTiltPWM < machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Shutdown_Tilt_Angle))
                {
                    IsTiltInRange = true;
                    // printf("Tilt In Range\n");

                }
            // }


            // if(effectCreator.ShutDown_Lift_Sign  < 0)
            // {
                if(tLiftPWM < machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Lift_Angle) && tLiftPWM > machineCommandHelper.ConvertAngleToPWMValue(effectCreator.ShutDown_Lift_Angle))
                {
                    IsLiftInRange = true;
                    // printf("Lift In Range\n");
                }
            
            // else if(effectCreator.ShutDown_Lift_Sign  > 0)
            // {
            //     if(tLiftPWM > machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Lift_Angle)) IsLiftInRange = true;
            // }

            // if(effectCreator.ShutDown_Lean_Sign  < 0)
            // {
            //     if(tLeanPWM < machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Lean_Angle)) IsLeanInRange = true;
            // }
            // else if(effectCreator.ShutDown_Lean_Sign  > 0)
            // {
                if(tLeanPWM > machineCommandHelper.ConvertAngleToPWMValue(effectCreator.Play_referance_Lean_Angle) && tLeanPWM < machineCommandHelper.ConvertAngleToPWMValue(effectCreator.ShutDown_Lean_Angle))
                {
                     IsLeanInRange = true;
                    // printf("Lean In Range\n");
                }
            // }

            if(IsLeanInRange && IsLiftInRange && (LastLiftPWM != tLiftPWM && LastLeanPWM != tLeanPWM) || (IsTiltInRange && (LastTiltPWM != tTiltPWM)))
            {
                
                if(IsLeanInRange && IsLiftInRange && (LastLiftPWM != tLiftPWM && LastLeanPWM != tLeanPWM))
                {
                    LastLiftPWM = tLiftPWM;
                    LastLeanPWM = tLeanPWM;
                    ZoomSet.push_back(KineticsRequestAngle(Actuator::LIFT, tLiftPWM));
                    ZoomSet.push_back(KineticsRequestAngle(Actuator::LEAN, tLeanPWM));

                    if(ZommEffectTimingCopy != EffectTiming)
                    {
                        ZommEffectTimingCopy = EffectTiming;
                        ZoomSet.push_back(KineticsRequestTiming(ZommEffectTimingCopy, Actuator::LEAN));
                        ZoomSet.push_back(KineticsRequestTiming(ZommEffectTimingCopy, Actuator::LIFT));
                    }

                    if(ZoomEase != CommandLabels::EasingFunction::LIN)
                    {
                        ZoomEase = CommandLabels::EasingFunction::LIN;
                        ZoomSet.push_back(KineticsRequestServoEasing(ZoomEase, Actuator::LIFT));
                        ZoomSet.push_back(KineticsRequestServoEasing(ZoomEase, Actuator::LEAN));
                    }
                }
                if(IsTiltInRange && (LastTiltPWM != tTiltPWM))
                { 
                    LastTiltPWM = tTiltPWM;
                    ZoomSet.push_back(KineticsRequestAngle(Actuator::TILT, tTiltPWM));

                     if(TiltEffectTimingCopy != EffectTiming)
                    {   
                        TiltEffectTimingCopy = EffectTiming;
                        ZoomSet.push_back(KineticsRequestTiming(TiltEffectTimingCopy, Actuator::TILT));
                    }

                     if(TiltEase != CommandLabels::EasingFunction::LIN)
                     {
                        TiltEase = CommandLabels::EasingFunction::LIN;
                        ZoomSet.push_back(KineticsRequestServoEasing(TiltEase, Actuator::TILT));
                     }
                }

                ZoomSet.push_back(KineticsRequestInstantTrigger());
            }
            else
            {
                CURENT_STATE  = NA;
            }
            
            if(ZoomSet.size() > 0)
            {
                IsAckRecieved = false;
                WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetGameEffectParameters(ZoomSet);
            }
            break;
        }
       
        default:
            break;
    }
}



void GameEffectsJOB::UniformZoomIN(){

     if(IsTriggerTimedOut && IsAckRecieved){
            std::vector<KineticsRequest> req = effectCreator.UniformZoomIn();
            req.push_back(KineticsRequestInstantTrigger());
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(req);
           
            IsTriggerTimedOut = false;
            TriggerTimer.stop();

            TriggerTimer.setTimeout([&]() {
                        TriggerTimeout();
                    } , 300); //TriggerSamplignTime set to 500ms


     }
}

void GameEffectsJOB::UniformZoomOut() {
      
     if(IsTriggerTimedOut && IsAckRecieved){
            std::vector<KineticsRequest> req = effectCreator.UniformZoomOut();
            req.push_back(KineticsRequestInstantTrigger());
            IsAckRecieved = false;
            WaitingForKineticsRequestAck = KineticsAccess::getInstance()->SetParameters(req);

            IsTriggerTimedOut = false;
            TriggerTimer.stop();

            TriggerTimer.setTimeout([&]() {
                        TriggerTimeout();
                    } , 100); //TriggerSamplignTime set to 500ms
            
     }
}



} // namespace fmSystem