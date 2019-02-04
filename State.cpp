//
// Created by Neelesh on 29/01/2019.
//

#include "State.hpp"
#include <iostream>
State::State(Fiptr Log){
    Logfile = Log;
    PythonDisplayScript = "DefaultDisplay.py";
    std::cout << "State Inititialisation Call" << std::endl;
    LogMessage = "State111";
}
void State::activateState(){
    active = true;
    *Logfile << LogMessage << " Activated" << std::endl;
    //std::cout << "State activation call" << std::endl;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript)).c_str());
}
bool State::getStatus() {
    return active;
}
void State::deactivateState() {
    active = false;
    *Logfile << LogMessage << " Deactivated" << std::endl;
}
void State::Refresh() {
    std::cout << "Incorrect Refresh Called" << std::endl;
    *Logfile << LogMessage << " Refreshed" << std::endl;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript)).c_str());
}
Debug_000::Debug_000(Fiptr LOG) : State(LOG){
    PythonDisplayScript = "DefaultDisplay.py";
    LogMessage = "State000";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
ShutOff_001::ShutOff_001(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "ShutOff001.py";
    LogMessage = "State001";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
Boot_002::Boot_002(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "Boot002.py";
    LogMessage = "State002";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
BtWait_003::BtWait_003(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "BluetoothWait003.py";
    LogMessage = "State003";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
Clock_004::Clock_004(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "ClockScreen004.py";
    LogMessage = "State004";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
void Clock_004::activateState(std::string elaboration) {
    active = true;
    *Logfile << LogMessage << " Activated" << std::endl;
    Elaboration = elaboration;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + Elaboration)).c_str());
}
void Clock_004::Refresh() {
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + Elaboration)).c_str());
}
ReNav_005::ReNav_005(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "RecieveNavigation005.py";
    LogMessage = "State005";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
void ReNav_005::activateState(std::string elaboration) {
    active = true;
    *Logfile << LogMessage << " Activated" << std::endl;
    Elaboration = elaboration;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + Elaboration)).c_str());
}
void ReNav_005::Refresh() {
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + Elaboration)).c_str());
}
GeNav_006::GeNav_006(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "GeneralNavigation006.py";
    LogMessage = "State006";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
void GeNav_006::activateState(std::string Streetname, std::string Distance, std::string NextTurn,
                              std::string NextStreet) {
    active = true;
    *Logfile << LogMessage << " Activated" << std::endl;
    streetname = Streetname;
    distance = Distance;
    nextstreet = NextStreet;
    nextturn = NextTurn;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + streetname + " " + distance + " " + nextturn + " " + nextstreet)).c_str());
}
void GeNav_006::Refresh() {
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + streetname + " " + distance + " " + nextturn + " " + nextstreet)).c_str());
}
Turn_007::Turn_007(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "TurnScreen007.py";
    LogMessage = "State007";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
void Turn_007::activateState(std::string Direction, std::string Streetname) {
    active = true;
    *Logfile << LogMessage << " Activated" << std::endl;
    direction = Direction;
    streetname = Streetname;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + direction + " " + streetname)).c_str());
}
void Turn_007::Refresh() {
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " + direction + " " + streetname)).c_str());
}
Arrived_008::Arrived_008(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "ArriverScreen008.py";
    LogMessage = "State008";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
void Arrived_008::activateState(std::string Streetname) {
    active = true;
    *Logfile << LogMessage << " Activated" << std::endl;
    streetname = Streetname;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " +  streetname)).c_str());
}
void Arrived_008::Refresh() {
    //std::cout << "Streetname Debug: " <<  streetname << std::endl;
    system((("python PythonDisplayFiles\\" + PythonDisplayScript + " " +  streetname)).c_str());
}
FallDetect_009::FallDetect_009(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "FallDetection009.py";
    LogMessage = "State009";
    *Logfile << LogMessage << " is initialised" << std::endl;
}
Blind_010::Blind_010(Fiptr LOG):State(LOG) {
    PythonDisplayScript = "BlindSpotDetection.py";
    LogMessage = "State010";
    *Logfile << LogMessage << " is initialised" << std::endl;
}