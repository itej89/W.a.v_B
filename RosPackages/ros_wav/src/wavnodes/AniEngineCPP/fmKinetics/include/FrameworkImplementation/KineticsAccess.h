#pragma once

#include <string>

#include "UUID.h"
#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsCommsConvey.h"
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsRemoteRequestConvey.h"
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsResponseConvey.h"
#include "FrameworkImplementation/PublicTypes/Delegates/KineticsParameterUpdatesConvey.h"
#include "FrameworkImplementation/PublicTypes/EEPROMDetails.h"
#include "Framework/DataTypes/Parsers/RequestCommandParser/KineticsRequestAngle.h"


#include "Framework/MachineCommunicationEngine.h"



using std::string;

using namespace fmCommon;


namespace fmKinetics
{
    class KineticsAccess: public MachineCommsConvey, public std::enable_shared_from_this<KineticsAccess>{
        


        private:
          static std::shared_ptr<KineticsAccess> Instance; 

          KineticsAccess() {} 

        public:


        std::shared_ptr<KineticsAccess> getPtr()
        {
            return shared_from_this();
        }
    
        //Initializes the Communication module
         void SetCommsDelegate(std::shared_ptr<KineticsCommsConvey> delegate);

        //this will set the listener for any remote events from the machine
         void SetMachineRemoteRequestListener(std::shared_ptr<KineticsRemoteRequestConvey> delegate);

        //this will set the listener of the machine responses for the previously sent request
         void SetKineticsResposeListener(std::shared_ptr<KineticsResponseConvey> delegate);

        //this will set the listener for any kinetics requests sent and trigger responses
        //meant to be used for updating system state
         void SetKineticsParameterUpdatesListener(std::shared_ptr<KineticsParameterUpdatesConvey> delegate);

         void InitializeComms();

        //Start scanning of machines
         void StartScan();

        //Stops scanning for machines
         void StopScan();

        //Connect to the given machine
         void ConnectToMachine(Machine machine);

        //Check If Comms is in connected state
         bool IsConnectedToMachine();

        //Disconnects from any connected machine
         void DisconnectMachine();




        //Handles Functionality to show explicit indication when machine has attention for the user input
        //In version 1 this will be turning on white led
         UUID IndicateAttention();

        //Handles Functionality to show explicit indication when machine is not paying attention for the user input
        //In version 1 this will be turning off white led
         UUID IndicateNoAttention();



        //request machines for the current angle of the given actuator
         UUID ReadDegree(Actuator::etype actuator);

        //request machine on the status of the proximity sensor
         UUID ReadProximity();

        //request machine for status if, all actuators are completed moving or not
         UUID ReadMotionState(Actuator::etype actuatorType);

        //request machine for status if, the power is on to the actuator
         UUID ReadActuatorPowerStatus(Actuator::etype actuator);

        //request machine for status if, the signal is attached to the actuator
         UUID ReadActuatorSignalStatus(Actuator::etype actuator);

        //request machine for status if, the power is on to the lock
         UUID ReadLockPowerStatus();

        //request machine for status if, the signal is attached to lock
         UUID ReadLockSignalStatus();


        //switch on power to the actuator
         UUID PowerOnMotor(Actuator::etype actuator);

        //switch off power to the actuator
         UUID PowerOffMotor(Actuator::etype actuator);

        //Attach Signal to actuator
         UUID AttachSignalToActuator(Actuator::etype actuator);

        //Detach Signal to actuator
         UUID DetachSignalToActuator(Actuator::etype actuator);


        //switch on power to the lock motor
         UUID PowerOnLockMotor();

        //switch off power to the lock motor
         UUID PowerOffLockMotor();

        //Attach Signal to lock actuator
         UUID AttachSignalToALockctuator();

        //Detach Signal to lock actuator
         UUID DetachSignalToLockActuator();

        //This Will Reset MachineComms Context during app deactivate or activate
         void ResetCommsContext();

        //requests machine to start motion with the previously set parameters
         UUID StartMotion();

        //Stops current ongoing motion and requests machine to start motion with the previously set parameters immediately
         UUID StartInstantMotion();

        //sets the parameters for the given actuator to be used in the next upload request
         UUID SetParameters(vector<KineticsRequest> parameters);

          //sets the parameters for game effects
         UUID SetGameEffectParameters(vector<KineticsRequest> parameters);

        //Sends comamnd to read actuator communication address
         UUID ReadActuatorAddress(Actuator::etype actuator);

        //Extracts Actuator address from machine response and saves in config for future use
         bool SetActuatorAddress(Actuator::etype actuator, vector<std::unique_ptr<KineticsResponse>>  response);

        //Sends comamnd to read actuator Delta Rese angle
         UUID ReadDeltaResetAngle(Actuator::etype actuator);

        //Extracts Actuator Delta Reset angle from machine response and saves in config for future use
         bool SetDeltaResetAngle(Actuator::etype actuator,vector<std::unique_ptr<KineticsResponse>>  response);

        //Sends comamnd to read actuator referance angle
         UUID ReadReferanceAngle(Actuator::etype actuator);

        //Extracts Actuator referance angle from machine response and saves in config for future use
         bool SetReferanceAngle(Actuator::etype actuator,vector<std::unique_ptr<KineticsResponse>>  response);

        //Create KinticAngleRequest from the KineticDegreeresponse for initial actuator initial settings
         KineticsRequestAngle GetKineticRequestAngleFromDegreeResponse(Actuator::etype actuator, vector<std::unique_ptr<KineticsResponse>>  response);

        //Returns Delta Angle by substracting referance angle for the actuator
         int GetDeltaAngleFromFullAngle(int FullAngle, Actuator::etype actuator);

        //Returns Delta Angle by substracting referance angle for the actuator
         int GetFullAngleFromDeltaAngle(int DeltaAngle, Actuator::etype actuator);

        //Reads any predefined machine command that is present in db using name
         vector<KineticsRequest> GetPredefinedKineticsRequestAngleByName(string Name);

        //Check if any device detected on proximty sensor from the read proximity repsonse
         bool CheckProximity(vector<std::unique_ptr<KineticsResponse>>  response);

        //Check if power is connected to actuator from the read actuator power status repsonse
         bool CheckActuatorPowerStatus(vector<std::unique_ptr<KineticsResponse>>  response);

        //Check if Signal is connected to actuator from the read actuator power status repsonse
         bool CheckActuatorSignalStatus(vector<std::unique_ptr<KineticsResponse>>  response);

        //Check if power is connected to lock from the read actuator power status repsonse
         bool CheckLockPowerStatus(vector<std::unique_ptr<KineticsResponse>>  response);

        //Check if Signal is connected to lock from the read actuator power status repsonse
         bool CheckLockSignalStatus(vector<std::unique_ptr<KineticsResponse>>  response);

        //requests machine to start power off sequence
         UUID TurnOffPower();

        //writes given bytes to mainboard eeprom Address location
          UUID WriteToEEPROM(EEPROMDetails AddressDetails, int Data);

        //Check if EEPROM write is successful
          bool CheckWriteToEEPROM(KineticsResponse Response);

        //read given number of bytes from from mainboard eeprom Address location
          UUID ReadFromEEPROM(EEPROMDetails AddressDetails);

        //Returns the payload bytes from EEPROMReadResonse Command
         vector<int> ExtractBytesFromEEPROMReadResponse(KineticsResponse EEPROMReadResponse);

        //read given number of bytes from from Servo board eeprom Address location
          UUID ReadFromServoEEPROM(Actuator::etype actuator, EEPROMDetails AddressDetails);


        //Returns the payload bytes from ServoEEPROMReadResonse Command
        vector<int> ExtractBytesFromServoEEPROMReadResponse(KineticsResponse EEPROMReadResponse);

        //Deletes calibration Data From DataBase for the given actuator
          void DeleteCalibrationDataForActuator(Actuator::etype actuator);

        //Saves Servo Degree and ADC Value
          void SaveActuatorCalibrationData(Actuator::etype actuator, int Degree, int ADC );

    std::shared_ptr<MachineCommunicationEngine> machineComms{new MachineCommunicationEngine()};


    //Machine Communication Delegate
    std::shared_ptr<KineticsCommsConvey> notify_KineticsComms;

    //Machine remote events Delegate
    std::shared_ptr<KineticsRemoteRequestConvey> notify_KineticsRemoteRequest;

    //Machine response Delegate
    std::shared_ptr<KineticsResponseConvey> notify_KineticsResponse;

    //Machine Parameter Updates Delegate
    std::shared_ptr<KineticsParameterUpdatesConvey> notify_KineticsParameterUpdates;


    //This variable will be used to initialize Comms delegates first only
    bool IsCommsDelegatesInitialized = false;



    virtual void commsStateChanged(MachineCommsStates::etype State);
    virtual void newMachineFound(Machine Device);

    virtual void RecievedRemoteCommand(MachineRequests::etype event);
    virtual void RecievedResponseData(vector<std::unique_ptr<KineticsResponse>> responeData, UUID _Acknowledgement);
    virtual void KineticsResponseDataTimeout(UUID uuid, vector<std::unique_ptr<KineticsResponse>> artialResponse);

    virtual void RequestSent(KineticsRequest request);
    virtual void ParameterTriggerSuccuss();

    static std::shared_ptr<KineticsAccess> getInstance() 
    { 
        if (Instance==nullptr) 
            Instance = std::shared_ptr<KineticsAccess>(new KineticsAccess()); 
        return Instance; 
    }
  
     
    };
}