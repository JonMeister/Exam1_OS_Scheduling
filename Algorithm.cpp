//
// Created by jonat on 04/10/2024.
//

#include "Algorithm.h"

#include <algorithm>
#include <iostream>

Algorithm::Algorithm() = default;

bool orderByATAndName(Process* a, Process* b) {
    if(a->getAT() == b->getAT()) {
        return a->getName() < b->getName();
    }
    return a->getAT() < b->getAT();
}
bool orderByRemTimeAndName(Process* a, Process* b) {
    if(a->getRemTime() == b->getRemTime()) {
        return a->getName() < b->getName();
    }
    return a->getRemTime() < b->getRemTime();
}
bool orderByBTAndName(Process* a, Process* b) {
    if(a->getBT() == b->getBT()) {
        return a->getName() < b->getName();
    }
    return a->getBT() < b->getBT();
}


void Algorithm::FCFS(std::vector<Process*> processVector,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByATAndName);
    std::cout << "Sorting processes by AT and name." << std::endl;
    for (Process* process : processVector) {

        std::cout <<"Attending process "<<process->getName()<<" in time: "<<time1<<std::endl;
        process->setRT(time1);
        time1+=process->getBT();
        std::cout<<"Process "<<process->getName()<<" finished in time: "<<time1<<std::endl;
        process->setCT(time1);
        process->setTAT(process->getTAT());
        process->setWT(process->getWT());
        std::cout << "Metrics: " << std::endl << "CT: " << process->getCT() << ", TAT: " << process->getTAT() <<
                ", WT: " << process->getWT() << std::endl;
    }
}


void Algorithm::SJF(std::vector<Process *> processVector,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByATAndName);
    std::cout << "Sorted process vector by arrival time and name." << std::endl;

    // Procesar el primer proceso
    processVector[0]->setRT(time1);
    time1 += processVector[0]->getBT();
    processVector[0]->setCT(time1);
    processVector[0]->setTAT(processVector[0]->getTAT());
    processVector[0]->setWT(processVector[0]->getWT());
    std::cout << "Processing first process: " << processVector[0]->getName() << std::endl;
    std::cout << "CT: " << processVector[0]->getCT() << ", TAT: " << processVector[0]->getTAT() << ", WT: " << processVector[0]->getWT() << std::endl;

    processVector.erase(processVector.begin());
    std::sort(processVector.begin(), processVector.end(), orderByATAndName);
    std::cout << "Sorted remaining process vector by arrival time and name." << std::endl;
    std::vector<Process *> processQueue;
    while (!processVector.empty() || !processQueue.empty()) {


        // Mover procesos a la cola de procesos
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
            std::sort(processQueue.begin(), processQueue.end(), orderByBTAndName);
            Process* process= processQueue.front();
            process->setRT(time1);
            std::cout << "Processing process: " << process->getName() << std::endl;
            time1 += process->getBT();
            process->setCT(time1);
            process->setTAT(process->getTAT());
            process->setWT(process->getWT());
            std::cout << "CT: " << process->getCT() << ", TAT: " << process->getTAT() << ", WT: " << process->getWT() << std::endl;

            // Eliminar el proceso de la cola
            processQueue.erase(std::remove(processQueue.begin(), processQueue.end(), process), processQueue.end());
            std::cout << "Removed process from queue: " << process->getName() << std::endl;

    }
}

void Algorithm::STCF(std::vector<Process*> processVector,int& time1) {
    std::sort(processVector.begin(), processVector.end(), orderByATAndName);
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
        std::sort(processQueue.begin(), processQueue.end(), orderByRemTimeAndName);
        std::cout<<"Primero en la fila= "<<processQueue[0]->getName()<<std::endl;

        if (!processQueue.empty()) {
            Process* currentProcess = processQueue.front();
            std::cout << "Current process: " << currentProcess->getName()
                      << ", Remaining Time: " << currentProcess->getRemTime() << std::endl;

            currentProcess->setRemTime(currentProcess->getRemTime() - 1);
            time1 += 1;

            // Verificar si el proceso ha terminado
            if (currentProcess->getRemTime() == 0) { // Cuando queda 1, se va a 0 en la siguiente iteración
                currentProcess->setCT(time1);
                // Calcular el tiempo de espera
                int waitTime = time1 - currentProcess->getBT() - currentProcess->getAT();

                std::cout << "Process " << currentProcess->getName()
                          << " completed at time " << time1 << std::endl;
                currentProcess->setTAT(currentProcess->getTAT());
                std::cout << "Wait Time: " << currentProcess->getWT() << std::endl;
                // Sacar el proceso completado de la cola
                processQueue.erase(processQueue.begin());
            }

            // Verificar si hay nuevos procesos que llegan y hacer el cambio si es necesario
            // Después de cada decremento de tiempo, reordenar la cola si es necesario
            std::sort(processQueue.begin(), processQueue.end(), orderByRemTimeAndName);
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
    std::sort(processVector.begin(), processVector.end(), orderByATAndName); // Ordenar por tiempo de llegada
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
                std::cout << "Wait Time: " << currentProcess->getWT() << std::endl;
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

void Algorithm::MLQ(std::vector<Process*> processes, int q, std::string highPriorityAlgorithm, std::string lowPriorityAlgorithm) {
    std::vector<Process*> highPriorityQueue; // Cola de alta prioridad
    std::vector<Process*> lowPriorityQueue;  // Cola de baja prioridad

    int time1 = 0; // Tiempo actual

    // Asignar procesos a colas según su prioridad
    for (Process* process : processes) {
        if (process->getPriority() == 1) {
            highPriorityQueue.push_back(process);
        } else {
            lowPriorityQueue.push_back(process);
        }
    }

    // Ejecutar el algoritmo para la cola de alta prioridad
    std::cout << "Executing high priority queue." << std::endl;
    if (highPriorityAlgorithm == "RR") {
        std::cout << "Using Round Robin for high priority queue." << std::endl;
        RR(highPriorityQueue, q, time1);
    } else if (highPriorityAlgorithm == "SJF") {
        std::cout << "Using Shortest Job First for high priority queue." << std::endl;
        SJF(highPriorityQueue, time1);
    } else if (highPriorityAlgorithm == "FCFS") {
        std::cout << "Using First-Come, First-Served for high priority queue." << std::endl;
        FCFS(highPriorityQueue, time1);
    }

    // Ejecutar el algoritmo para la cola de baja prioridad
    std::cout << "Executing low priority queue." << std::endl;
    if (lowPriorityAlgorithm == "RR") {
        std::cout << "Using Round Robin for low priority queue." << std::endl;
        RR(lowPriorityQueue, q, time1);
    } else if (lowPriorityAlgorithm == "SJF") {
        std::cout << "Using Shortest Job First for low priority queue." << std::endl;
        SJF(lowPriorityQueue, time1);
    } else if (lowPriorityAlgorithm == "FCFS") {
        std::cout << "Using First-Come, First-Served for low priority queue." << std::endl;
        FCFS(lowPriorityQueue, time1);
    }
}

void Algorithm::getAverage(std::vector<Process *> processVector) {
    double averageWT, averageCT, averageRT, averageTAT;
    for (auto it = processVector.begin(); it != processVector.end();it++) {
        averageCT += (*it)->getCT();
        averageRT += (*it)->getRT();
        averageTAT += (*it)->getTAT();
        averageWT += (*it)->getWT();
    }
    averageWT /= processVector.size();
    averageCT /= processVector.size();
    averageRT /= processVector.size();
    averageTAT /= processVector.size();

    std::cout << "**************************************" << std::endl << "Printing results:" << std::endl;
    std::cout << "Average WT: " << averageWT << std::endl;
    std::cout << "Average CT: " << averageCT << std::endl;
    std::cout << "Average RT: " << averageRT << std::endl;
    std::cout << "Average TAT: " << averageTAT << std::endl;


}

