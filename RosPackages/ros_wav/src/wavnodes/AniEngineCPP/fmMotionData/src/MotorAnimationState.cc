
#include<tuple>

#include "StringX.h"
#include "nlohmann/json.hpp"

#include "Framework/DataTypes/Constants/CommandLabels.h"
#include "FrameworkImplementation/KineticsAccess.h"
#include "MotorAnimationState.h"


using namespace fmCommon;
using jsonObject = nlohmann::json;

using namespace fmKinetics;

namespace fmMotionData
{


            bool MotorAnimationState::setKineticsState(std::unique_ptr<KineticsRequestAngle> request)
            {
                switch (request->RequestType)
                {
                case CommandLabels::CommandTypes::ANG:
                    Angle = std::make_tuple(request->Angle, true);
                    return true;
                default:
                    break;
                }

                return false;
            }


            std::vector<KineticsRequest> MotorAnimationState::GetStateCommandString(Actuator::etype actuator)
            {
                std::vector<KineticsRequest> Command;
                if (std::get<1>(Angle) == true)
                {
                    int angle = std::get<0>(Angle);
                    if (IsDeltaAngle == true)
                    {
                        angle = KineticsAccess::getInstance()->GetFullAngleFromDeltaAngle(angle, actuator);
                    }
                    Command.push_back(KineticsRequestAngle((angle), actuator));
                }
                return Command;
            }


            void MotorAnimationState::parseJson(jsonObject json)
            {
                try
                {

                    StringX Xstr;

                    jsonObject dictionary = json["AnimationState"].get<jsonObject>();

                    IsDeltaAngle = Xstr.to_bool(dictionary["IsDeltaAngle"].get<string>());

                    dictionary = dictionary["Angle"].get<jsonObject>();

                    Angle = std::make_tuple(std::atoi(dictionary["key"].get<string>().c_str()), Xstr.to_bool(dictionary["value"].get<string>()));
                }
                catch (int e)
                {
                }
            }

             std::string MotorAnimationState::Json()
            {

                std::string json = "";

                json = json.append("{ \"AnimationState\" : {");
                json = json.append(" \"IsDeltaAngle\" : \"" + std::to_string(IsDeltaAngle) + "\" , ");
                json = json.append(" \"Angle\" : {");
                json = json.append((" \"key\" : \"" + std::to_string(std::get<0>(Angle)) + "\" , " + " \"value\" : \"" + std::to_string(std::get<1>(Angle)) + "\" "));
                json = json.append("}}");

                json = json.append("}");

                return json;
            }


            MotorAnimationState::MotorAnimationState() {}


            MotorAnimationState::MotorAnimationState(AnimationObject _TargetObject,
                                std::tuple<int, bool> _Angle)
            {
                Angle = _Angle;
            }
}