//
// Created by Neelesh on 22/10/2018.
//

#include "SymphonyNetwork.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <thread>
SymphonyNetwork::SymphonyNetwork() = default;
SymphonyNetwork::SymphonyNetwork(int input_nodes,int hidden_layers, std::vector<int>* hidden_nodes, int output_nodes){
    Input_Nodes = input_nodes;
    Output_Nodes = output_nodes;
    Hidden_Layer_Count = hidden_layers;
    Hidden_Nodes = *hidden_nodes;
    Total_Layer_Count = Hidden_Layer_Count + 2;
    Interlayer_Count = Total_Layer_Count - 1;
    Node_Count.push_back(Input_Nodes);
    for(int i = 0; i < Hidden_Layer_Count; i++){
        Node_Count.push_back(Hidden_Nodes[i]);
    }
    Node_Count.push_back(Output_Nodes);
    for(int i = 0; i < Hidden_Layer_Count; i++){
        Interlayer_Node_Count.push_back(Hidden_Nodes[i]);
    }
    Interlayer_Node_Count.push_back(Output_Nodes);

    Init_Activation_Structure();
    Init_Weight_Structure();
    Init_Sigma_Structure();
    Init_Ans();
}


////Initialise Structures////
void SymphonyNetwork :: Init_Activation_Structure(){
    for(int i = 0; i < Total_Layer_Count; i++){
        std::vector<double> temp;
        for(int j = 0 ; j < Node_Count[i]; j++){
            temp.push_back(0);
        }
        Activation_All_Layers.push_back(temp);
    }

}
void SymphonyNetwork :: Init_Weight_Structure(){
    for(int i = 0; i < Interlayer_Count; i++){
        std::vector<std::vector<double>> temp0;
        for(int j = 0 ; j  < Interlayer_Node_Count[i]; j++){
            std::vector<double> temp1;
            for(int k = 0; k < Node_Count[i]; k++){
                temp1.push_back(Random_Weight());
            }
            temp0.push_back(temp1);
        }
        Interlayer_Weights.push_back(temp0);
    }
    for(int i = 0; i < Interlayer_Count; i++){
        std::vector<std::vector<double>> temp0;
        for(int j = 0 ; j  < Interlayer_Node_Count[i]; j++){
            std::vector<double> temp1;
            for(int k = 0; k < Node_Count[i]; k++){
                temp1.push_back(0);
            }
            temp0.push_back(temp1);
        }
        Interlayer_Delta_Weights.push_back(temp0);
    }
}
void SymphonyNetwork :: Init_Sigma_Structure(){
    for(int i = 0; i < Interlayer_Count; i++){
        std::vector<double> temp;
        for(int j = 0; j < Interlayer_Node_Count[i]; j++){
            temp.push_back(0);
        }
        Sigma_Interlayer.push_back(temp);
    }
}
////Initialise & Set Answers & input////
void SymphonyNetwork :: Init_Ans(){
    for(int i = 0; i < Output_Nodes; i++){
        Answer_Data.push_back(0);
    }
}
void SymphonyNetwork :: Set_Input(std::vector<double> input_data){
    Input_Data.clear();
    for(int i = 0;i < Input_Nodes; i++){
        Input_Data.push_back(input_data[i]);
    }
    for(int i = 0 ; i  < Input_Nodes; i++){
        Activation_All_Layers[0][i] = Input_Data[i];
    }
}
void SymphonyNetwork :: Set_Ans(std::vector<double> answers){
    Answer_Data.clear();
    for(int i = 0 ; i < Output_Nodes; i++){
        Answer_Data.push_back(answers[i]);
    }
}
//// Initialise Factors ////
void SymphonyNetwork :: Set_Eta(double value){
    Eta = value;
}
void SymphonyNetwork :: Set_Mu(double value){
    Mu = value;
}
//// Forward Sweep Process ////
void SymphonyNetwork :: Forward_Sweep(){
    Activation_Calc();
}
///Modular functions ///
double SymphonyNetwork :: Single_Node_Calc(int Interlayer, int Node_Ref){
    double epsilon = 0;
    for(int i = 0; i < Node_Count[Interlayer]; i++){
        epsilon += Activation_All_Layers[Interlayer][i] * Interlayer_Weights[Interlayer][Node_Ref][i];
    }
    return Sigma_function(epsilon);
}
void SymphonyNetwork :: Activation_Calc(){
    for(int i = 0; i < Interlayer_Count; i++){
        for(int j = 0 ; j < Interlayer_Node_Count[i]; j++){
            Activation_All_Layers[i+1][j] = Single_Node_Calc(i,j);
        }
    }
}
//// Backward Sweep Process ////
void SymphonyNetwork :: Backward_Sweep(){
    Sigma_All_Nodes();
    Delta_All_Nodes();
    Weight_Update();
}
/// Modular Functions ///
///Sigma Process///
void SymphonyNetwork :: Sigma_Final_Layer(){
    for(int i = 0; i < Output_Nodes; i++){
        double xi = Activation_All_Layers[Total_Layer_Count - 1][i];
        double yi = Answer_Data[i];
        Sigma_Interlayer[Interlayer_Count-1][i] = (xi - yi)*xi*(1-xi);
    }
}
double SymphonyNetwork :: Sigma_General_Node(int Interlayer, int Node_Ref){
    double temp = 0;
    double xi = Activation_All_Layers[Interlayer+1][Node_Ref];
    for(int i = 0; i < Interlayer_Node_Count[Interlayer+1]; i++){
        temp += Sigma_Interlayer[Interlayer+1][i] * Interlayer_Weights[Interlayer+1][i][Node_Ref];
    }
    return (temp * xi * (1-xi));
}
void SymphonyNetwork :: Sigma_All_Nodes(){
    Sigma_Final_Layer();
    for(int i = (Interlayer_Count-2); i >= 0; i--){
        for(int j = 0; j<Node_Count[i+1]; j++){
            Sigma_General_Node(i,j);
        }
    }
}
///Delta Process///
void SymphonyNetwork :: Delta_Single_Node(int Interlayer, int Node_Ref){
    for(int i = 0; i< Node_Count[Interlayer]; i++){
        double tau = Eta*Sigma_Interlayer[Interlayer][Node_Ref]*Activation_All_Layers[Interlayer][i];
        double psi = Mu*Interlayer_Delta_Weights[Interlayer][Node_Ref][i];
        Interlayer_Delta_Weights[Interlayer][Node_Ref][i] = tau + psi;
    }
}
void SymphonyNetwork :: Delta_All_Nodes(){
    for(int i = 0; i < Interlayer_Count; i++){
        for(int j = 0; j < Node_Count[i+1]; j++){
            Delta_Single_Node(i,j);
        }
    }
}
///Weight Update///
void SymphonyNetwork :: Weight_Update(){
    for(int i = 0; i < Interlayer_Count; i++){
        for(int j = 0; j<Node_Count[i+1]; j++){
            for(int k = 0; k < Node_Count[i]; k++){
                Interlayer_Weights[i][j][k] -= Interlayer_Delta_Weights[i][j][k];
            }
        }
    }
}
//// Output Data ////
double SymphonyNetwork :: Get_Output(int Node_Ref){
    return Activation_All_Layers[Total_Layer_Count-1][Node_Ref];
}
double SymphonyNetwork ::  Sigma_function(double epsilon) {
    double denominator;
    denominator = 1 + exp(-1 * epsilon);

    return pow(denominator, -1);
}
double SymphonyNetwork ::  Random_Weight(){
    double ran =  ((std::rand() % 200) - 100);
    return ran / 100;

}
/// Print Values To File ///
void SymphonyNetwork ::  printToFile(std::string filename){
    std::ofstream file(filename);
    if(file.is_open()){
        for(int i = 0; i < Interlayer_Count; i++) {
            for (int j = 0; j < Interlayer_Node_Count[i]; j++) {
                for(int k = 0; k < Node_Count[i]; k++) {
                    file << Interlayer_Weights[i][j][k] << " ";
                }
                file << std::endl;
            }
            file << std::endl;
        }
    }
    file.close();
}
void SymphonyNetwork ::  printToFile(){
    std::ofstream file("type.ncfg");

    if(file.is_open()){
        for(int i = 0; i < Interlayer_Count; i++) {
            for (int j = 0; j < Interlayer_Node_Count[i]; j++) {
                for(int k = 0; k < Node_Count[i]; k++) {
                    file << Interlayer_Weights[i][j][k] << " ";
                }
                file << std::endl;
            }
            file << std::endl;
        }
    }
    file.close();
}
void SymphonyNetwork ::readFromFile(std::string filename) {
    try {
        std::ifstream file(filename);
        if (file.is_open() && !is_empty(file)) {
            for (int i = 0; i < Interlayer_Count; i++) {
                for (int j = 0; j < Interlayer_Node_Count[i]; j++) {
                    for (int k = 0; k < Node_Count[i]; k++) {
                        file >> Interlayer_Weights[i][j][k];
                    }
                }
            }
        }
        else{
            throw 4;
        }
        file.close();
    }
    catch(int &e){
        std::cout << "Invalid Read From weighting file" << std::endl;
    }
}
void SymphonyNetwork ::readFromFile() {
    std::ifstream file("Settings.config");
    if(file.is_open() && !is_empty(file)){
        for(int i = 0; i < Interlayer_Count; i++) {
            for (int j = 0; j < Interlayer_Node_Count[i]; j++) {
                for(int k = 0; k < Node_Count[i]; k++) {
                    file >> Interlayer_Weights[i][j][k];
                }
            }
        }
    }
    file.close();
}
bool SymphonyNetwork :: is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}
void SymphonyNetwork ::printData() {
    std::cout << Input_Nodes << std::endl;
    std::cout << Hidden_Layer_Count << std::endl;
    for(int i = 0; i < Hidden_Layer_Count; i++){
        std::cout << Hidden_Nodes[i] << std::endl;
    }
    std::cout << Output_Nodes << std::endl;
}