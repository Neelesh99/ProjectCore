//
// Created by Neelesh on 29/01/2019.
//

#include "Communication.hpp"
#include <iostream>
#include <string>
Communication::Communication() = default;
Communication::Communication (cptr Command, cptr Instruction, cptr Data, cptr Elaboration){
    Command_Key_Word = new char[10];
    Command_Key_Word = Command;
    CommandKeyWord = Command_Key_Word;
    //std::cout << Command_Key_Word << std::endl;
    //std::cout << CommandKeyWord << std::endl;
    Instruction_Key_Word = new char[10];
    Instruction_Key_Word = Instruction;
    InstructionKeyWord = Instruction_Key_Word;
    Elaboration_Word = new char[10];
    Elaboration_Word = Elaboration;
    ElaborationWord = Elaboration_Word;
    DataWord = Data;
    Data_Word = new char[DataWord.length()];
    Data_Word = Data;
}
const cptr Communication::getCommand(){
    //std::cout << Command_Key_Word << std::endl;
    return Command_Key_Word;
}
const cptr Communication::getInstruction(){
    return Instruction_Key_Word;
}
const cptr Communication::getData(){
    //std::cout << *Data_Word << std::endl;
    return Data_Word;
}
const cptr Communication::getElaboration() {
    return Elaboration_Word;
}
Communication::~Communication(){
    delete Command_Key_Word;
    delete Instruction_Key_Word;
    delete Data_Word;
    delete Elaboration_Word;
}