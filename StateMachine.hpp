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
enum StringCommand{
    eINST,
    eEXEC,
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
    eFINI
};
class StateMachine {
private:
    int current_state = 1;
    SYptr Symphonynetwork;
    SHptr Sensorhandler;
    CTptr Controls;
    CMptr Comms;
    CBptr Commsbuffer;
    StringCommand CurrentCommand;
    StringInstruction CurrentInstruction;
    Fiptr Log;
    std::vector<std::string> ValidityMap;
public:
    StateMachine(SYptr Symphony, SHptr Sensor, CTptr Control, CBptr CommsBuffer, Fiptr Logfile, int &exception);
    bool StateChangeCall(std::string command, std::string instruction, std::string elaboration, int datano, std::vector<std::string> data);
    StringCommand StringToEnumCommand(std::string command);
    StringInstruction StringToEnumInstruction(std::string instruction);
    bool CheckStateChange();
    std::string pullValue(StringInstruction s, int stat);
    void LoadValidityMap(int &exception);
    int GetValidityMapIndex(StringInstruction s);
    int xytoi(int x, int y);
};


#endif //PROJECTCORE_STATEMACHINE_HPP
