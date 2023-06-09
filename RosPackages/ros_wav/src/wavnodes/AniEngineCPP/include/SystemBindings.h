#pragma once

#include <memory>

class SystemFlowManager;

namespace fmSystem
{

    class SystemBindings
    {
    private:
       std::shared_ptr<SystemFlowManager> Manager;
    public:
            void Initialize();
            void Wake();
            void Nap();
            void Close();
            void AttentionOn();
            void AttenstionOFF();
            void UniformZoom(int ZoomPercent, int TiltPercent);
            void UniformZoomIN();
            void UniformZoomOut();

            SystemBindings();
            ~SystemBindings();
    };
    
}
