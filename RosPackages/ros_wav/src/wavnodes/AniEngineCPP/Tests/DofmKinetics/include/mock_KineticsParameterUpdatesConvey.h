
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsParameterUpdatesConvey.h"

using namespace fmKinetics;

class mock_KineticsParameterUpdatesConvey: public KineticsParameterUpdatesConvey
{
    public:
        //MOCK_METHOD(void, commsStateChanged, (MachineCommsStates::etype State), (override));
        //MOCK_METHOD(void, newMachineFound, (Machine Device), (override));
        //MOCK_METHOD(void, RecievedRemoteCommand, (MachineRequests::etype event), (override));
        //MOCK_METHOD(void, RecievedResponseData, (vector<KineticsResponse> responeData, UUID _Acknowledgement), (override));
        //MOCK_METHOD(void, KineticsResponseDataTimeout, (UUID uuid, vector<KineticsResponse> artialResponse), (override));
        //MOCK_METHOD(void, RequestSent, (KineticsRequest request), (override));
        //MOCK_METHOD(void, ParameterTriggerSuccuss, (), (override));

        void ParameterUpdated(KineticsRequest request)
        {}

        void ParametersSetSuccessfully()
        {}
};