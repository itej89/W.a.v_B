#pragma once


#include "FrameworkImplementation/PublicTypes/Delegates/KineticsCommsConvey.h"
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsParameterUpdatesConvey.h"
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsRemoteRequestConvey.h"


#include "Initialization/BindJOB/MachineBindJOB.h"
#include "JOBS/GameEffectsJOB.h"

namespace  fmSystem
{
    class  SystemFlowManager:   public MachineBindStatusDelegate, public KineticsCommsConvey, public KineticsParameterUpdatesConvey,
                                public KineticsRemoteRequestConvey, public std::enable_shared_from_this<SystemFlowManager>
    {
        private:
            std::shared_ptr<MachineBindJOB> machineBindJOB{new MachineBindJOB()};
            std::shared_ptr<GameEffectsJOB> gameEffectsJOB{new GameEffectsJOB()};

        public:
        std::shared_ptr<SystemFlowManager> getPtr();

        //KineticsCommsConvey
        void commsStateChanged(MachineCommsStates::etype State);
        void newMachineFound(Machine Device);
        //End of KineticsCommsConvey


        //KineticsParameterUpdatesConvey
        void ParameterUpdated(KineticsRequest request);
        void ParametersSetSuccessfully();
        //End of KineticsParameterUpdatesConvey


        //KineticsRemoteRequestConvey
        void machineRequested(MachineRequests::etype Request);
        //End of KineticsRemoteRequestConvey


        //MachineBindStatusDelegate
        void BindStateChanged(BIND_STATES::STATES State);
        //End of MachineBindStatusDelegate


        void InitializeKineticsEngine();
        void BindMachine();
        
        void Effect_UniformZoom(int ZoomPercent, int TiltPercent);
        void Effect_UniformZoomIN();
        void Effect_UniformZoomOut();

        void UnBindMachine();
        void AttenstionON();
        void AttenstionOFF();

        void DisconnectKineticsEngine();
    };
    
} // namespace  fmSystem
