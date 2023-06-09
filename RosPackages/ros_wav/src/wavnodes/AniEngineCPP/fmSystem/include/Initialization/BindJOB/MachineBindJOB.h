#pragma once

#include <vector>
#include <string>

#include "UUID.h"


#include "FrameworkImplementation/PublicTypes/Delegates/KineticsResponseConvey.h"



#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"

#include "FrameworkImplementation/KineticsAccess.h"

#include "Initialization/BindJOB/BIND_STATES.h"
#include "Initialization/BindJOB/MachineBindStatusDelegate.h"

using namespace fmCommon;
using namespace fmKinetics;
using namespace std;

namespace fmSystem
{



class MachineBindJOB : public KineticsResponseConvey, public std::enable_shared_from_this<MachineBindJOB>
{

private:
    UUID WaitingForKineticsRequestAck;
    std::shared_ptr<MachineBindStatusDelegate> BindStateConvey;

    vector<std::unique_ptr<KineticsResponse>> LastKineticsResponse;
    vector<KineticsRequest> KineticsTurnRequest;
    vector<KineticsRequest> KineticsLeanRequest;
    vector<KineticsRequest> KineticsLiftRequest;
    vector<KineticsRequest> KineticsTiltRequest;

    bool MachineBindActuators = false;
    vector<Actuator::etype> BindedActuatorList;
    std::vector<std::thread> WorkerThread;

public:
    std::shared_ptr<MachineBindJOB> getPtr();


    BIND_STATES::STATES CURRENT_STATE = BIND_STATES::NA;

    //KineticsResponseConvey
    void CommsLost();
    void MachiResponseTimeout(vector<std::unique_ptr<KineticsResponse>> partialResponse, UUID _Acknowledgement) ;
    void MachineResponseRecieved(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement) ;
    //End of KineticsResponseConvey


    //Scheduler Calls
    void TakeOverResources();
    void Resume();
    void Pause();
    //End Of Scheduler calls

    void SetBindStatusConvey(std::shared_ptr<MachineBindStatusDelegate> delegate);

    void BindActuatorSignal();

    void DOSTEP();

    void notify_BindState(BIND_STATES::STATES State);

    ~MachineBindJOB();


};

} // namespace fmSystem
