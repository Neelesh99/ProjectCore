//
// Created by Neelesh on 29/01/2019.
//

#ifndef PROJECTCORE_COMMUNCATIONSBUFFER_HPP
#define PROJECTCORE_COMMUNCATIONSBUFFER_HPP

#include <iostream>
#include <algorithm>
#include <queue>
#include "Communication.hpp"
typedef Communication* Comptr;
typedef char* cptr;
class CommunicationsBuffer {
private:
    std::queue<Comptr> buffer;
    Comptr StartUp;
public:
    CommunicationsBuffer();
    void pollCommuncations();
    const cptr getLatestCommand();
    const cptr getLatestInstruction();
    const cptr getLatestElaboration();
    const cptr getLatestData();
    bool isEmpty();
    void releaseLatestCommunication();
    ~CommunicationsBuffer();
};


#endif //PROJECTCORE_COMMUNCATIONSBUFFER_HPP
