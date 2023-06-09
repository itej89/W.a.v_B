
#include "SystemFlowManager.h"
#include "SystemBindings.h"

namespace fmSystem
{

          void SystemBindings::Initialize()
          {
            Manager->InitializeKineticsEngine();
          }

            void SystemBindings::AttentionOn()
            {
                Manager->AttenstionON();
            }

            void SystemBindings::AttenstionOFF()
            {
                Manager->AttenstionOFF();
            }

            void SystemBindings::UniformZoom(int ZoomPercent, int TiltPercent)
            {
                Manager->Effect_UniformZoom(ZoomPercent, TiltPercent);
            }

            void SystemBindings::UniformZoomIN()
            {
                Manager->Effect_UniformZoomIN();
            }

            void SystemBindings::UniformZoomOut()
            {
                Manager->Effect_UniformZoomOut();
            }

            void SystemBindings::Wake()
            {
                Manager->BindMachine();
            }

            void SystemBindings::Nap()
            {
                Manager->UnBindMachine();
            }

            void SystemBindings::Close()
            {
                Manager->DisconnectKineticsEngine();
            }

            SystemBindings::SystemBindings()
            {
                Manager.reset(new SystemFlowManager());
            }

             SystemBindings::~SystemBindings()
             {
             }
}