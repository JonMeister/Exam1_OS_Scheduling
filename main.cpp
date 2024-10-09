// main.cpp
#include <iostream>
#include "Algorithm.h"
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("MyProcesses2.txt");
    if (!file) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<Process*> processVector;
    std::getline(file, line);
    while (std::getline(file,line)) {
        std::stringstream ss(line);
        std::string name, bt_str, at_str, priority_str;

        std::getline(ss, name, ',');
        std::getline(ss, bt_str, ',');
        std::getline(ss, at_str, ',');


        int BT=std::stoi(bt_str);
        int AT=std::stoi(at_str);

        // Inicializar prioridad a 0 por defecto
        int priority = 0;

        // Comprobar si hay un cuarto parámetro (prioridad)
        if (std::getline(ss, priority_str, ',')) {
            priority = std::stoi(priority_str);
        }

        processVector.push_back(new Process(name,BT,AT,priority));
    }
    file.close();

    Algorithm algorithm{};
    algorithm.MLQ(processVector,4,"RR","FCFS");
    algorithm.getAverage(processVector);


    return 0;
}
