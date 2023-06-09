

#include "FrameworkImplementation/PublicTypes/Delegates/KineticsResponseConvey.h"
#include "FrameworkImplementation/PublicTypes/Constants/MachineRequests.h"
#include "Framework/DataTypes/Parsers/ResponseCommandParser/KineticsResponseEEPROMRead.h"


using namespace fmKinetics;

class mock_KineticsResponseConvey : public KineticsResponseConvey
{
public:
    //MOCK_METHOD(void, commsStateChanged, (MachineCommsStates::etype State), (override));
    //MOCK_METHOD(void, newMachineFound, (Machine Device), (override));
    //MOCK_METHOD(void, RecievedRemoteCommand, (MachineRequests::etype event), (override));
    //MOCK_METHOD(void, RecievedResponseData, (vector<KineticsResponse> responeData, UUID _Acknowledgement), (override));
    //MOCK_METHOD(void, KineticsResponseDataTimeout, (UUID uuid, vector<KineticsResponse> artialResponse), (override));
    //MOCK_METHOD(void, RequestSent, (KineticsRequest request), (override));
    //MOCK_METHOD(void, ParameterTriggerSuccuss, (), (override));

    vector<std::unique_ptr<KineticsResponse>> ResponeData;
    void CommsLost() {}

    void MachiResponseTimeout(vector<std::unique_ptr<KineticsResponse>> partialResponse, UUID _Acknowledgement) {}

    void MachineResponseRecieved(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement)
    {
        ResponeData.clear();    
        CommandLabels::CommandTypes comamnd;
        for(int i=0; i<responeData.size(); i++)
        {
            ResponeData.push_back(std::move(responeData.at(i)));
        }

       

        if (ResponeData.size() == 1 && ResponeData.at(0)->ResponseType == CommandLabels::CommandTypes::EEPR)
        {
           
            KineticsResponseEEPROMRead *EEPROMRead = static_cast<KineticsResponseEEPROMRead*>(ResponeData.at(0).get());
            
            if (EEPROMRead != nullptr && EEPROMRead->ResponseType == CommandLabels::CommandTypes::EEPR && EEPROMRead->Data.size() > 0)
            {
                
            }
        }
        // printf("KRx: %s",comamnd.enumtostring.at(responeData.at(0).ResponseType).c_str());
    }
};