//
// Created by Neelesh on 29/01/2019.
//

#include "StateMachine.hpp"

StateMachine::StateMachine( SYptr Symphony, SHptr Sensor, CTptr Control, CMptr Commun,
                           CBptr CommsBuffer) {

    Symphonynetwork = Symphony;
    Sensorhandler = Sensor;
    Controls = Control;
    Comms = Commun;
    Commsbuffer = CommsBuffer;
    current_state = 2;
}
