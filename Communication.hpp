//
// Created by Neelesh on 29/01/2019.
//

#ifndef PROJECTCORE_COMMUNICATION_HPP
#define PROJECTCORE_COMMUNICATION_HPP
#include <iostream>
#include <string>
typedef char* cptr;

class Communication {
private:
    std::string CommandKeyWord;
    cptr Command_Key_Word;
    std::string InstructionKeyWord;
    cptr Instruction_Key_Word;
    std::string DataWord;
    cptr Data_Word;
    std::string ElaborationWord;
    cptr Elaboration_Word;
public:
    Communication();
    Communication(cptr Command, cptr Instruction, cptr Data, cptr Elaboration);
    const cptr getCommand();
    const cptr getInstruction();
    const cptr getData();
    const cptr getElaboration();
    ~Communication();

};


#endif //PROJECTCORE_COMMUNICATION_HPP
