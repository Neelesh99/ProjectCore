//
// Created by Neelesh on 22/10/2018.
//

#ifndef SYMPHONY03_SYMPHONYNETWORK_HPP
#define SYMPHONY03_SYMPHONYNETWORK_HPP
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <thread>
class SymphonyNetwork {
private:
    //// Member data ////
    std::vector<std::vector<double>> Activation_All_Layers;
    /// [x] Layers [y] Nodes ///
    std::vector<std::vector<std::vector<double>>> Interlayer_Weights;
    ///[x] Interlayer no [y] Node ref [z] Weight ref ///
    std::vector<std::vector<std::vector<double>>> Interlayer_Delta_Weights;
    ///[x]Interlayer no [y] Node ref [z] Weight ref ///
    std::vector<std::vector<double>> Sigma_Interlayer;
    ///[x]Interlayer no [y] Node ref ///

    std::vector<double> Input_Data;
    std::vector<double> Answer_Data;

    int Total_Layer_Count;
    int Hidden_Layer_Count;
    int Interlayer_Count;
    std::vector<int> Hidden_Nodes;
    int Input_Nodes;
    int Output_Nodes;
    std::vector<int> Node_Count;
    std::vector<int> Interlayer_Node_Count;

    double Eta;
    double Mu;
    void Init_Activation_Structure();
    void Init_Weight_Structure();
    void Init_Sigma_Structure();
    void Init_Ans();
    double Single_Node_Calc(int Interlayer, int Node_Ref);
    void Activation_Calc();
    void Sigma_Final_Layer();
    double Sigma_General_Node(int Interlayer, int Node_Ref);
    void Sigma_All_Nodes();
    void Delta_Single_Node(int Interlayer, int Node_Ref);
    void Delta_All_Nodes();
    void Weight_Update();
    double Sigma_function(double epsilon);
    double Random_Weight();

public:
    SymphonyNetwork();
    SymphonyNetwork(int input_nodes,int hidden_layers, std::vector<int>* hidden_nodes, int output_nodes);
    //void Init_Network(int input_nodes, int hidden_layers, std::vector<int> hidden_nodes, int output_nodes);
    void Set_Input(std::vector<double> input_data);
    void Set_Ans(std::vector<double> answers);
    void Set_Eta(double value);
    void Set_Mu(double value);
    void Forward_Sweep();
    void Backward_Sweep();
    void Cycle();
    double Get_Output(int Node_Ref);
    void printToFile(std::string filename);
    void readFromFile(std::string filename);
    void printToFile();
    void readFromFile();
    bool is_empty(std::ifstream& pFile);
    void printData();
};


#endif //SYMPHONY03_SYMPHONYNETWORK_HPP
