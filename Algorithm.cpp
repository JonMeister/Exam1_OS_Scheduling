//
// Created by jonat on 04/10/2024.
//

#include "Algorithm.h"

#include <algorithm>
#include <iostream>

Algorithm::Algorithm() = default;

bool orderByPriorityATAndName(Process* a, Process* b) {
    if (a->getP() < b->getP()) {
        if(a->getAT() == b->getAT()) {
            return a->getName() < b->getName();
        }
        return a->getAT() < b->getAT();
    }
    return a->getP() < b->getP();
}
bool orderByPriorityRemTimeAndName(Process* a, Process* b) {
    if(a->getP() == b->getP()) {
        if(a->getRemTime() == b->getRemTime()) {
            return a->getName() < b->getName();
        }
        return a->getRemTime() < b->getRemTime();
    }

    return a->getP() < b->getP();
}
bool orderByPriorityBTAndName(Process* a, Process* b) {
    if(a->getP() == b->getP()) {
        if(a->getBT() == b->getBT()) {
            return a->getName() < b->getName();
        }
        return a->getBT() < b->getBT();
    }
    return a->getP() < b->getP();
}

void Algorithm::FCFS(std::vector<Process*> processVector,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByPriorityATAndName);
    std::cout << "Executing First Come First Served Algorithm." << std::endl;
    for (Process* process : processVector) {

        std::cout <<"Attending process "<<process->getName()<<" in time: "<<time1<<std::endl;
        process->setRT(time1);
        time1+=process->getBT();
        std::cout<<"Process "<<process->getName()<<" finished in time: "<<time1<<std::endl;
        process->setCT(time1);
        process->setTAT(process->getTAT());
        process->setWT(process->getWT());
        std::cout << "Metrics: " << std::endl << "CT: " << process->getCT() << ", TAT: " << process->getTAT() <<
                ", WT: " << process->getWT() <<", RT: "<<process->getRT()<< std::endl;
    }
}


void Algorithm::SJF(std::vector<Process *> processVector,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByPriorityATAndName);
    std::cout << "Executing Shortest Job First Algorithm." << std::endl;
    std::vector<Process *> processQueue;
    while (!processVector.empty() || !processQueue.empty()) {


        // Moving processes to the processes queue
        for (auto it = processVector.begin(); it != processVector.end();) {
            if (time1 >= (*it)->getAT()) {
                std::cout << "Adding process to queue: " << (*it)->getName() << std::endl;
                processQueue.push_back(*it);
                it = processVector.erase(it);
            } else {
                ++it;
            }
        }

        // Procesar los procesos en la cola
            std::sort(processQueue.begin(), processQueue.end(), orderByPriorityBTAndName);
            Process* process= processQueue.front();
            process->setRT(time1);
            std::cout << "Processing process: " << process->getName() << std::endl;
            time1 += process->getBT();
            process->setCT(time1);
            process->setTAT(process->getTAT());
            process->setWT(process->getWT());
            std::cout << "Metrics: " << std::endl << "CT: " << process->getCT() << ", TAT: " << process->getTAT() <<
            ", WT: " << process->getWT() <<", RT: "<<process->getRT()<< std::endl;

            // Eliminar el proceso de la cola
            processQueue.erase(std::remove(processQueue.begin(), processQueue.end(), process), processQueue.end());
            std::cout << "Removed process from queue: " << process->getName() << std::endl;

    }
}

void Algorithm::STCF(std::vector<Process*> processVector,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByPriorityATAndName);
    std::vector<Process*> processQueue;

    while (!processVector.empty() || !processQueue.empty()) {
        // Agregar procesos a la cola
        for (auto it = processVector.begin(); it != processVector.end();) {
            if (time1 >= (*it)->getAT()) {
                std::cout << "Adding process to queue: " << (*it)->getName() << " at time " << time1 <<"REM= "<<(*it)-> getRemTime()<<std::endl;
                processQueue.push_back(*it);
                (*it)->setRemTime((*it)->getBT()); // Inicializar tiempo restante
                it = processVector.erase(it); // Eliminar el proceso de processVector
            } else {
                ++it; // Avanzar el iterador
            }
        }

        // Ordenar la cola por tiempo restante
        std::sort(processQueue.begin(), processQueue.end(), orderByPriorityRemTimeAndName);
        std::cout<<"Primero en la fila= "<<processQueue[0]->getName()<<std::endl;

        if (!processQueue.empty()) {
            Process* currentProcess = processQueue.front();
            std::cout << "Current process: " << currentProcess->getName()
                      << ", Remaining Time: " << currentProcess->getRemTime() << std::endl;
            if (currentProcess->getRT() == -1) {currentProcess->setRT(time1);}
            currentProcess->setRemTime(currentProcess->getRemTime() - 1);
            time1 += 1;

            // Verificar si el proceso ha terminado
            if (currentProcess->getRemTime() == 0) { // Cuando queda 1, se va a 0 en la siguiente iteración
                currentProcess->setCT(time1);
                std::cout << "Process " << currentProcess->getName()
                          << " completed at time " << time1 << std::endl;
                currentProcess->setTAT(currentProcess->getTAT());
                std::cout << "Metrics: " << std::endl << "CT: " << currentProcess->getCT() << ", TAT: " << currentProcess->getTAT() <<
                ", WT: " << currentProcess->getWT() <<", RT: "<<currentProcess->getRT()<< std::endl;
                // Sacar el proceso completado de la cola
                processQueue.erase(processQueue.begin());
            }

            // Verificar si hay nuevos procesos que llegan y hacer el cambio si es necesario
            // Después de cada decremento de tiempo, reordenar la cola si es necesario
            std::sort(processQueue.begin(), processQueue.end(), orderByPriorityRemTimeAndName);
            currentProcess=nullptr;
        } else {
            // Si no hay procesos para ejecutar, avanzar el tiempo
            std::cout << "No processes to execute. Advancing time." << std::endl;
            time1++;
        }
        std::cout << "Current Time: " << time1 << ", Queue size: " << processQueue.size() << std::endl;
    }
}
void Algorithm::RR(std::vector<Process*> processVector, int q,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByPriorityATAndName); // Ordenar por tiempo de llegada
    std::vector<Process*> processQueue;

    while (!processVector.empty() || !processQueue.empty()) {
        // Agregar procesos a la cola si ya han llegado (AT <= tiempo actual)
        for (auto it = processVector.begin(); it != processVector.end();) {
            if (time1 >= (*it)->getAT()) {
                std::cout << "Adding process to queue: " << (*it)->getName() << " at time " << time1
                          << " REM = " << (*it)->getRemTime() << std::endl;
                processQueue.push_back(*it);
                (*it)->setRemTime((*it)->getBT()); // Inicializar tiempo restante si es la primera vez
                it = processVector.erase(it); // Eliminar el proceso de la lista de procesos pendientes
            } else {
                ++it; // Avanzar al siguiente proceso si aún no ha llegado
            }
        }

        // Si hay procesos en la cola
        if (!processQueue.empty()) {
            Process* currentProcess = processQueue.front(); // Tomar el primer proceso de la cola
            processQueue.erase(processQueue.begin()); // Sacar el proceso de la cola
            std::cout << "Current process: " << currentProcess->getName()
                      << ", Remaining Time: " << currentProcess->getRemTime() << std::endl;
            if (currentProcess->getRT() == -1) {currentProcess->setRT(time1);}
            // Ejecutar el proceso por un quantum o hasta que termine
            int execTime = std::min(q, currentProcess->getRemTime()); // Quantum o el tiempo restante, lo que sea menor
            currentProcess->setRemTime(currentProcess->getRemTime() - execTime);
            time1 += execTime;

            // Verificar si el proceso ha terminado
            if (currentProcess->getRemTime() == 0) {
                currentProcess->setCT(time1); // Tiempo de finalización
                // Calcular el tiempo de espera (Wait Time)
                int waitTime = currentProcess->getCT() - currentProcess->getBT() - currentProcess->getAT();
                std::cout << "Process " << currentProcess->getName()
                          << " completed at time " << time1 << std::endl;
                currentProcess->setTAT(currentProcess->getTAT());
                std::cout << "Metrics: " << std::endl << "CT: " << currentProcess->getCT() << ", TAT: " << currentProcess->getTAT() <<
                                ", WT: " << currentProcess->getWT() <<", RT: "<<currentProcess->getRT()<< std::endl;
            } else {
                // Si no ha terminado, agregarlo de nuevo al final de la cola
                processQueue.push_back(currentProcess);
                std::cout << "Process " << currentProcess->getName()
                          << " is not finished, remaining time: " << currentProcess->getRemTime()
                          << ". Re-adding to queue." << std::endl;
            }
        } else {
            // Si no hay procesos para ejecutar, avanzar el tiempo
            std::cout << "No processes to execute. Advancing time." << std::endl;
            time1++;
        }

        // Imprimir el estado actual de la cola
        std::cout << "Current Time: " << time1 << ", Queue size: " << processQueue.size() << std::endl;
    }
}

void Algorithm::MLQ(std::vector<Process*> processes, std::vector<std::string> queues,int q1,int q2, int q3) {
    std::vector<Process*> highPriorityQueue; // Cola de alta prioridad
    std::vector<Process*> midPriorityQueue; // Cola de mediana prioridad
    std::vector<Process*> lowPriorityQueue;  // Cola de baja prioridad

    int time1 = 0; // Tiempo actual

    // Asignar procesos a colas según su cola
    for (Process* process : processes) {
        if (process->getQ() == 1) {
            highPriorityQueue.push_back(process);
        }
        else if (process->getQ() == 2) {
            midPriorityQueue.push_back(process);
        }
        else if (process->getQ()==3){lowPriorityQueue.push_back(process);
        }
        else{ std::cout << "There are only 3 queues"<<std::endl; }
    }

    // Ejecutar el algoritmo para la cola de alta prioridad
    std::cout << "Executing high priority queue." << std::endl;
    if (queues[0] == "RR") {
        std::cout << "Using Round Robin for high priority queue." << std::endl;
        RR(highPriorityQueue, q1, time1);
    } else if (queues[0] == "SJF") {
        std::cout << "Using Shortest Job First for high priority queue." << std::endl;
        SJF(highPriorityQueue, time1);
    } else if (queues[0] == "FCFS") {
        std::cout << "Using First-Come, First-Served for high priority queue." << std::endl;
        FCFS(highPriorityQueue, time1);
    }
    else if (queues[0] == "STCF") {
        std::cout << "Using Shortes Time to Complete First for high priority queue." << std::endl;
        STCF(highPriorityQueue, time1);
    }

    // Ejecutar el algoritmo para la cola de media prioridad
    std::cout << "Executing mid priority queue." << std::endl;
    if (queues[1] == "RR") {
        std::cout << "Using Round Robin for mid priority queue." << std::endl;
        RR(midPriorityQueue, q2, time1);
    } else if (queues[1] == "SJF") {
        std::cout << "Using Shortest Job First for mid priority queue." << std::endl;
        SJF(midPriorityQueue, time1);
    } else if (queues[1] == "FCFS") {
        std::cout << "Using First-Come, First-Served for mid priority queue." << std::endl;
        FCFS(midPriorityQueue, time1);
    }
    else if (queues[1] == "STCF") {
        std::cout << "Using Shortes Time to Complete First for mid priority queue." << std::endl;
        STCF(midPriorityQueue, time1);
    }

    // Ejecutar el algoritmo para la cola de baja prioridad
    std::cout << "Executing low priority queue." << std::endl;
    if (queues[2] == "RR") {
        std::cout << "Using Round Robin for low priority queue." << std::endl;
        RR(lowPriorityQueue, q3, time1);
    } else if (queues[2] == "SJF") {
        std::cout << "Using Shortest Job First for low priority queue." << std::endl;
        SJF(lowPriorityQueue, time1);
    } else if (queues[2] == "FCFS") {
        std::cout << "Using First-Come, First-Served for low priority queue." << std::endl;
        FCFS(lowPriorityQueue, time1);
    }
    else if (queues[2] == "STCF") {
        std::cout << "Using Shortes Time to Complete First for low priority queue." << std::endl;
        STCF(lowPriorityQueue, time1);
    }
}

std::vector<double> Algorithm::getAverage(std::vector<Process *> processVector) {
    double averageWT = 0, averageCT = 0, averageRT = 0, averageTAT = 0;
    std::vector<double> averagesVector;
    for (Process* process : processVector) {
        averageCT += process->getCT();
        averageRT += process->getRT();
        averageTAT += process->getTAT();
        averageWT += process->getWT();
    }
    averageWT /= processVector.size();
    averagesVector.push_back(averageWT);
    averageCT /= processVector.size();
    averagesVector.push_back(averageCT);
    averageRT /= processVector.size();
    averagesVector.push_back(averageRT);
    averageTAT /= processVector.size();
    averagesVector.push_back(averageTAT);
    

    std::cout << "**************************************" << std::endl << "Printing results:" << std::endl;
    std::cout << "Average WT: " << averageWT << std::endl;
    std::cout << "Average CT: " << averageCT << std::endl;
    std::cout << "Average RT: " << averageRT << std::endl;
    std::cout << "Average TAT: " << averageTAT << std::endl;
    return averagesVector;

}

