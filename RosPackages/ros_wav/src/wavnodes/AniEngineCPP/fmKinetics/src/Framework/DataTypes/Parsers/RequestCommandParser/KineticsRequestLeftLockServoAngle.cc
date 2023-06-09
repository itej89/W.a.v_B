#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestLeftLockServoAngle.h"

namespace fmKinetics
{
      KineticsRequestLeftLockServoAngle::KineticsRequestLeftLockServoAngle(int angle, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::LLK)
        {
            Angle = angle;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            PWM_VALUE = CommandHelper.ConvertAngleToPWMValue(Angle);
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(PWM_VALUE)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

        KineticsRequestLeftLockServoAngle::KineticsRequestLeftLockServoAngle(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::LLK)
        {
            string _command = removeDelimiters(command);
            vector<string> contents = decomposeCommand( _command);
            if(contents.size() == 2)
            {
                int address = std::stoi(contents.at(1));
               
                    ActuatorType = MachineConfig::Instance.getActuatorWith(address);
                    Angle = std::stoi(contents.at(2));
                
            }
        }
}