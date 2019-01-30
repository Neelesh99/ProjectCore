//
// Created by Neelesh on 29/01/2019.
//

#include "CommuncationsBuffer.hpp"
#include "Communication.hpp"
#include <string>
typedef Communication* Comptr;
typedef char* cptr;

CommunicationsBuffer::CommunicationsBuffer() {
   cptr StartUpCommand = "cccINSTccc";
   cptr PowerOnInstruction = "sssPWRNsss";
   cptr ElaborationStartUp = "N/A";
   cptr StartUpData = "N/A";
   StartUp = new Communication(StartUpCommand,PowerOnInstruction,ElaborationStartUp,StartUpData);
   buffer.push(StartUp);
}
CommunicationsBuffer::~CommunicationsBuffer() {
   delete StartUp;
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