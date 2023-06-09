#pragma once



#include <vector>
#include <string>
#include <mutex>

#include "UUID.h"
#include "Timer.h"


#include "FrameworkImplementation/PublicTypes/Delegates/KineticsResponseConvey.h"



#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"

#include "FrameworkImplementation/KineticsAccess.h"

#include "GameEffects/EffectCreator.h"

using namespace fmCommon;
using namespace fmKinetics;
using namespace std;

namespace fmSystem
{



class GameEffectsJOB : public KineticsResponseConvey, public std::enable_shared_from_this<GameEffectsJOB>
{



private:
    UUID WaitingForKineticsRequestAck;
    Timer TriggerTimer;
    bool IsTriggerTimedOut = true;
    bool IsAckRecieved = true;
    enum STATE {NA, ZOOM} CURENT_STATE = NA;
    int LiftPWM;
    int LeanPWM;
    int TiltPWM;
    int Zoomlevel = 0;
    int Tiltlevel = 0;
    int MaxZoomlevel = 0;
    int MaxTiltlevel = 0;
    int InputZoomLevel = 0;
    int InputTiltLevel = 0;

    int LastLiftPWM = 0;
    int LastLeanPWM = 0;
    int LastTiltPWM = 0;

public:
    std::shared_ptr<GameEffectsJOB> getPtr();
    EffectCreator effectCreator;

    //KineticsResponseConvey
    void CommsLost();
    void MachiResponseTimeout(vector<std::unique_ptr<KineticsResponse>> partialResponse, UUID _Acknowledgement) ;
    void MachineResponseRecieved(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement) ;
    //End of KineticsResponseConvey

    void TriggerTimeout();


    //Scheduler Calls
    void TakeOverResources();
    void Resume();
    void Pause();
    //End Of Scheduler calls

    void UniformZoom(int ZoomPercent, int TiltPercent);

    void UniformZoomIN();

    void UniformZoomOut();

    void DOSTEP();

private:
    std::mutex m_effectLock;

};

} // namespace fmSystem
