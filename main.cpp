#include <iostream>
#include "SymphonyNetwork.hpp"
#include <vector>
#include <fstream>
#include <thread>
#include "CommuncationsBuffer.hpp"
#include "Communication.hpp"
#include "State.hpp"
#include <chrono>
#include <ctime>
#include "Instructor.hpp"
typedef std::vector<int>* viptr;
typedef SymphonyNetwork* Syptr;
typedef std::string* Stptr;
typedef CommunicationsBuffer* Cbptr;
typedef std::ofstream* Fiptr;

Fiptr StartLogFile(int &exception);

class MachineLearningCore{
private:
    int s;
    int Fall_Input_Nodes;
    int Fall_Interlayer_Count;
    std::vector<int> Fall_Interlayer_Nodes;
    viptr Fall_Interlayer;
    int Fall_Output_Nodes;
    int Blind_Input_Nodes;
    int Blind_Interlayer_Count;
    std::vector<int> Blind_Interlayer_Nodes;
    viptr Blind_Interlayer;
    int Blind_Output_Nodes;
    std::string WeightingFall;
    std::string WeightingBlindSpot;
    Syptr FallDetectionNetwork;
    Syptr BlindSpotNetwork;
public:
    MachineLearningCore(Stptr ConfigFileFallDetection, Stptr ConfigFileBlindSpotDetection, Stptr WeightingFallDetection, Stptr WeightingBlindSpotDetection, int &exception){
        try {
            exception = 0;
            std::ifstream FallConfig(*ConfigFileFallDetection);
            std::ifstream BlindConfig(*ConfigFileBlindSpotDetection);
            WeightingFall = *WeightingFallDetection;
            WeightingBlindSpot = *WeightingBlindSpotDetection;
            if (!is_empty(FallConfig)) {
                FallConfig >> Fall_Input_Nodes;
                FallConfig >> Fall_Interlayer_Count;
                for (int i = 0; i < Fall_Interlayer_Count; i++) {
                    int temp;
                    FallConfig >> temp;
                    Fall_Interlayer_Nodes.push_back(temp);
                }
                FallConfig >> Fall_Output_Nodes;
                Fall_Interlayer = &Fall_Interlayer_Nodes;
                FallConfig.close();
                std::cout << "Fall Detection Network Loaded and ready to initialise" << std::endl;
            }
            else {
                std::cout << "Fall Config File is Empty, fatal error, exception thrown" << std::endl;
                throw 4;
            }

            if (!is_empty(BlindConfig)) {
                BlindConfig >> Blind_Input_Nodes;
                BlindConfig >> Blind_Interlayer_Count;
                for (int i = 0; i < Blind_Interlayer_Count; i++) {
                    int temp;
                    BlindConfig >> temp;
                    Blind_Interlayer_Nodes.push_back(temp);
                }
                BlindConfig >> Blind_Output_Nodes;
                Blind_Interlayer = &Blind_Interlayer_Nodes;
                BlindConfig.close();
                std::cout << "Blind Spot detection Network Loaded and ready to initialise" << std::endl;
            } else {
                std::cout << "Blind Spot Config File is Empty, fatal error, exception thrown" << std::endl;
                throw 5;
            }
        }
        catch(int &e){
            exception = e;
        }
    }
    void Initialise_Fall_Detection(){
        auto FP = new SymphonyNetwork(Fall_Input_Nodes,Fall_Interlayer_Count,Fall_Interlayer,Fall_Output_Nodes);
        std::ifstream FallFile(WeightingFall);
        if(FallFile.is_open()){
            FP -> readFromFile(WeightingFall);
        }
        else{
            std::cout << "Settings File not found, initialising new network" << std::endl;
        }
        FallFile.close();
        FP -> Set_Eta(7);
        FP -> Set_Mu(0.05);
        std::cout << "Fall Detection Network Fully Initialised and ready to Run" << std::endl;
        FallDetectionNetwork = FP;
        //return FP;
    }
    std::thread Init_Fall_thread(){
        return std::thread(&MachineLearningCore::Initialise_Fall_Detection,this);
    }
    Syptr getFallPointer(){
        return FallDetectionNetwork;
    }
    void Initialise_Blind_Spot_Detection(){
        auto BP = new SymphonyNetwork(Blind_Input_Nodes,Blind_Interlayer_Count,Blind_Interlayer,Blind_Output_Nodes);
        std::ifstream BlindFile(WeightingBlindSpot);
        if(BlindFile.is_open()){
            BP->readFromFile(WeightingBlindSpot);
        }
        else{
            std::cout << "Settings File not found, initialising new network" << std::endl;
        }
        BlindFile.close();
        BP->Set_Eta(7);
        BP->Set_Mu(0.05);
        std::cout << "Blind Spot Detection Network Fully Initialised and ready to Run" << std::endl;
        BlindSpotNetwork = BP;
        //return BP;
    }
    std::thread Init_Blind_Thread(){
        return std::thread(&MachineLearningCore::Initialise_Blind_Spot_Detection,this);
    }
    Syptr getBlindPointer(){
        return BlindSpotNetwork;
    }
    bool is_empty(std::ifstream& pFile)
    {
        return pFile.peek() == std::ifstream::traits_type::eof();
    }
};
class CommunicationCore{
private:
    int s;
    Cbptr CommunicationBuffer;
public:
    CommunicationCore(){
        CommunicationBuffer = new CommunicationsBuffer();
        s = 0;
    }
    ~CommunicationCore(){
        delete CommunicationBuffer;
    }
    const Cbptr getCommsBuffer(){
        return CommunicationBuffer;
    }
};
class ExceptionHandler{
public:
    explicit ExceptionHandler(int exception){
        switch(exception){
            case 4:
                std::cout << "Program exiting due to fatal error in Fall detection Config File Reading: \nCheck if file exists, and that it is in correct format" << std::endl;
            case 5:
                std::cout << "Program exiting due to fatal error in Blind Spot detection Config File Reading: \nCheck if file exists, and that it is in correct format" << std::endl;
            case 6:
                std::cout << "Program Exiting due to fatal error in Logfile: \nCheck if the file exists and is in the correct format" << std::endl;
            default:
                std::cout << "Unhandled Exception caused fatal error in program: \nCheck Log file if in Debug Mode" << std::endl;
        }

    }
};
class TimeClass{
private:
    int s;
public:
    explicit TimeClass(int ds){
        s =ds;
    }
    std::string getTime(){
        auto start = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(start);
        return (std::ctime(&end_time));
    }
};

int main() {
    int exceptions = 0;
    Fiptr Logging;
    Logging = StartLogFile(exceptions);

    if(exceptions != 0){
        ExceptionHandler E(exceptions);
        return 1;
    }

    /// Neural Network INitialisationa nd savefile testing /// Passed ///
    /*
   std::string f = "FallDetectCOnfig.scfg";
   std::string ff = "BlindDetectConfig.scfg";
   std::string g = "FallWeight.scfg";
   std::string gg = "BlindWeight.scfg";
   int exception;
   Stptr fptr = &f;
   Stptr ffptr = &ff;
   Stptr gptr = &g;
   Stptr ggptr = &gg;
   MachineLearningCore m(fptr,ffptr,gptr,ggptr,exception);
   if(exception != 0){
       ExceptionHandler e(exception);
       return 1;
   }
   Syptr Blptr;
   Syptr Faptr;
   std::thread tw1 = m.Init_Fall_thread();
   std::thread tw2 = m.Init_Blind_Thread();
   tw1.join();
   tw2.join();
   Faptr = m.getFallPointer();
   Faptr->printData();
   Blptr = m.getBlindPointer();
   Blptr->printData();


   Syptr Blptr;
   Blptr = m.Initialise_Blind_Spot_Detection();
   Syptr FAptr;
   FAptr = m.Initialise_Fall_Detection();
   Blptr -> printToFile(g);
   FAptr -> printToFile(gg);
   delete Blptr;
   delete FAptr;
    */

    ///State python calls testing /// Passed ///
    /*
    State s(Logging);
    s.activateState();
    s.Refresh();
     */
    ///LOGFILE Testing ///
    ///
    ///Commsbuffer and Instructor All up testing ///
    /*
    auto Com = new CommunicationsBuffer();
    std::cout << Com->getLatestCommand() << std::endl;
    std::cout << Com->getLatestInstruction() << std::endl;
    std::cout << Com->getLatestElaboration() << std::endl;
    std::cout << Com->getLatestData() << std::endl;
    std::cout << Com->isEmpty() << std::endl;
    Instructor Inst(Logging,Com,exceptions);
    Inst.PollCommsBuffer();
    Inst.FormatCommunication();
    Com->releaseLatestCommunication();
    std::cout << "Is the comms buffer empty: " << Com->isEmpty() << std::endl;
    std::string coms = "cccEXECccc";
    std::string inst = "sssFALLsss";
    std::string elaboration = "eeeNONEeee";
    std::string data = "ddd3d07443570659dCALLdHYPHENddd";
    cptr cmmd = new char[coms.length()+1];
    cptr instr = new char[inst.length()+1];
    cptr elabs = new char[elaboration.length()+1];
    cptr dd = new char[data.length()+1];
    std::strcpy(cmmd,coms.c_str());
    std::strcpy(instr,inst.c_str());
    std::strcpy(elabs,elaboration.c_str());
    std::strcpy(dd,data.c_str());
    Com->Debugging_Manual_Poll(cmmd,instr,elabs,dd);
    std::cout << Com->getLatestCommand() << std::endl;
    std::cout << Com->getLatestInstruction() << std::endl;
    std::cout << Com->getLatestElaboration() << std::endl;
    std::cout << Com->getLatestData() << std::endl;
    std::cout << Com->isEmpty() << std::endl;
    Inst.PollCommsBuffer();
    Inst.FormatCommunication();
    Com->releaseLatestCommunication();
    std::cout << "Is the comms buffer empty: " << Com->isEmpty() << std::endl;
    std::string coms2 = "cccINSTccc";
    std::string inst2 = "sssREGEsss";
    std::string elaboration2 = "N/A";
    std::string data2 = "ddd3dORMANDS_STREETd57dCAPITOL_WAYddd";
    cptr cmmd2 = new char[coms.length()+1];
    cptr instr2 = new char[inst.length()+1];
    cptr elabs2 = new char[elaboration.length()+1];
    cptr dd2 = new char[data.length()+1];
    std::strcpy(cmmd2,coms2.c_str());
    std::strcpy(instr2,inst2.c_str());
    std::strcpy(elabs2,elaboration2.c_str());
    std::strcpy(dd2,data2.c_str());
    Com->Debugging_Manual_Poll(cmmd2,instr2,elabs2,dd2);
    std::cout << Com->getLatestCommand() << std::endl;
    std::cout << Com->getLatestInstruction() << std::endl;
    std::cout << Com->getLatestElaboration() << std::endl;
    std::cout << Com->getLatestData() << std::endl;
    std::cout << Com->isEmpty() << std::endl;
    Inst.PollCommsBuffer();
    Inst.FormatCommunication();
    delete Com;
    */
    ///New ALL Up test ///
    CommunicationCore s;
    Cbptr Com = s.getCommsBuffer();
    std::string FallDetectConfig = "FallDetectCOnfig.scfg";
    std::string FallWeight = "FallWeight.scfg";
    std::string BlindDetectConfig = "BlindDetectConfig.scfg";
    std::string BlindWeight = "BlindWeight.scfg";
    MachineLearningCore m(&FallDetectConfig,&BlindDetectConfig,&FallWeight,&BlindWeight,exceptions);
    auto stat = new StateMachine(m.getBlindPointer(),Com,Logging,exceptions);
    if(exceptions != 0){
        ExceptionHandler e(exceptions);
        return 1;
    }
    Instructor I(Logging,Com,stat,exceptions);
    if(I.PollCommsBuffer()){
        I.FormatCommunication();
        I.SendInstructionToSM();
        Com->releaseLatestCommunication();
    }
    std::string coms = "cccEXECccc";
    std::string inst = "sssBATRsss";
    std::string elaboration = "N/A";
    std::string data = "N/A";
    cptr cmmd = new char[coms.length()+1];
    cptr instr = new char[inst.length()+1];
    cptr elabs = new char[elaboration.length()+1];
    cptr dd = new char[data.length()+1];
    std::strcpy(cmmd,coms.c_str());
    std::strcpy(instr,inst.c_str());
    std::strcpy(elabs,elaboration.c_str());
    std::strcpy(dd,data.c_str());
    Com->Debugging_Manual_Poll(cmmd,instr,elabs,dd);
    if(I.PollCommsBuffer()){
        I.FormatCommunication();
        I.SendInstructionToSM();
        Com->releaseLatestCommunication();
    }
    ///
    delete Com;
    delete stat;
    return 0;
}
Fiptr StartLogFile(int &exception){
    TimeClass t(4);
    auto s = new std::ofstream("Logfile.txt", std::ios_base::app | std::ios_base::out);
    try {
        if(s->is_open()) {
            *s << t.getTime() << std::endl;
            *s << "Program initialised " << std::endl;
        }
        else{
            throw 6;
        }
    }
    catch(int &e){
        exception = e;
    }
    return s;
}