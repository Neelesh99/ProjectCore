//
// Created by Neelesh on 29/01/2019.
//

#include "StateMachine.hpp"


StateMachine::StateMachine(SYptr Symphony, SHptr Sensor, CTptr Control,
                           CBptr CommsBuffer, Fiptr Logfile) {
    Symphonynetwork = Symphony;
    Sensorhandler = Sensor;
    Controls = Control;
    Commsbuffer = CommsBuffer;
    current_state = 1;
    Log = Logfile;
}
std::string StateMachine::pullValue(StringInstruction s, int stat, std::vector<std::string> store) {

}
bool StateMachine::CheckStateChange(int &exception){
    std::ifstream file("StateChangeMap.map");
    try{
        if(file.is_open()){
            std::vector<std::string> truthtable;
            std::string temp;
            while(file >> temp){
                truthtable.push_back(temp);
            }
            std::string booleanvalue = pullValue(CurrentInstruction,current_state,truthtable);
        }
        else{
            throw 7;
        }
    }
    catch(int &e){
        exception = e;
    }
}
bool StateMachine::StateChangeCall(std::string command, std::string instruction, std::string elaboration, int datano, std::vector<std::string> data){
    CurrentCommand = StringToEnumCommand(command);
    CurrentInstruction = StringToEnumInstruction(instruction);
    switch(CurrentCommand){
        case eEXEC:
            *Log << "Executive Command passed on state " << current_state << std::endl;
        case eINST:
            *Log << "Instruction Command passed on state " << current_state << std::endl;
    }
    switch(CurrentInstruction) {
        case eDBUG:
            *Log << "Debug instructional call passed on state " << current_state << std::endl;
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