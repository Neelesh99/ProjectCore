//
// Created by Neelesh on 29/01/2019.
//

#include "StateMachine.hpp"


StateMachine::StateMachine(SYptr Symphony, SHptr Sensor, CTptr Control,
                           CBptr CommsBuffer, Fiptr Logfile, int &exception) {
    Symphonynetwork = Symphony;
    Sensorhandler = Sensor;
    Controls = Control;
    Commsbuffer = CommsBuffer;
    current_state = 1;
    Log = Logfile;
    LoadValidityMap(exception);
    ShutOff_001 shutdown(Logfile);
    Boot_002 boot(Logfile);
    BtWait_003 btwait(Logfile);
    Clock_004 clockscreen(Logfile);
    ReNav_005 recieve_navigation(Logfile);
    GeNav_006 general_navigation(Logfile);
    Turn_007 turn_screen(Logfile);
    Arrived_008 arrival_screen(Logfile);
    FallDetect_009 fall_detection(Logfile);
    Blind_010 blind_spot(Logfile);
    Debug_000 debug_screen(Logfile);
}
int StateMachine::GetValidityMapIndex(StringInstruction s) {
    if(s == eDBUG){
        return 0;
    }
    if(s == eRSET){
        return 1;
    }
    if(s == eBATR){
        return 2;
    }
    if(s == eBTDC){
        return 3;
    }
    if(s == eFALL){
        return 4;
    }
    if(s == eBLND){
        return 5;
    }
    if(s == ePWRN){
        return 6;
    }
    if(s == eBTWT){
        return 7;
    }
    if(s == eCLKS){
        return 8;
    }
    if(s == eBTRC){
        return 9;
    }
    if(s == eSTNV){
        return 10;
    }
    if(s == eTURN){
        return 11;
    }
    if(s == eREGE){
        return 12;
    }
    if(s == eFINI){
        return 13;
    }
}
int StateMachine::xytoi(int x, int y) {
    x++;
    y++;
    return (y*14 + x);
}
std::string StateMachine::pullValue(StringInstruction s, int stat) {
    int index_x = GetValidityMapIndex(s);
    int index_y = stat;
    int index_i = xytoi(index_x,index_y);
    return ValidityMap[index_i];
}
void StateMachine::LoadValidityMap(int &exception) {
    std::ifstream file("StateChangeMap.map");
    try{
        if(file.is_open()){
            std::vector<std::string> truthtable;
            std::string temp;
            while(file >> temp){
                truthtable.push_back(temp);
            }
            ValidityMap = truthtable;
        }
        else{
            throw 7;
        }
    }
    catch(int &e){
        exception = e;
    }

}
bool StateMachine::CheckStateChange(){
    return (pullValue(CurrentInstruction, current_state) == "true");
}
bool StateMachine::StateChangeCall(std::string command, std::string instruction, std::string elaboration, int datano, std::vector<std::string> data){
    CurrentCommand = StringToEnumCommand(command);
    CurrentInstruction = StringToEnumInstruction(instruction);
    bool valid = false;
    switch(CurrentCommand){
        case eEXEC:
            *Log << "Executive Command passed on state " << current_state << std::endl;
        case eINST:
            *Log << "Instruction Command passed on state " << current_state << std::endl;
    }
    switch(CurrentInstruction) {
        case eDBUG:
            *Log << "Debug instructional call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Debug instruciton validated by executive command tree, calling Debug State" << std::endl;
                }
            }
            else{
                *Log << "Debug instruction passed on Non-Exectuive command tree, instruction ignored" << std::endl;
            }
        case eRSET:
            *Log << "Reset instructional call passed on state " << current_state << std::endl;
        case eBATR:
            *Log << "Low Battery instructional call passed on state " << current_state << std::endl;
        case eBTDC:
            *Log << "Bluetooth Link lost instructional call passed on state " << current_state << std::endl;
        case eFALL:
            *Log << "Fall detection call passed on state " << current_state << std::endl;
        case eBLND:
            *Log << "Blind Spot detection call passed on state " << current_state << std::endl;
        case ePWRN:
            *Log << "Power on call passed on state " << current_state << std::endl;
        case eBTWT:
            *Log << "Bluetooth Wait call passed on state " << current_state << std::endl;
        case eCLKS:
            *Log << "Go to Clock call passed on state " << current_state << std::endl;
        case eBTRC:
            *Log << "Recieve Blurtooth call passed on state " << current_state << std::endl;
        case eSTNV:
            *Log << "Start Navigation call passed on state " << current_state << std::endl;
        case eTURN:
            *Log << "Turn screen call passed on state " << current_state << std::endl;
        case eREGE:
            *Log << "Switch from turn screen to general screen call passed on state " << current_state << std::endl;
        case eFINI:
            *Log << "Go to emd screen call passed on state " << current_state << std::endl;
    }

}
StringCommand StateMachine::StringToEnumCommand(std::string command) {
    if(command == "EXEC"){return eEXEC;}
    if(command == "INST"){return eINST;}
}
StringInstruction StateMachine::StringToEnumInstruction(std::string instruction) {
    if(instruction == "DBUG"){return eDBUG;}
    if(instruction == "RSET"){return eRSET;}
    if(instruction == "BATR"){return eBATR;}
    if(instruction == "BTDC"){return eBTDC;}
    if(instruction == "FALL"){return eFALL;}
    if(instruction == "BLND"){return eBLND;}
    if(instruction == "PWRN"){return ePWRN;}
    if(instruction == "BTWT"){return eBTWT;}
    if(instruction == "CLKS"){return eCLKS;}
    if(instruction == "BTRC"){return eBTRC;}
    if(instruction == "STNV"){return eSTNV;}
    if(instruction == "TURN"){return eTURN;}
    if(instruction == "REGE"){return eREGE;}
    if(instruction == "FINI"){return eFINI;}
}