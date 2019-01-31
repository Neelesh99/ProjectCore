//
// Created by Neelesh on 29/01/2019.
//

#ifndef PROJECTCORE_STATE_HPP
#define PROJECTCORE_STATE_HPP

#include <string>
#include <fstream>
typedef std::ofstream* Fiptr;
class State {
protected:
    int s;
    std::string PythonDisplayScript;
    bool active = false;
    Fiptr Logfile;
    std::string LogMessage;
public:
    State(Fiptr Log);
    void activateState();
    bool getStatus();
    void Refresh();
    void deactivateState();
};
class Debug_000 : public State{
public:
    Debug_000(Fiptr LOG);
};
class ShutOff_001 : public State{
public:
    ShutOff_001(Fiptr LOG);
};
class Boot_002 : public State{
public:
    Boot_002(Fiptr LOG);
};
class BtWait_003: public State{
public:
    BtWait_003(Fiptr LOG);
};
class Clock_004: public State{
private:
    std::string Elaboration;
public:
    Clock_004(Fiptr LOG);
    void activateState(std::string elaboration);
    void Refresh();
};
class ReNav_005: public State{
private:
    std::string Elaboration;
public:
    ReNav_005(Fiptr LOG);
    void activateState(std::string elaboration);
    void Refresh();
};
class GeNav_006: public State{
private:
    std::string streetname;
    std::string distance;
    std::string nextturn;
    std::string nextstreet;
public:
    GeNav_006(Fiptr LOG);
    void activateState(std::string Streetname, std::string Distance, std::string NextTurn, std::string NextStreet);
    void Refresh();
};
class Turn_007: public State{
private:
    std::string direction;
    std::string streetname;
public:
    Turn_007(Fiptr LOG);
    void activateState(std::string Direction, std::string Streetname);
    void Refresh();
};
class Arrived_008: public State{
private:
    std::string streetname;
public:
    Arrived_008(Fiptr LOG);
    void activateState(std::string Streetname);
    void Refresh();
};
class FallDetect_009: public State{
public:
    FallDetect_009(Fiptr LOG);
};
class Blind_010: public State{
public:
    Blind_010(Fiptr LOG);
};
#endif //PROJECTCORE_STATE_HPP
