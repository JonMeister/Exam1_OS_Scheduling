// main.cpp
#include <iostream>
#include "Algorithm.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

/**
 * @brief Reads a file containing process information and returns a vector of Process pointers.
 *
 * The expected format of the file is:
 * - Each line contains process information separated by semicolons.
 * - The first and second line are ignored (headers).
 *
 * @param fileName The name of the file to read.
 * @return std::vector<Process*> A vector of pointers to Process objects created from the file data.
 */
std::vector<Process*> readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Error opening file" << std::endl;
        return std::vector<Process*>{};
    }
    std::string line;
    std::vector<Process*> processVector;
    std::getline(file, line); // Ignore the first line (header)
    std::getline(file, line); // Ignore the second line (header)

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, btStr, atStr, qStr, pStr;

        std::getline(ss, name, ';');
        std::getline(ss, btStr, ';');
        std::getline(ss, atStr, ';');
        std::getline(ss, qStr, ';');
        std::getline(ss, pStr, ';');

        int BT = std::stoi(btStr);
        int AT = std::stoi(atStr);
        int Q = std::stoi(qStr);
        int P = std::stoi(pStr);

        processVector.push_back(new Process(name, BT, AT, Q, P));
    }
    file.close();
    return processVector;
}

/**
 * @brief Writes process information and their averages to an output file.
 *
 * The output file includes the process details and average metrics calculated.
 *
 * @param fileName The name of the output file.
 * @param processVector A vector of pointers to Process objects.
 * @param averagesVector A vector containing average metrics: WT, CT, RT, and TAT.
 */
void writeToFile(const std::string& fileName, std::vector<Process*> processVector, std::vector<double> averagesVector) {
    // Generating an output file
    std::string directory="./Results/";
    std::ofstream outFile(directory+"results_" + fileName);

    if (!outFile) {
        std::cerr << "Error: no se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    // Writing headers
    outFile << "# archivo: " << fileName << std::endl;
    outFile << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT" << std::endl;

    // Writing data
    for (Process* process : processVector) {
        outFile << process->getName() << "; " <<
            process->getBT() << "; " << process->getAT() << "; " <<
            process->getQ() << "; " << process->getP() << "; " <<
            process->getWT() << "; " << process->getCT() << "; " <<
            process->getRT() << "; " << process->getTAT() << std::endl;
    }

    // Writing averages
    outFile << std::fixed << std::setprecision(2) << "WT=" << averagesVector[0] << "; CT=" << averagesVector[1] <<
            "; RT=" << averagesVector[2] << "; TAT=" << averagesVector[3] << ";" << std::endl;

    // Closing the file
    outFile.close();
    std::cout << "File successfully generated: " << "results_"+fileName << std::endl;
}

/**
 * @brief Main function of the program.
 *
 * This function orchestrates reading from a file, processing the data through different scheduling algorithms,
 * and writing the results back to an output file. It also handles user input to select the scheduling queues.
 *
 * @return int Exit status of the program.
 */
int main() {
    int userInput, q1, q2, q3;
    std::vector<double> averagesVector;
    std::vector<std::string> queues;
    std::string fileName;
    std::cout<<"**************************************"<<std::endl<<"Welcome to the MLQ algorithm simulation\n"<<"Please enter the file's name without spaces: "<<std::endl;
    std::cin >> fileName;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    const std::string fileDir = "./Files/"+fileName;
    std::vector<Process*> processVector = readFile(fileDir);
    if (processVector.empty()) {return 2;}

    std::cout << "Please select the queues you'd like to use:" << std::endl <<
                 "1. Q1: RR(1), Q2: RR(3), Q3: SJF" << std::endl <<
                 "2. Q1: RR(3), Q2: RR(5), Q3: FCFS" << std::endl <<
                 "3. Q1: RR(2), Q2: RR(3), Q3: STCF" << std::endl;
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            q1 = 1; q2 = 3; q3 = 0;
            queues = {"RR", "RR", "SJF"};
            break;
        case 2:
            q1 = 3; q2 = 5; q3 = 0;
            queues = {"RR", "RR", "FCFS"};
            break;
        case 3:
            q1 = 2; q2 = 3; q3 = 0;
            queues = {"RR", "RR", "STCF"};
            break;
        default:
            std::cout << "Invalid input!" << std::endl;
            return 1;
    }

    Algorithm algorithm{};
    algorithm.MLQ(processVector, queues, q1, q2, q3);
    averagesVector = algorithm.getAverage(processVector);
    writeToFile(fileName, processVector, averagesVector);

    return 0;
}


