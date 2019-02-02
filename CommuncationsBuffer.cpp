//
// Created by Neelesh on 29/01/2019.
//

#include "CommuncationsBuffer.hpp"
#include "Communication.hpp"
#include <string>
#include <cstring>
typedef Communication* Comptr;
typedef char* cptr;

CommunicationsBuffer::CommunicationsBuffer() {
   cptr  StartUpCommand = new char[10];
   std::string temp = "cccINSTccc";
   std::strcpy(StartUpCommand,temp.c_str());
   cptr PowerOnInstruction = new char[10];
   temp = "sssPWRNsss";
   std::strcpy(PowerOnInstruction,temp.c_str());
   cptr ElaborationStartUp = new char[3];
   temp = "N/A";
   std::strcpy(ElaborationStartUp,temp.c_str());
   cptr StartUpData = new char[3];
   temp = "N/A";
   std::strcpy(StartUpData,temp.c_str());
   StartUp = new Communication(StartUpCommand,PowerOnInstruction,ElaborationStartUp,StartUpData);
   buffer.push(StartUp);
}
CommunicationsBuffer::~CommunicationsBuffer() {
   delete StartUp;
}
bool CommunicationsBuffer::isEmpty() {
    if(buffer.size() == 0){
        return true;
    }
    return false;
}
void CommunicationsBuffer::pollCommuncations() {

}
const cptr CommunicationsBuffer::getLatestCommand() {
   Comptr temp = buffer.front();
   cptr Out = temp->getCommand();
   return Out;
}
const cptr CommunicationsBuffer::getLatestInstruction() {
   Comptr temp = buffer.front();
   cptr Out = temp->getInstruction();
   return Out;
}
const cptr CommunicationsBuffer::getLatestElaboration() {
   Comptr temp = buffer.front();
   cptr Out = temp->getElaboration();
   return Out;
}
const cptr CommunicationsBuffer::getLatestData() {
   Comptr temp = buffer.front();
   cptr Out = temp->getData();
   return Out;
}
void CommunicationsBuffer::releaseLatestCommunication() {
   buffer.pop();
}