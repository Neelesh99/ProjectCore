//
// Created by Neelesh on 29/01/2019.
//

#ifndef PROJECTCORE_STATEMACHINE_HPP
#define PROJECTCORE_STATEMACHINE_HPP

#include <iostream>


#include "SymphonyNetwork.hpp"
#include "SensorHandler.hpp"
#include "Controller.hpp"
#include "Communication.hpp"
#include "CommuncationsBuffer.hpp"
#include "State.hpp"


typedef SymphonyNetwork* SYptr;
typedef SensorHandler* SHptr;
typedef Controller* CTptr;
typedef Communication* CMptr;
typedef CommunicationsBuffer* CBptr;
typedef std::ofstream* Fiptr;
typedef char* cptr;
enum StringCommand{
    eINST,
    eEXEC,
    eVOID2
};
enum StringInstruction{
    eDBUG,
    eRSET,
    eBATR,
    eBTDC,
    eFALL,
    eBLND,
    ePWRN,
    eBTWT,
    eCLKS,
    eBTRC,
    eSTNV,
    eTURN,
    eREGE,
    eFINI,
    eVOID
};
class StateMachine {
private:
    int refresh_count = 0;
    int current_state = 1;
    State* Current_State;
    SYptr Symphonynetwork;
    SHptr Sensorhandler;
    CTptr Controls;
    CMptr Comms;
    CBptr Commsbuffer;
    StringCommand CurrentCommand;
    StringInstruction CurrentInstruction;
    Fiptr Log;
    std::vector<std::string> ValidityMap;
    ShutOff_001* shutdown;
    Boot_002* boot;
    BtWait_003* btwait;
    Clock_004* clockscreen;
    ReNav_005* recieve_navigation;
    GeNav_006* general_navigation;
    Turn_007* turn_screen;
    Arrived_008* arrival_screen;
    FallDetect_009* fall_detection;
    Blind_010* blind_spot;
    Debug_000* debug_screen;
public:
    StateMachine(SYptr Symphony, CBptr CommsBuffer, Fiptr Logfile, int &exception);
    bool StateChangeCall(std::string* command, std::string* instruction, std::string elaboration,int NoOfData, std::vector<std::string> data);
    StringCommand StringToEnumCommand(std::string command);
    StringInstruction StringToEnumInstruction(std::string instruction);
    bool CheckStateChange();
    std::string pullValue(StringInstruction s, int stat);
    void LoadValidityMap(int &exception);
    int GetValidityMapIndex(StringInstruction s);
    int xytoi(int x, int y);
    void StateRefreshCall();
    void DeactivateCurrent();
    ~StateMachine();
};


#endif //PROJECTCORE_STATEMACHINE_HPP
