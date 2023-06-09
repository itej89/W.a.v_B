#include "FrameworkImplementation/PublicTypes/Config/MachineConfig.h"

namespace fmKinetics
{


            MachineConfig MachineConfig::Instance;
            Actuator::etype MachineConfig::getActuatorWith(int address)
            {

                	std::map<Actuator::etype, ActuatorCalibration*>::iterator it = MachineActuatorList.begin();
 
                    while (it != MachineActuatorList.end())
                    {
                        if(it->second->Address == address)
                        {
                            return it->first;
                        }
                        it++;
                    }

                return Actuator::UNKNOWN;
            }
}