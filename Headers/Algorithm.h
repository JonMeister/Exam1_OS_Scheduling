//
// Created by jonat on 04/10/2024.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Process.h"
#include <queue>
#include <string>

/**
 * @class Algorithm
 * @brief A class for implementing various scheduling algorithms for processes.
 *
 * This class provides methods for different scheduling algorithms such as
 * First Come First Served (FCFS), Shortest Job First (SJF), Shortest Time to Completion First (STCF),
 * Round Robin (RR), and Multi-Level Queue (MLQ) scheduling.
 */
class Algorithm {
public:
    /**
     * @brief Default constructor for the Algorithm class.
     *
     * Initializes an instance of the Algorithm class.
     */
    Algorithm();

    /**
     * @brief Default destructor for the Algorithm class.
     */
    ~Algorithm() = default;

    /**
     * @brief Executes the First Come First Served (FCFS) scheduling algorithm.
     *
     * @param processVector A vector of pointers to Process objects to be scheduled.
     * @param time1 Reference to an integer representing the current time.
     */
    void FCFS(std::vector<Process*> processVector, int& time1);

    /**
     * @brief Executes the Shortest Job First (SJF) scheduling algorithm.
     *
     * @param processVector A vector of pointers to Process objects to be scheduled.
     * @param time1 Reference to an integer representing the current time.
     */
    void SJF(std::vector<Process*> processVector, int& time1);

    /**
     * @brief Executes the Shortest Time to Completion First (STCF) scheduling algorithm.
     *
     * @param processVector A vector of pointers to Process objects to be scheduled.
     * @param time1 Reference to an integer representing the current time.
     */
    void STCF(std::vector<Process*> processVector, int& time1);

    /**
     * @brief Executes the Round Robin (RR) scheduling algorithm.
     *
     * @param processVector A vector of pointers to Process objects to be scheduled.
     * @param q An integer representing the quantum time for the RR algorithm.
     * @param time1 Reference to an integer representing the current time.
     */
    void RR(std::vector<Process*> processVector, int q, int& time1);

    /**
     * @brief Executes the Multi-Level Queue (MLQ) scheduling algorithm.
     *
     * @param processes A vector of pointers to Process objects to be scheduled.
     * @param queues A vector of strings representing the queue types for scheduling.
     * @param q1 An integer representing the quantum time for the first queue.
     * @param q2 An integer representing the quantum time for the second queue.
     * @param q3 An integer representing the quantum time for the third queue.
     */
    void MLQ(std::vector<Process*> processes, std::vector<std::string> queues, int q1, int q2, int q3);

    /**
     * @brief Calculates the average metrics for the given processes.
     *
     * @param processVector A vector of pointers to Process objects for which to calculate averages.
     * @return A vector of doubles containing the average Wait Time (WT), Completion Time (CT),
     *         Response Time (RT), and Turnaround Time (TAT).
     */
    std::vector<double> getAverage(std::vector<Process*> processVector);

};



#endif //ALGORITHM_H
