//
// Created by Neelesh on 29/01/2019.
//

#include "Communication.hpp"
#include <iostream>
#include <string>
Communication::Communication() = default;
Communication::Communication (cptr Command, cptr Instruction, cptr Data, cptr Elaboration): Command_Key_Word(Command), Instruction_Key_Word(Instruction), Data_Word(Data), Elaboration_Word(Elaboration){
    CommandKeyWord = Command_Key_Word;
    InstructionKeyWord = Instruction_Key_Word;
    DataWord = Data_Word;
    ElaborationWord = Elaboration_Word;
}
const cptr Communication::getCommand(){
    return Command_Key_Word;
}
const cptr Communication::getInstruction(){
    return Instruction_Key_Word;
}
const cptr Communication::getData(){
    return Data_Word;
}
const cptr Communication::getElaboration() {
    return Elaboration_Word;
}
Communication::~Communication() = default;