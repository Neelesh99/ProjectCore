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


typedef SymphonyNetwork* SYptr;
typedef SensorHandler* SHptr;
typedef Controller* CTptr;
typedef Communication* CMptr;
typedef CommunicationsBuffer* CBptr;

class StateMachine {
private:
    int current_state = 1;
    SYptr Symphonynetwork;
    SHptr Sensorhandler;
    CTptr Controls;
    CMptr Comms;
    CBptr Commsbuffer;
public:
    StateMachine(SYptr Symphony, SHptr Sensor, CTptr Control, CMptr Commun, CBptr CommsBuffer);

};


#endif //PROJECTCORE_STATEMACHINE_HPP
