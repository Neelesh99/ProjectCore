//
// Created by Neelesh on 01/02/2019.
//

#include "Instructor.hpp"
Instructor::Instructor(Fiptr Log, CBptr CommsBuffer, SMptr Statemachine, int &exception):except(exception) {
    Logfile = Log;
    commsbuffer = CommsBuffer;
    statemachine = Statemachine;
}
bool Instructor::PollCommsBuffer() {
    if(!commsbuffer->isEmpty()){
        UnformattedCommand = commsbuffer->getLatestCommand();
        UnformattedInstruction = commsbuffer->getLatestInstruction();
        UnformattedElaboration = commsbuffer->getLatestElaboration();
        UnformattedData = commsbuffer->getLatestData();
        return true;
    }
    else{
        return false;
    }
}
Instructor::Instructor(Fiptr Log, CBptr CommsBuffer, int &exception):except(exception) {
    Logfile = Log;
    commsbuffer = CommsBuffer;
    *Logfile << "Instructor started in debugging mode, limited functionality available" << std::endl;
}
void Instructor::FormatCommunication() {
    char *command = new char[UnformattedCommand.length() + 1];
    strcpy(command, UnformattedCommand.c_str());
    char *FormatC = new char[5];
    FormatC[0] = command[3];
    FormatC[1] = command[4];
    FormatC[2] = command[5];
    FormatC[3] = command[6];
    FormatC[4] = '\0';
    FormattedCommand = FormatC;
    //std::cout << "command: " << command << " FormatC: " << FormatC << " FormattedCommand: " <<  FormattedCommand << std::endl;
    *Logfile << "Instructor has recieved " << FormattedCommand << " command" << std::endl;
    delete [] command;
    delete [] FormatC;
    char *instruction = new char[UnformattedInstruction.length() + 1];
    strcpy(instruction, UnformattedInstruction.c_str());
    char *instructionC = new char[5];
    instructionC[0] = instruction[3];
    instructionC[1] = instruction[4];
    instructionC[2] = instruction[5];
    instructionC[3] = instruction[6];
    instructionC[4] = '\0';
    FormattedInstruction = instructionC;
    *Logfile << "Instructor has recieved " << FormattedInstruction << " instruction" << std::endl;
    delete [] instruction;
    delete [] instructionC;
    char *elaboration = new char[UnformattedElaboration.length() + 1];
    strcpy(elaboration, UnformattedElaboration.c_str());
    char *elaborationC = new char[5];
    elaborationC[0] = elaboration[3];
    elaborationC[1] = elaboration[4];
    elaborationC[2] = elaboration[5];
    elaborationC[3] = elaboration[6];
    elaborationC[4] = '\0';
    FormattedElaboration = elaborationC;
    *Logfile << "Instructor has recieved " << FormattedElaboration << " elaboration" << std::endl;
    delete [] elaboration;
    delete [] elaborationC;
    char *data = new char[UnformattedData.length()+1];
    strcpy(data,UnformattedData.c_str());
    if(data[0] == 'd') {
        int NoOfData = data[3] - '0';
        *Logfile << NoOfData << " pieces of data to parse" << std::endl;
        std::vector<std::string> DataStore;
        int index = 5;
        for (int i = 0; i < NoOfData; i++) {
            char temp = 'o';
            int size = 0;
            int endpoint;
            while (temp != 'd') {
                size++;
                index++;
                temp = data[index];
                //std::cout << temp << " ";
            }
            //std::cout << std::endl;
            endpoint = index;
            index = index - size;
            //std::cout << "index: " << index  << " endpoint: " << endpoint  << "size_+1 "  << size+1<< std::endl;
            char *temparray = new char[size + 1];
            for (int j = 0; j < size; j++) {
                temparray[j] = data[index];
                //std::cout << temparray[j] << " ";
                index++;
            }
            //std::cout << std::endl;
            temparray[size] = '\0';
           // std::cout << temparray << std::endl;
            std::string tempstring = temparray;
            DataStore.push_back(tempstring);
            delete[] temparray;
            index++;
        }
        FormattedData = DataStore;
        *Logfile << "Instructor has recieved data" << std::endl;
        for(int i = 0; i < FormattedData.size();i++){
            *Logfile << FormattedData[i] << " ";
        }
        *Logfile << std::endl;
    }
    else{
        *Logfile << "Invalid or N/A data stream:\n" << UnformattedData << std::endl;
    }

}
void Instructor::SendInstructionToSM() {
    if(first){
        statemachine->StateChangeCall(&FormattedCommand, &FormattedInstruction,FormattedElaboration,NoofDataWords,FormattedData);
        *Logfile << "Instructor has submitted State Change Call" << std::endl;
        first = false;
        return;
    }
    statemachine->DeactivateCurrent();
    statemachine->StateChangeCall(&FormattedCommand, &FormattedInstruction,FormattedElaboration,NoofDataWords,FormattedData);
    *Logfile << "Instructor has submitted State Change Call" << std::endl;
}
void Instructor::RefreshInstructionSM() {
    statemachine->StateRefreshCall();
    *Logfile << "Instructor has submitted a State refresh Call" << std::endl;
}