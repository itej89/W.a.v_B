#include "SystemFlowManager.h"

namespace fmSystem
{
        std::shared_ptr<SystemFlowManager> SystemFlowManager::getPtr()
        {
                return shared_from_this();
        }


        //KineticsCommsConvey
        void SystemFlowManager::commsStateChanged(MachineCommsStates::etype State){}
        void SystemFlowManager::newMachineFound(Machine Device){}
        //End of KineticsCommsConvey


        //KineticsParameterUpdatesConvey
        void SystemFlowManager::ParameterUpdated(KineticsRequest request){}
        void SystemFlowManager::ParametersSetSuccessfully(){}
        //End of KineticsParameterUpdatesConvey


        //KineticsRemoteRequestConvey
        void SystemFlowManager::machineRequested(MachineRequests::etype Request){}
        //End of KineticsRemoteRequestConvey


        //MachineBindStatusDelegate
        void SystemFlowManager::BindStateChanged(BIND_STATES::STATES State)
        {
                printf("binded finsihed");
                switch (State)
                {
                case BIND_STATES::MACHINE_BINDED :
                        gameEffectsJOB->TakeOverResources();
                        gameEffectsJOB->Resume();
                break;
                
                default:
                break;
                }
        }
        //End of MachineBindStatusDelegate


        void SystemFlowManager::InitializeKineticsEngine()
        {
                KineticsAccess::getInstance()->InitializeComms();

                std::shared_ptr<KineticsCommsConvey> m_KineticsCommsConvey{getPtr()};
                KineticsAccess::getInstance()->SetCommsDelegate(m_KineticsCommsConvey);

                std::shared_ptr<KineticsParameterUpdatesConvey> m_KineticsParameterUpdatesConvey{getPtr()};
                KineticsAccess::getInstance()->SetKineticsParameterUpdatesListener(m_KineticsParameterUpdatesConvey);

                std::shared_ptr<KineticsRemoteRequestConvey> m_KineticsRemoteRequestConvey{getPtr()};
                KineticsAccess::getInstance()->SetMachineRemoteRequestListener(m_KineticsRemoteRequestConvey);

              
        }

        void SystemFlowManager::AttenstionON()
        {
                KineticsAccess::getInstance()->IndicateAttention();
        }

        void SystemFlowManager::AttenstionOFF()
        {
                KineticsAccess::getInstance()->IndicateNoAttention();
        }

        void SystemFlowManager::BindMachine() {
                machineBindJOB->TakeOverResources();
                 machineBindJOB->SetBindStatusConvey(getPtr());
                machineBindJOB->BindActuatorSignal();
        }


        void SystemFlowManager::Effect_UniformZoom(int ZoomPercent, int TiltPercent)
        {
                 if(machineBindJOB->CURRENT_STATE == BIND_STATES::MACHINE_BINDED)
                {
                        gameEffectsJOB->UniformZoom(ZoomPercent, TiltPercent);
                }
        }
        
        void SystemFlowManager::Effect_UniformZoomIN()
        {
                if(machineBindJOB->CURRENT_STATE == BIND_STATES::MACHINE_BINDED)
                {
                        gameEffectsJOB->UniformZoomIN();
                }
        }
        void SystemFlowManager::Effect_UniformZoomOut()
        {
                if(machineBindJOB->CURRENT_STATE == BIND_STATES::MACHINE_BINDED)
                {
                        gameEffectsJOB->UniformZoomOut();
                }
        }
        

        void SystemFlowManager::UnBindMachine() {}

        void SystemFlowManager::DisconnectKineticsEngine()
        {
                KineticsAccess::getInstance()->DisconnectMachine();
        }

} // namespace  fmSystem
