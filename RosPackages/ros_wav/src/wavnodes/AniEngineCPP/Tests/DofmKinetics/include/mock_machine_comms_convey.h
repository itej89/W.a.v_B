
#pragma once

#include <iostream>

#include "gmock/gmock.h"

#include "Framework/DataTypes/Delegates/MachineCommsConvey.h"

#include "UUID.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequest.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponse.h"
#include "FrameworkImplementation/PublicTypes/Constants/MachineCommsStates.h"
#include "FrameworkImplementation/PublicTypes/Constants/MachineRequests.h"
#include "FrameworkImplementation/PublicTypes/Machine.h"

using fmKinetics::MachineCommsConvey;
using fmKinetics::MachineCommsStates;
using fmKinetics::Machine;
using fmKinetics::MachineRequests;
using fmKinetics::KineticsRequest;
using fmKinetics::KineticsResponse;
using fmCommon::UUID;

using std::vector;

class mock_machine_comms_convey: public MachineCommsConvey
{
    public:
        //MOCK_METHOD(void, commsStateChanged, (MachineCommsStates::etype State), (override));
        //MOCK_METHOD(void, newMachineFound, (Machine Device), (override));
        //MOCK_METHOD(void, RecievedRemoteCommand, (MachineRequests::etype event), (override));
        //MOCK_METHOD(void, RecievedResponseData, (vector<KineticsResponse> responeData, UUID _Acknowledgement), (override));
        //MOCK_METHOD(void, KineticsResponseDataTimeout, (UUID uuid, vector<KineticsResponse> artialResponse), (override));
        //MOCK_METHOD(void, RequestSent, (KineticsRequest request), (override));
        //MOCK_METHOD(void, ParameterTriggerSuccuss, (), (override));
       
        void commsStateChanged (MachineCommsStates::etype State)
        {
            std::cout << "" << std::endl;
        }

        void newMachineFound (Machine Device)
        {
            std::cout << "" << std::endl;
        }

        void RecievedRemoteCommand (MachineRequests::etype event)
        {
            std::cout << event << std::endl;
        }

        void RecievedResponseData (vector<std::unique_ptr<KineticsResponse>>  responeData, UUID _Acknowledgement)
        {
            if(responeData.size() > 0)
            {
                fmKinetics::CommandLabels::CommandTypes commandtype;
                for(int i = 0; i< responeData.size(); i++)
                std::cout << "Rx : "+commandtype.enumtostring.at(responeData.at(i)->ResponseType) << std::endl;
            }
        }

        void KineticsResponseDataTimeout (UUID uuid, vector<std::unique_ptr<KineticsResponse>>  artialResponse)
        {
            std::cout << "" << std::endl;
        }

        void RequestSent (KineticsRequest request)
        {
            fmKinetics::CommandLabels::CommandTypes commandtype;
            std::cout << "Tx : "+commandtype.enumtostring.at(request.RequestType) << std::endl;
        }

        void ParameterTriggerSuccuss ()
        {
            std::cout << "" << std::endl;
        }
};