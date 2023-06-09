#pragma once

#include <string>
#include <map>

using std::string;
using std::map;

namespace fmKinetics
{
     namespace CommandLabels
    {
        
              class EasingFunction
                {
                     public:
                        enum etype
                        {
                    SIN,
                    QAD,
                    LIN,
                    EXP,
                    ELA,
                    CIR,
                    BOU,
                    BAK,
                    TRI,
                    TRW,
                    SNW,
                    SPR
                     };
                        const map<string, etype> stringtoenum{{"SIN", SIN}, {"QAD", QAD}, {"LIN", LIN}, {"EXP", EXP}, {"ELA", ELA}, {"CIR", CIR},
                                                              {"BOU", BOU}, {"BAK", BAK}, {"TRI", TRI}, {"TRW", TRW}, {"SNW", SNW}, {"SPR", SPR}};

                        const map<etype, string> enumtostring{{SIN, "SIN"}, {QAD, "QAD"}, {LIN, "LIN"}, {EXP, "EXP"}, {ELA, "ELA"}, {CIR, "CIR"},
                                                              {BOU, "BOU"}, {BAK, "BAK"}, {TRI, "TRI"}, {TRW, "TRW"}, {SNW, "SNW"}, {SPR, "SPR"} };
                };

                class EasingType{
                    public:
                        enum etype
                        {
                            IN ,
                            OU ,
                            IO
                        };
                        const map<string, etype> stringtoenum{{"IN", IN}, {"OU", OU}, {"IO", IO}};

                        const map<etype, string> enumtostring{{IN, "IN"}, {OU, "OU"}, {IO, "IO"} };
                };

                class CommandTypes
                {
                    public:
                        enum etype{
                            ANG,  // Servo command to set angle in PWM ~ANG#6#[PWM : 544-2400]:
                            TMG,  // Servo command to set TIMING ~TMG#6#[ms]:
                            TRG,  // Command to trigger servo motion ~TRG:
                            ITRG, // Command to trigger servo motion with interrupt ~ITRG:
                            DEG,  // Command to read current Servo angle in ADC ~DEG#6:
                            ATC,  //Attach Servo ~ATC#6:
                            DTC,  //Detach Servo ~DTC#6:
                            LLK,  // Set Left Lock Servo Angle in PWM  ~LLK#6#PWM_VALUE:
                            RLK,  // Set Right Lock Servo Angle in PWM ~RLK#6#PWM_VALUE:
                            EAS,  //Set Servo Easing Func  ~EAS#6#SIN:
                            INO,  // Set SErvo Easing Type ~INO#6#IN:
                            PRX,  // read promity sensor.. Support sonly 9 address  ~PRX#9:
                            CELL1,//Read CELL1 value in ADC   ~CELL1:
                            CELL2,//Read CELL2 value in ADC   ~CELL2:
                            CELL3,//Read CELL3 value in ADC   ~CELL3:
                            SLEEP,
                            VEN,  //Set Voice LED Fade     ~VEN:
                            VNO,  //Stop Voice LED Fade    ~VNO:
                            CPW,  //Connect servo Power    ~ATC#6:
                            DPW,  //Disconnect servo power ~DTC#6:
                            LAT,  //Attach lock servos     ~LAT#9:
                            LDT,  //Detach lock servos     ~LDT#9:
                            LON,  //Power on lock servos   ~LON#9:
                            LOF,  //power off lock servos  ~LOF#9:
                            SMV,  //REad if servo is moving or not ~SMV#6:
                            SAT,  //REad if servo is attached or not ~SAT#6:
                            SPW,  //REad if servo is powered on or not ~SPW#6:
                            LSA,  //REad if lock servo attached or not ~LSA#6:
                            LPW,  //REad if lock servo is powered or not ~LPW#6:
                            FRQ,  //Sets the frequency of animation waveforms     ~FRQ#6#
                            DEL,  //Sets the delay before motor starts animation  ~DEL#6#[ms]:
                            DMP,  //range 1-10 sets the damping level of spring waveform motion   ~DMP#6#[1-10]:
                            VEL,  //range 1-5  set the velocity of spring waveform motion   ~VEL#6#[1-5]:
                            ISLR, //Reads Data from ISL94203 RAM Address
                            ISLW, //Writes Data to ISL94203 RAM Address
                            ISLER,//Reads Data from ISL94203 EEPROM Address
                            ISLEW,//Writes Data to ISL94203 EEPROM Address
                            EEPR, //Reads data from MAater Controller EEPROM
                            EEPW, //Writes Data to  MAster Controlelr EEPROM
                            POFF, //Request MAchine Power Off
                            SCAL,//Start  Servo Calibration loop ~SCAL#ServoAddress:
                            SEPR, //Read Servo EEPROM Data ~SEPR#ServoAddress#EEPROMAddress#NumberOfBytes:
                            UNKNOWN
                    };
                    const map<string, etype> stringtoenum{{"ANG", ANG}, {"TMG", TMG}, {"TRG", TRG}, {"ITRG", ITRG}, {"DEG", DEG}, {"ATC", ATC}, {"DTC", DTC}, {"LLK", LLK}, {"RLK", RLK},
                                                              {"EAS", EAS}, {"INO", INO}, {"PRX", PRX}, {"TRG", TRG}, {"CELL1", CELL1}, {"CELL2", CELL2}, {"CELL3", CELL3}, {"SLEEP", SLEEP}, 
                                                              {"VEN", VEN}, {"VNO", VNO}, {"CPW", CPW}, {"DPW", DPW}, {"LAT", LAT}, {"LDT", LDT}, {"LON", LON}, {"LOF", LOF}, {"SMV", SMV}, 
                                                              {"SAT", SAT}, {"SPW", SPW}, {"LSA", LSA}, {"LPW", LPW}, {"FRQ", FRQ}, {"DEL", DEL}, {"DMP", DMP}, {"VEL", VEL}, {"ISLR", ISLR}, 
                                                              {"ISLW", ISLW},{"ISLER", ISLER}, {"ISLEW", ISLEW}, {"EEPR", EEPR}, {"EEPW", EEPW}, {"POFF", POFF}, {"SCAL", SCAL}, {"SEPR", SEPR}, 
                                                              {"UNKNOWN", UNKNOWN}, 
                                                            };

                     const map<etype, string> enumtostring{{ANG, "ANG"}, {TMG, "TMG"}, {TRG, "TRG"}, {ITRG, "ITRG"}, {DEG, "DEG"}, {ATC, "ATC"}, {DTC, "DTC"}, {LLK, "LLK"}, {RLK, "RLK"},
                                                              {EAS, "EAS"}, {INO, "INO"}, {PRX, "PRX"}, {TRG, "TRG"}, {CELL1, "CELL1"}, {CELL2, "CELL2"}, {CELL3, "CELL3"}, {SLEEP, "SLEEP"}, 
                                                              {VEN, "VEN"}, {VNO, "VNO"}, {CPW, "CPW"}, {DPW, "DPW"}, {LAT, "LAT"}, {LDT, "LDT"}, {LON, "LON"}, {LOF, "LOF"}, {SMV, "SMV"}, 
                                                              {SAT, "SAT"}, {SPW, "SPW"}, {LSA, "LSA"}, {LPW, "LPW"}, {FRQ, "FRQ"}, {DEL, "DEL"}, {DMP, "DMP"}, {VEL, "VEL"}, {ISLR, "ISLR"}, 
                                                              {ISLW, "ISLW"},{ISLER, "ISLER"}, {ISLEW, "ISLEW"}, {EEPR, "EEPR"}, {EEPW, "EEPW"}, {POFF, "POFF"}, {SCAL, "SCAL"}, {SEPR, "SEPR"}, 
                                                              {UNKNOWN, "UNKNOWN"}, 
                                                            };

                        map<CommandTypes::etype, int> CommandResponseCount {
                        {CommandTypes::ANG,1},
                        {CommandTypes::TMG,1},
                        {CommandTypes::TRG,1},
                        {CommandTypes::ITRG,1},
                        {CommandTypes::DEG,2},
                        {CommandTypes::ATC,1},
                        {CommandTypes::DTC,1},
                        {CommandTypes::LLK,1},
                        {CommandTypes::RLK,1},
                        {CommandTypes::EAS,1},
                        {CommandTypes::INO,1},
                        {CommandTypes::PRX,2},
                        {CommandTypes::CELL1,2},
                        {CommandTypes::CELL2,2},
                        {CommandTypes::CELL3,2},
                        {CommandTypes::SLEEP,2},
                        {CommandTypes::VEN,1},
                        {CommandTypes::VNO,1},
                        {CommandTypes::CPW,1},
                        {CommandTypes::DPW,1},
                        {CommandTypes::LAT,1},
                        {CommandTypes::LDT,1},
                        {CommandTypes::LOF,1},
                        {CommandTypes::LON,1},
                        {CommandTypes::SMV,2},
                        {CommandTypes::SAT,2},
                        {CommandTypes::SPW,2},
                        {CommandTypes::LSA,2},
                        {CommandTypes::LPW,2},
                        {CommandTypes::FRQ,1},
                        {CommandTypes::DEL,1},
                        {CommandTypes::DMP,1},
                        {CommandTypes::VEL,1},
                        {CommandTypes::ISLR,2},
                        {CommandTypes::ISLW,2},
                        {CommandTypes::ISLER,2},
                        {CommandTypes::ISLEW,2},
                        {CommandTypes::EEPR,2},
                        {CommandTypes::EEPW,2},
                        {CommandTypes::POFF,1},
                        {CommandTypes::SCAL,1},
                        {CommandTypes::SEPR,2},
                        {CommandTypes::UNKNOWN,0}
                    };
                };

              class RemoteCommandTypes {
                    public:
                        enum etype{
                        PBTN,
                        VBTN
                        };
                      const map<string, etype> stringtoenum =  {{"PBTN", PBTN}, {"VBTN", VBTN}};
                      const map<etype, string> enumtostring = {{PBTN, "PBTN"}, {VBTN, "VBTN"}};
                };

               
          
    };
}