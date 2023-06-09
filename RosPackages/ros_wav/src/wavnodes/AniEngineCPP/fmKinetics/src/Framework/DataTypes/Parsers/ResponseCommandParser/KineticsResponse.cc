#include <memory>
#include <iostream>

#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"

#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAngle.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttachLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttachServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttentionOff.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseAttentionOn.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLOne.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLThree.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseCELLTwo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseConnectPower.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDamp.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDelay.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDettachLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDettachServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseDisconnectPower.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEasingInOut.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEEPROMRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEEPROMWrite.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseFrequency.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseInstantTrigger.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLEEPROMRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLEEPROMWrite.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseISLWrite.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLeftServoAngle.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLockPowerStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseLockSignalStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOff.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOffLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponsePowerOnLockServo.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseProximityRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseRightServoAngle.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoDegree.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoEasing.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoEEPROMRead.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoMotionCheck.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoPowerStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseServoSignalStatus.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTiming.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseTrigger.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseVelocity.h"

namespace fmKinetics
{
KineticsResponse::KineticsResponse()
{
    ResponseType = CommandLabels::CommandTypes::UNKNOWN;
}

KineticsResponse::KineticsResponse(string response)
{
    using namespace CommandLabels;
    CommandTypes _CommandTypes;
    StringX stringX;
    string allResponses = removeDelimiters(response);
    vector<string> responseList = stringX.split(allResponses, ':');
    if (responseList.size() > 0)
    {
        ResponseType = CommandLabels::CommandTypes::UNKNOWN;

        for (std::vector<string>::iterator part_response = responseList.begin(); part_response != responseList.end(); ++part_response)
        {

            vector<string> parts = stringX.split(removeDelimiters(*part_response), '#');
            if (parts.size() > 0)
            {
                DecomposedResponse.push_back(parts);

                CommandLabels::CommandTypes::etype responseType = CommandLabels::CommandTypes().stringtoenum.at(parts[0]);

                if (ResponseType != _CommandTypes.CommandTypes::UNKNOWN && ResponseType != responseType)
                {
                    ResponseType = _CommandTypes.CommandTypes::UNKNOWN;
                    return;
                }

                ResponseType = responseType;
            }
            else
            {
                return;
            }
        }

        if ((DecomposedResponse.size()) != (_CommandTypes.CommandResponseCount.at(ResponseType)))
        {
            ResponseType = CommandLabels::CommandTypes::UNKNOWN;
            return;
        }
    }
}

string KineticsResponse::removeDelimiters(string command)
{
    StringX stringX;
    command = stringX.removeDelimiter(command, '~', ':');
    return command;
}

vector<string> KineticsResponse::decomposeCommand(string command)
{
    StringX stringX;
    vector<string> data;

    if (ResponseType != CommandLabels::CommandTypes::UNKNOWN)
    {
        vector<string> parts = stringX.split(command, '#');
        if (parts.size() > 0)
        {
            if (parts.size() > 1)
            {
                for (int i = 0; i < parts.size(); i++)
                {
                    data.push_back(parts.at(i));
                }
            }
        }
    }
    return data;
}

std::unique_ptr<KineticsResponse> KineticsResponse::GetResponseObject(string response)
{
    std::unique_ptr<KineticsResponse> kineticReponse = std::make_unique<KineticsResponse>(response);
    if (kineticReponse->ResponseType != CommandLabels::CommandTypes::UNKNOWN)
    {
        switch (kineticReponse->ResponseType)
        {
        case CommandLabels::CommandTypes::ANG:
            return std::make_unique<KineticsResponseAngle>(response);
        case CommandLabels::CommandTypes::TMG:
            return std::make_unique<KineticsResponseTiming>(response);
        case CommandLabels::CommandTypes::TRG:
            return std::make_unique<KineticsResponseTrigger>(response);
        case CommandLabels::CommandTypes::ITRG:
            return std::make_unique<KineticsResponseInstantTrigger>(response);
        case CommandLabels::CommandTypes::DEG:
            return std::make_unique<KineticsResponseServoDegree>(response);
        case CommandLabels::CommandTypes::ATC:
            return std::make_unique<KineticsResponseAttachServo>(response);
        case CommandLabels::CommandTypes::DTC:
            return std::make_unique<KineticsResponseDettachServo>(response);
        case CommandLabels::CommandTypes::LLK:
            return std::make_unique<KineticsResponseLeftServoAngle>(response);
        case CommandLabels::CommandTypes::RLK:
            return std::make_unique<KineticsResponseLeftServoAngle>(response);
        case CommandLabels::CommandTypes::EAS:
            return std::make_unique<KineticsResponseServoEasing>(response);
        case CommandLabels::CommandTypes::INO:
            return std::make_unique<KineticsResponseEasingInOut>(response);
        case CommandLabels::CommandTypes::PRX:
            return std::make_unique<KineticsResponseProximityRead>(response);
        case CommandLabels::CommandTypes::CELL1:
            return std::make_unique<KineticsResponseCELLOne>(response);
        case CommandLabels::CommandTypes::CELL2:
            return std::make_unique<KineticsResponseCELLTwo>(response);
        case CommandLabels::CommandTypes::CELL3:
            return std::make_unique<KineticsResponseCELLThree>(response);
        case CommandLabels::CommandTypes::SLEEP:
            return std::make_unique<KineticsResponse>(response);
        case CommandLabels::CommandTypes::VEN:
            return std::make_unique<KineticsResponseAttentionOn>(response);
        case CommandLabels::CommandTypes::VNO:
            return std::make_unique<KineticsResponseAttentionOff>(response);
        case CommandLabels::CommandTypes::CPW:
            return std::make_unique<KineticsResponseConnectPower>(response);
        case CommandLabels::CommandTypes::DPW:
            return std::make_unique<KineticsResponseDisconnectPower>(response);
        case CommandLabels::CommandTypes::LAT:
            return std::make_unique<KineticsResponseAttachLockServo>(response);
        case CommandLabels::CommandTypes::LDT:
            return std::make_unique<KineticsResponseDettachLockServo>(response);
        case CommandLabels::CommandTypes::LON:
            return std::make_unique<KineticsResponsePowerOnLockServo>(response);
        case CommandLabels::CommandTypes::LOF:
            return std::make_unique<KineticsResponsePowerOffLockServo>(response);
        case CommandLabels::CommandTypes::SMV:
            return std::make_unique<KineticsResponseServoMotionCheck>(response);
        case CommandLabels::CommandTypes::FRQ:
            return std::make_unique<KineticsResponseFrequency>(response);
        case CommandLabels::CommandTypes::DEL:
            return std::make_unique<KineticsResponseDelay>(response);
        case CommandLabels::CommandTypes::DMP:
            return std::make_unique<KineticsResponseDamp>(response);
        case CommandLabels::CommandTypes::VEL:
            return std::make_unique<KineticsResponseVelocity>(response);
        case CommandLabels::CommandTypes::ISLR:
            return std::make_unique<KineticsResponseISLRead>(response);
        case CommandLabels::CommandTypes::ISLW:
            return std::make_unique<KineticsResponseISLWrite>(response);
        case CommandLabels::CommandTypes::ISLER:
            return std::make_unique<KineticsResponseISLEEPROMRead>(response);

        case CommandLabels::CommandTypes::ISLEW:
            return std::make_unique<KineticsResponseISLEEPROMWrite>(response);
        case CommandLabels::CommandTypes::EEPR:
        {
           
            return std::move( std::unique_ptr<KineticsResponse>(new KineticsResponseEEPROMRead(response)));
        }
        case CommandLabels::CommandTypes::EEPW:
            return std::make_unique<KineticsResponseEEPROMWrite>(response);
        case CommandLabels::CommandTypes::UNKNOWN:
            return std::make_unique<KineticsResponse>(response);
        case CommandLabels::CommandTypes::SAT:
            return std::make_unique<KineticsResponseServoSignalStatus>(response);
        case CommandLabels::CommandTypes::SPW:
            return std::make_unique<KineticsResponseServoPowerStatus>(response);
        case CommandLabels::CommandTypes::LSA:
            return std::make_unique<KineticsResponseLockSignalStatus>(response);
        case CommandLabels::CommandTypes::LPW:
            return std::make_unique<KineticsResponseLockPowerStatus>(response);
        case CommandLabels::CommandTypes::SEPR:
            return std::make_unique<KineticsResponseServoEEPROMRead>(response);
        }
    }

    return kineticReponse;
}
} // namespace fmKinetics