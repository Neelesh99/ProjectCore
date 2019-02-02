//
// Created by Neelesh on 01/02/2019.
//

#ifndef PROJECTCORE_INSTRUCTOR_HPP
#define PROJECTCORE_INSTRUCTOR_HPP

#include <iostream>
#include "SymphonyNetwork.hpp"
#include "SensorHandler.hpp"
#include "Controller.hpp"
#include "Communication.hpp"
#include "CommuncationsBuffer.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include <cstring>

typedef SymphonyNetwork* SYptr;
typedef SensorHandler* SHptr;
typedef Controller* CTptr;
typedef Communication* CMptr;
typedef CommunicationsBuffer* CBptr;
typedef std::ofstream* Fiptr;
typedef StateMachine* SMptr;

class Instructor {
private:
    int noofdata;
    Fiptr Logfile;
    CBptr commsbuffer;
    SMptr statemachine;
    int &except;
    std::string UnformattedCommand;
    std::string UnformattedInstruction;
    std::string UnformattedElaboration;
    std::string UnformattedData;
    std::string FormattedCommand;
    std::string FormattedInstruction;
    std::string FormattedElaboration;
    int NoofDataWords;
    std::vector<std::string> FormattedData;
public:
    Instructor(Fiptr Log, CBptr CommsBuffer, SMptr Statemachine, int &exception);
    Instructor(Fiptr Log, CBptr CommsBuffer, int &exception);
    bool PollCommsBuffer();
    void FormatCommunication();
    void RefreshInstructionSM();
    void SendInstructionToSM();
};


#endif //PROJECTCORE_INSTRUCTOR_HPP
