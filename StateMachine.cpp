//
// Created by Neelesh on 29/01/2019.
//

#include "StateMachine.hpp"


StateMachine::StateMachine(SYptr Symphony,
                           CBptr CommsBuffer, Fiptr Logfile, int &exception) {
    Symphonynetwork = Symphony;
    //Sensorhandler = Sensor;
    //Controls = Control;
    Commsbuffer = CommsBuffer;
    current_state = 1;
    Log = Logfile;
    LoadValidityMap(exception);
    shutdown = new ShutOff_001(Logfile);
    boot = new Boot_002(Logfile);
    btwait = new BtWait_003(Logfile);
    clockscreen = new Clock_004(Logfile);
    recieve_navigation = new ReNav_005(Logfile);
    general_navigation = new GeNav_006(Logfile);
    turn_screen = new Turn_007(Logfile);
    arrival_screen = new Arrived_008(Logfile);
    fall_detection = new FallDetect_009(Logfile);
    blind_spot = new Blind_010(Logfile);
    debug_screen = new Debug_000(Logfile);
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
    else{
        return -1;
    }
}
int StateMachine::xytoi(int x, int y) {
    x++;
    y++;
    return (y*15 + x);
}
std::string StateMachine::pullValue(StringInstruction s, int stat) {
    int index_x = GetValidityMapIndex(s);
    int index_y = stat;
    int index_i = xytoi(index_x,index_y);
    //index_i++;
    std::cout << index_i << std::endl;
    std::cout << ValidityMap[index_i] << std::endl;
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
//Abhiram was here :)
bool StateMachine::StateChangeCall(std::string* command, std::string* instruction, std::string elaboration,int NoOfData, std::vector<std::string> data){
    refresh_count = 0;
    CurrentCommand = StringToEnumCommand(*command);
    CurrentInstruction = StringToEnumInstruction(*instruction);
    bool valid = false;
    switch(CurrentCommand){
        case eEXEC:
            *Log << "Executive Command passed on state " << current_state << std::endl;
            break;
        case eINST:
            *Log << "Instruction Command passed on state " << current_state << std::endl;
            break;
        default:
            *Log << "Invalid Command passed on state " << current_state << std::endl;
            break;
    }
    switch(CurrentInstruction) {
        case eDBUG:
            *Log << "Debug instructional call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Debug instruction validated by executive command tree, calling Debug State" << std::endl;
                    Current_State = debug_screen;
                    current_state = 0;
                    if(!(debug_screen->getStatus())) {
                        debug_screen->activateState();
                    }
                    else{
                        debug_screen->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Debug instruction passed on Non-Exectuive command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eRSET:
            *Log << "Reset instructional call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Reset instruction validated by executive command tree, calling Boot state" << std::endl;
                    Current_State = boot;
                    current_state = 2;
                    if(!(boot->getStatus())){
                        boot->activateState();
                    }
                    else{
                        boot->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Debug instruction passed on Non-executive command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eBATR:
            *Log << "Low Battery instructional call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Low battery instruction validated by exectuive command tree, calling shut down state" << std::endl;
                    Current_State = shutdown;
                    current_state = 1;
                    if(!(shutdown->getStatus())){
                        shutdown->activateState();
                    }
                    else{
                        shutdown->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Low battery passed on Non-executive command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eBTDC:
            *Log << "Bluetooth Link lost instructional call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Bluetooth Disconnect instruction validated by executive command tree, calling bluetooth wait screen" << std::endl;
                    Current_State = btwait;
                    current_state = 3;
                    if(!(btwait->getStatus())){
                        btwait->activateState();
                    }
                    else{
                        btwait->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "BT link lost instruction passed on Non-executive command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eFALL:
            *Log << "Fall detection call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Fall detection instruction validated by executive command tree, calling fall detection screen" << std::endl;
                    Current_State = fall_detection;
                    current_state = 9;
                    if(!(fall_detection->getStatus())){
                        fall_detection->activateState();
                    }
                    else{
                        fall_detection->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Fall Detection instruction passed on Non-executive command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eBLND:
            *Log << "Blind Spot detection call passed on state " << current_state << std::endl;
            if(CurrentCommand == eEXEC){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Blind Spot detection instruction validated by executive command tree, calling blind detection screen" << std::endl;
                    Current_State = blind_spot;
                    current_state = 10;
                    if(!(blind_spot->getStatus())){
                        blind_spot->activateState();
                    }
                    else{
                        blind_spot->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Blind Spot detection instruction passed on Non-executive command tree, instruction ignored" << std::endl;
            }
            return valid;
        case ePWRN:
            *Log << "Power on call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Power on instruction validated by Instructional command tree, calling boot screen" << std::endl;
                    Current_State = boot;
                    current_state = 2;
                    if(!(boot->getStatus())){
                        boot->activateState();
                    }
                    else{
                        boot->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Power on call passed on non-instructional command tree" << std::endl;
            }
            return valid;
        case eBTWT:
            *Log << "Bluetooth Wait call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Bluetooth wait call validated by Instructional command tree, calling Bluetooth wait screen" << std::endl;
                    Current_State = btwait;
                    current_state = 3;
                    if(!(btwait->getStatus())){
                        btwait->activateState();
                    }
                    else{
                        btwait->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Bluetooth wait call passed on non-instructional command tree" << std::endl;
            }
            return valid;
        case eCLKS:
            *Log << "Go to Clock call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Clock screen call validated by Instructional command tree, calling Clock screen" << std::endl;
                    Current_State = clockscreen;
                    current_state = 4;
                    if(!(clockscreen->getStatus())){
                        clockscreen->activateState(elaboration);
                    }
                    else{
                        clockscreen->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Clock screen call passed on nin-instrucitonal command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eBTRC:
            *Log << "Recieve Bluetooth call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Bluetooth recieve instruction validated by the Instructional command tree, calling bt recieve screen" << std::endl;
                    Current_State = recieve_navigation;
                    current_state = 5;
                    if(!(recieve_navigation->getStatus())){
                        recieve_navigation->activateState(elaboration);
                    }
                    else{
                        recieve_navigation->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Bluetooth recieve instruction called on non-instructional command chain, instruction ignored" << std::endl;
            }
            return valid;
        case eSTNV:
            *Log << "Start Navigation call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Start navigation command validated by instructional command tree, calling General Navigation screen" << std::endl;
                    Current_State = general_navigation;
                    current_state = 6;
                    if(!(general_navigation->getStatus())){
                        general_navigation->activateState(data[0],data[1],data[2],data[3]);
                    }
                    else{
                        general_navigation->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Start navigation instruction called on non-instructional command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eTURN:
            *Log << "Turn screen call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Turn screen instruction validated by instructional command tree, calling turn screen" << std::endl;
                    Current_State = turn_screen;
                    current_state = 7;
                    if(!(turn_screen->getStatus())){
                        turn_screen->activateState(data[0],data[1]);
                    }
                    else{
                        turn_screen->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Turn screen instruction called on non-instructional command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eREGE:
            *Log << "Switch from turn screen to general screen call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST){
                valid = CheckStateChange();
                if(valid){
                    *Log << "Rejoin General navigation instruction validated by instructional command tree, calling general navigation screen" << std::endl;
                    Current_State = general_navigation;
                    current_state = 6;
                    if(!(general_navigation->getStatus())){
                        general_navigation->activateState(data[0],data[1],data[2],data[3]);
                    }
                    else{
                        general_navigation->Refresh();
                    }
                }
                else{
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Rejoin general navigation instruction called on non-instructional command tree, instruction ignored" << std::endl;
            }
            return valid;
        case eFINI:
            *Log << "Go to emd screen call passed on state " << current_state << std::endl;
            if(CurrentCommand == eINST) {
                valid = CheckStateChange();
                if (valid) {
                    *Log
                            << "Finish Navigation instruction validated by instructional command tree, calling Finish Screen"
                            << std::endl;
                    Current_State = arrival_screen;
                    current_state = 8;
                    if (!(arrival_screen->getStatus())) {
                        arrival_screen->activateState(data[0]);
                    } else {
                        arrival_screen->Refresh();
                    }
                } else {
                    *Log << "Invalid State change called, instruction was ignored" << std::endl;
                }
            }
            else{
                *Log << "Finish screen instruction called on non instructional command tree, instruction ignored" << std::endl;
            }
            return valid;
        default:
            return valid;

    }
}
StringCommand StateMachine::StringToEnumCommand(std::string command) {
    if(command == "EXEC"){return eEXEC;}
    if(command == "INST"){
        return eINST;}
    else{
        return eVOID2;
    }
}
//Maybe you should add more comments. Cos this looks confusing.
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
    else{
        return eVOID;
    }
}
void StateMachine::StateRefreshCall() {
    Current_State->Refresh();
    *Log << "Refresh on state " << current_state << std::endl;
    refresh_count++;
}
StateMachine::~StateMachine() {
    delete shutdown;
    delete boot;
    delete btwait;
    delete clockscreen;
    delete recieve_navigation;
    delete general_navigation;
    delete turn_screen;
    delete arrival_screen;
    delete fall_detection;
    delete blind_spot;
    delete debug_screen;
}