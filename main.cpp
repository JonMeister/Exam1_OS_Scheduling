// main.cpp
#include <iostream>
#include "Algorithm.h"
#include <fstream>
#include <sstream>

std::vector<Process*> readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Error opening file" << std::endl;
    }
    std::string line;
    std::vector<Process*> processVector;
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file,line)) {
        std::stringstream ss(line);
        std::string name, btStr, atStr,qStr, pStr;

        std::getline(ss, name, ';');
        std::getline(ss, btStr, ';');
        std::getline(ss, atStr, ';');
        std::getline(ss, qStr, ';');
        std::getline(ss, pStr, ';');



        int BT=std::stoi(btStr);
        int AT=std::stoi(atStr);
        int Q=std::stoi(qStr);
        int P=std::stoi(pStr);



        processVector.push_back(new Process(name,BT,AT,Q,P));
    }
    file.close();
    return processVector;
}

void writeToFile(const std::string& fileName, std::vector<Process*>processVector, std::vector <double>averagesVector) {
    // Crear un archivo de salida
    std::ofstream outFile("results"+fileName);

    if (!outFile) {
        std::cerr << "Error: no se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    // Escribir encabezados
    outFile << "# archivo: "<<fileName<< std::endl;
    outFile << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT" << std::endl;

    // Escribir datos de los procesos
    for (Process* process : processVector) {
            outFile << process->getName()<< "; "<<
            process->getBT()<< "; "<<process->getAT()<< "; "<<
            process->getAT()<< "; "<<process->getQ()<< "; "<<
            process->getP()<< "; "<<process->getWT()<< "; "<<
            process->getCT()<< "; "<<process->getRT()<< "; "<<
            process->getTAT() << std::endl;
    }

    // Escribir los promedios al final
    outFile << "WT=" << averagesVector[0] << "; CT=" << averagesVector[1] << "; RT=" << averagesVector[2] << "; TAT=" << averagesVector[3] << ";" << std::endl;

    // Cerrar el archivo
    outFile.close();
    std::cout << "Archivo escrito con éxito: " << "results"+fileName << std::endl;
}

int main() {
    int userInput,q1,q2,q3;
    std::vector <double> averagesVector;
    std::vector<std::string>queues;
    const std::string fileName="mlq001.txt";
    std::vector<Process*> processVector=readFile(fileName);

    std::cout << "Please select the queues you'd like to use:" << std::endl<<
                 "1. Q1: RR(1), Q2: RR(3), Q3: SJF" << std::endl<<
                 "2. Q1: RR(3), Q2: RR(5), Q3: FCFS"<<std::endl<<
                 "3. Q1: RR(2), Q2: RR(3), Q3: STCF"<<std::endl;
    std::cin>>userInput;

    switch (userInput) {
        case 1:
            q1=1;q2=3;q3=0;
            queues={"RR","RR","SJF"};
            break;
        case 2:
            q1=3;q2=5;q3=0;
            queues={"RR","RR","FCFS"};
            break;
        case 3:
            q1=2;q2=3;q3=0;
            queues={"RR","RR","STCF"};
        default:
            std::cout << "Invalid input!" << std::endl;

    }
    Algorithm algorithm{};


    algorithm.MLQ(processVector,queues,q1,q2,q3);
    averagesVector=algorithm.getAverage(processVector);
    writeToFile("results_"+fileName,processVector,averagesVector);


    return 0;
}


