#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"

namespace fmKinetics
{

    KineticsRequestAngle::KineticsRequestAngle() : KineticsRequestForActuator(CommandLabels::CommandTypes::ANG){}
    
   KineticsRequestAngle::KineticsRequestAngle(int angle, Actuator::etype actuatorType)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::ANG)
        {
            Angle = angle;
            ActuatorType = actuatorType;

            MachineCommandHelper CommandHelper;
            PWM_VALUE = CommandHelper.ConvertAngleToPWMValue(Angle);
            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(PWM_VALUE)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

           KineticsRequestAngle::KineticsRequestAngle(Actuator::etype actuatorType, int pwm)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::ANG)
        {
            ActuatorType = actuatorType;

            vector<string> c {std::to_string(MachineConfig::Instance.MachineActuatorList.at(ActuatorType)->Address), std::to_string(pwm)};

            string Command = formCommand(c);

            Request = addDelimiters(Command);
        }

       KineticsRequestAngle::KineticsRequestAngle(string command)
        : KineticsRequestForActuator(CommandLabels::CommandTypes::ANG)
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