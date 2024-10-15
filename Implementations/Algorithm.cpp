//
// Created by jonat on 04/10/2024.
//

#include "../Headers/Algorithm.h"

#include <algorithm>
#include <iostream>

Algorithm::Algorithm() = default;

/**
 * @brief Comparator function to order processes by priority, arrival time, and name.
 *
 * @param a First process
 * @param b Second process
 * @return true if process `a` has higher priority or arrives earlier than process `b`.
 */
bool orderByPriorityATAndName(Process* a, Process* b) {
    if (a->getP() == b->getP()) {
        if(a->getAT() == b->getAT()) {
            return a->getName() < b->getName();
        }
        return a->getAT() < b->getAT();
    }
    return a->getP() > b->getP();
}

/**
 * @brief Comparator function to order processes by priority, remaining time, and name.
 *
 * @param a First process
 * @param b Second process
 * @return true if process `a` has higher priority or shorter remaining time than process `b`.
 */
bool orderByPriorityRemTimeAndName(Process* a, Process* b) {
    if(a->getP() == b->getP()) {
        if(a->getRemTime() == b->getRemTime()) {
            if(a->getAT() == b->getAT()) {
                return a->getName() < b->getName();
            }
            return a->getAT() < b->getAT();
        }
        return a->getRemTime() < b->getRemTime();
    }
    return a->getP() > b->getP();
}

/**
 * @brief Comparator function to order processes by priority, burst time, and name.
 *
 * @param a First process
 * @param b Second process
 * @return true if process `a` has higher priority or shorter burst time than process `b`.
 */
bool orderByPriorityBTAndName(Process* a, Process* b) {
    if(a->getP() == b->getP()) {
        if(a->getBT() == b->getBT()) {
            if(a->getAT()==b->getAT()) {
                return a->getName() < b->getName();
            }
            return a->getAT() < b->getAT();
        }
        return a->getBT() < b->getBT();
    }
    return a->getP() > b->getP();
}

void Algorithm::FCFS(std::vector<Process*> processVector,int& time1) {
    std::cout << "Executing First Come First Served Algorithm." << std::endl;
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
        std::sort(processQueue.begin(), processQueue.end(), orderByPriorityATAndName);
        Process* process = processQueue.front();
        std::cout <<"Attending process "<<process->getName()<<" in time: "<<time1<<std::endl;
        process->setRT(time1);
        time1+=process->getBT();
        std::cout<<"Process "<<process->getName()<<" finished in time: "<<time1<<std::endl;
        process->setCT(time1);
        std::cout << "Metrics: " << std::endl << "CT: " << process->getCT() << ", TAT: " << process->getTAT() <<
                ", WT: " << process->getWT() <<", RT: "<<process->getRT()<< std::endl;
        processQueue.erase(processQueue.begin());
    }
}

void Algorithm::SJF(std::vector<Process *> processVector,int& time1) {
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

        // Process the processes in the queue
        std::sort(processQueue.begin(), processQueue.end(), orderByPriorityBTAndName);
        Process* process= processQueue.front();
        process->setRT(time1);
        std::cout << "Processing process: " << process->getName() << std::endl;
        time1 += process->getBT();
        process->setCT(time1);

        std::cout << "Metrics: " << std::endl << "CT: " << process->getCT() << ", TAT: " << process->getTAT() <<
        ", WT: " << process->getWT() <<", RT: "<<process->getRT()<< std::endl;

        // Remove the process from the queue
        processQueue.erase(std::remove(processQueue.begin(), processQueue.end(), process), processQueue.end());
        std::cout << "Removed process from queue: " << process->getName() << std::endl;
    }
}

void Algorithm::STCF(std::vector<Process*> processVector, int& time1) {

    std::vector<Process*> processQueue;
    while (!processVector.empty() || !processQueue.empty()) {
        // Add processes to the queue
        for (auto it = processVector.begin(); it != processVector.end();) {
            if (time1 >= (*it)->getAT()) {
                std::cout << "Adding process to queue: " << (*it)->getName() << " at time " << time1 <<"REM= "<<(*it)-> getRemTime()<<std::endl;
                processQueue.push_back(*it);
                (*it)->setRemTime((*it)->getBT()); // Initialize remaining time
                it = processVector.erase(it); // Remove the process from processVector
            } else {
                ++it; // Move to the next process
            }
        }

        // Sort the queue by remaining time

        std::sort(processQueue.begin(), processQueue.end(), orderByPriorityRemTimeAndName);
        if (!processQueue.empty()) {
            Process* currentProcess = processQueue.front();
            std::cout << "Current process: " << currentProcess->getName()
                      << ", Remaining Time: " << currentProcess->getRemTime() << std::endl;
            if (currentProcess->getRT() == -1) {currentProcess->setRT(time1);}
            currentProcess->setRemTime(currentProcess->getRemTime() - 1);
            time1 += 1;

            // Check if the process has finished
            if (currentProcess->getRemTime() == 0) { // Process completed
                currentProcess->setCT(time1);
                std::cout << "Process " << currentProcess->getName()
                          << " completed at time " << time1 << std::endl;

                std::cout << "Metrics: " << std::endl << "CT: " << currentProcess->getCT() << ", TAT: " << currentProcess->getTAT() <<
                ", WT: " << currentProcess->getWT() <<", RT: "<<currentProcess->getRT()<< std::endl;
                // Remove the completed process from the queue
                processQueue.erase(processQueue.begin());
            }

            currentProcess = nullptr;
        } else {
            // If no processes to execute, advance the time
            std::cout << "No processes to execute. Advancing time." << std::endl;
            time1++;
        }
        std::cout << "Current Time: " << time1 << ", Queue size: " << processQueue.size() << std::endl;
    }
}

void Algorithm::RR(std::vector<Process*> processVector, int q, int& time1) {

    std::sort(processVector.begin(), processVector.end(), orderByPriorityATAndName);
    std::vector<Process*> processQueue;
    // Add processes to the queue if they have arrived

    while (!processVector.empty() || !processQueue.empty()) {
        for (auto it = processVector.begin(); it != processVector.end();) {
            if (time1 >= (*it)->getAT()) {
                std::cout << "Adding process to queue: " << (*it)->getName() << " at time " << time1
                          << " REM = " << (*it)->getRemTime() << std::endl;
                processQueue.push_back(*it);
                (*it)->setRemTime((*it)->getBT()); // Initialize remaining time
                it = processVector.erase(it); // Remove the process from pending processes
            } else {
                ++it; // Move to the next process if it hasn't arrived
            }
        }


        if (!processQueue.empty()) {
            Process* currentProcess = processQueue.front(); // Get the first process in the queue
            processQueue.erase(processQueue.begin()); // Remove the process from the queue
            std::cout << "Current process: " << currentProcess->getName()
                      << ", Remaining Time: " << currentProcess->getRemTime() << std::endl;
            if (currentProcess->getRT() == -1) {currentProcess->setRT(time1);}
            for (int i = 0; i < q && currentProcess->getRemTime() > 0; ++i) {
                currentProcess->setRemTime(currentProcess->getRemTime() - 1);
                time1++;
                std::cout << "Time advanced to " << time1 << std::endl;
                if(!processVector.empty()) {
                    // Add processes to the queue if they have arrived
                    for (auto it = processVector.begin(); it != processVector.end();) {
                        if (time1 >= (*it)->getAT()) {
                            std::cout << "Adding process to queue: " << (*it)->getName() << " at time " << time1
                                      << " REM = " << (*it)->getRemTime() << std::endl;
                            processQueue.push_back(*it);
                            (*it)->setRemTime((*it)->getBT()); // Initialize remaining time
                            it = processVector.erase(it); // Remove the process from pending processes
                        } else {
                            ++it; // Move to the next process if it hasn't arrived
                        }
                    }
                }
            }

            // Check if the process has finished
            if (currentProcess->getRemTime() == 0) {
                currentProcess->setCT(time1); // Set completion time
                std::cout << "Process " << currentProcess->getName()
                          << " completed at time " << time1 << std::endl;
                std::cout << "Metrics: " << std::endl << "CT: " << currentProcess->getCT() << ", TAT: " << currentProcess->getTAT() <<
                                ", WT: " << currentProcess->getWT() <<", RT: "<<currentProcess->getRT()<< std::endl;
            } else {
                // If not finished, re-add to the end of the queue
                processQueue.push_back(currentProcess);
                std::cout << "Process " << currentProcess->getName()
                          << " is not finished, remaining time: " << currentProcess->getRemTime()
                          << ". Re-adding to queue." << std::endl;
            }
        } else {
            // If no processes to execute, advance the time
            std::cout << "No processes to execute. Advancing time." << std::endl;
            time1++;
        }

        std::cout << "Current Time: " << time1 << ", Queue size: " << processQueue.size() << std::endl;
    }
}

void Algorithm::MLQ(std::vector<Process*> processVector, std::vector<std::string> queues, int q1, int q2, int q3) {
    std::vector<Process*> highPriorityQueue; // High priority queue
    std::vector<Process*> midPriorityQueue;  // Medium priority queue
    std::vector<Process*> lowPriorityQueue;  // Low priority queue

    int time1 = 0; // Current simulation time

    // Assign processes to their respective queues
    for (Process* process : processVector) {
        if (process->getQ() == 1) {
            highPriorityQueue.push_back(process);
        }
        else if (process->getQ() == 2) {
            midPriorityQueue.push_back(process);
        }
        else if (process->getQ() == 3) {
            lowPriorityQueue.push_back(process);
        }
        else {
            std::cout << "There are only 3 queues." << std::endl;
        }
    }

    // Execute the algorithm for the high priority queue
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
    } else if (queues[0] == "STCF") {
        std::cout << "Using Shortest Time to Complete First for high priority queue." << std::endl;
        STCF(highPriorityQueue, time1);
    }

    // Execute the algorithm for the mid priority queue
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
    } else if (queues[1] == "STCF") {
        std::cout << "Using Shortest Time to Complete First for mid priority queue." << std::endl;
        STCF(midPriorityQueue, time1);
    }

    // Execute the algorithm for the low priority queue
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
    } else if (queues[2] == "STCF") {
        std::cout << "Using Shortest Time to Complete First for low priority queue." << std::endl;
        STCF(lowPriorityQueue, time1);
    }
}

/**
 * @brief Calculates and returns average metrics for a list of processes.
 *
 * Averages are computed for Waiting Time (WT), Completion Time (CT),
 * Response Time (RT), and Turnaround Time (TAT). Results are printed
 * to the console and returned in a vector.
 *
 * @param processVector A vector of Process* objects.
 * @return std::vector<double> A vector containing the averages:
 *         [WT, CT, RT, TAT].
 */
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

