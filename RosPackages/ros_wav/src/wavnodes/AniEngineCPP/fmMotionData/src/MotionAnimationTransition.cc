
#include<tuple>


#include "DataTypes/Constants/AnimationFillModes.h"

#include "MotionAnimationTransition.h"



namespace fmMotionData
{
 bool MotionAnimationTransition::setKineticsTransition(std::unique_ptr<KineticsRequest> request)
        {
            switch(request->RequestType) {
            case CommandLabels::CommandTypes::TMG:
                Timing = (static_cast<KineticsRequestTiming*>(request.get()))->Timing;
                return true;
            case CommandLabels::CommandTypes::DEL:
                Delay = (static_cast<KineticsRequestDelay*>(request.get()))->Delay;
                return true;
            case CommandLabels::CommandTypes::FRQ:
                Frequency = (static_cast<KineticsRequestFrequency*>(request.get()))->Frequency;
                return true;
            case CommandLabels::CommandTypes::DMP:
                Damp = (static_cast<KineticsRequestDamp*>(request.get()))->Damping;
                return true;
            case CommandLabels::CommandTypes::VEL:
                Velocity = (static_cast<KineticsRequestVelocity*>(request.get()))->Velocity;
                return true;
            case CommandLabels::CommandTypes::EAS:
                EasingFunction = (static_cast<KineticsRequestServoEasing*>(request.get()))->EasingFunction;
                return true;
            case CommandLabels::CommandTypes::INO:
                EasingType = (static_cast<KineticsRequestEasingInOut*>(request.get()))->EasingType;
                return true;
            default:
                break;
            }

            return false;
        }

         std::vector<KineticsRequest> MotionAnimationTransition::GetTransitionCommandString(Actuator::etype actuator) {
            std::vector<KineticsRequest> Command;
            Command.push_back(KineticsRequestServoEasing(EasingFunction, actuator));
            Command.push_back(KineticsRequestEasingInOut(EasingType, actuator));
            Command.push_back(KineticsRequestTiming(Timing, actuator));
            Command.push_back(KineticsRequestDelay(Delay, actuator));

            if(Timing == 0 && Delay ==0)
            {
                std::cout<<("MotionTransition","ZERO TIMING CONDITION")<< std::endl;
            }

            if(EasingFunction == CommandLabels::EasingFunction::TRI ||
                EasingFunction == CommandLabels::EasingFunction::SNW ||
                EasingFunction == CommandLabels::EasingFunction::TRW)
            {
                Command.push_back(KineticsRequestFrequency(Frequency,  actuator));
            }

            if(EasingFunction == CommandLabels::EasingFunction::SPR)
            {
                Command.push_back(KineticsRequestFrequency(Frequency,  actuator));
                Command.push_back(KineticsRequestDamp(Damp,  actuator));
                Command.push_back(KineticsRequestVelocity(Velocity, actuator));
            }

            return Command;
        }

        void MotionAnimationTransition::parseJson(jsonObject json)
        {
            try {
                jsonObject dictionary = json["Transition"].get<jsonObject>();

                Timing = std::atoi(dictionary["Timing"].get<string>().c_str());
                Delay = std::atoi(dictionary["Delay"].get<string>().c_str());
                Frequency = std::atoi(dictionary["Frequency"].get<string>().c_str());
                Damp = std::atoi(dictionary["Damp"].get<string>().c_str());
                Velocity = std::atoi(dictionary["Velocity"].get<string>().c_str());

                CommandLabels::EasingFunction easingFucntion;
                EasingFunction = easingFucntion.stringtoenum.at(dictionary["EasingFunction"].get<std::string>() );

                CommandLabels::EasingType easingType;
                EasingType = easingType.stringtoenum.at(dictionary["EasingType"].get<std::string>());
            }
            catch (int e)
            {}
        }

        std::string MotionAnimationTransition::Json()
        {

            std::string json = "";

            json = json.append("{ \"Transition\" : {");

            json = json.append(" \"Timing\" : \""+std::to_string(Timing)+"\" ,");

            json = json.append(" \"Delay\" : \""+std::to_string(Delay)+"\" ,");

            json = json.append(" \"Velocity\" : \""+std::to_string(Velocity)+"\" ,");

            json = json.append(" \"Frequency\" : \""+std::to_string(Frequency)+"\" ,");

            json = json.append(" \"Damp\" : \""+std::to_string(Damp)+"\" ,");

            CommandLabels::EasingFunction easingFucntion;
            json = json.append(" \"EasingFunction\" : \""+easingFucntion.enumtostring.at(EasingFunction)+"\" ,");

            CommandLabels::EasingType easingType;
            json = json.append(" \"EasingType\" : \""+easingType.enumtostring.at(EasingType)+"\" ");

            json = json.append("}}");

            return json;

        }


        MotionAnimationTransition::MotionAnimationTransition()
        {}

        MotionAnimationTransition::MotionAnimationTransition(
            int _Timing,
            int _Delay,
            int _Frequency,
            int _Damp,
            CommandLabels::EasingFunction::etype _EasingFunction,
            CommandLabels::EasingType::etype _EasingType)
        {
            Timing = _Timing;
            Delay = _Delay;
            Frequency = _Frequency;
            Damp = _Damp;
            EasingFunction = _EasingFunction;
            EasingType = _EasingType;
        }

}