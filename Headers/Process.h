//
// Created by jonat on 04/10/2024.
//

#ifndef PROCESS_H
#define PROCESS_H
#include <string>


/**
 * @class Process
 * @brief A class representing a process with various scheduling attributes.
 *
 * This class encapsulates the attributes and behaviors of a process
 * in a scheduling simulation, including burst time, arrival time,
 * completion time, response time, waiting time, turnaround time,
 * remaining time, priority, and queue.
 */
class Process {
protected:
    std::string name; ///< The name of the process.
    int BT;          ///< Burst Time (BT) of the process.
    int AT;          ///< Arrival Time (AT) of the process.
    int CT;          ///< Completion Time (CT) of the process.
    int RT;          ///< Response Time (RT) of the process.
    int WT;          ///< Waiting Time (WT) of the process.
    int TAT;         ///< Turnaround Time (TAT) of the process.
    int remTime;     ///< Remaining Time of the process.
    int P;           ///< Priority of the process.
    int Q;           ///< Queue of the process.

public:
    /**
     * @brief Constructor to create a Process instance.
     *
     * @param name The name of the process.
     * @param BT Burst Time of the process.
     * @param AT Arrival Time of the process.
     * @param Q Queue of the process.
     * @param P Priority of the process.
     */
    Process(std::string name, int BT, int AT, int Q, int P);

    /**
     * @brief Gets the name of the process.
     *
     * @return The name of the process.
     */
    std::string getName();

    /**
     * @brief Gets the Burst Time (BT) of the process.
     *
     * @return The Burst Time of the process.
     */
    int getBT();

    /**
     * @brief Gets the Arrival Time (AT) of the process.
     *
     * @return The Arrival Time of the process.
     */
    int getAT();

    /**
     * @brief Gets the Completion Time (CT) of the process.
     *
     * @return The Completion Time of the process.
     */
    int getCT();

    /**
     * @brief Gets the Response Time (RT) of the process.
     *
     * @return The Response Time of the process.
     */
    int getRT();

    /**
     * @brief Gets the Waiting Time (WT) of the process.
     *
     * @return The Waiting Time of the process.
     */
    int getWT();

    /**
     * @brief Gets the Turnaround Time (TAT) of the process.
     *
     * @return The Turnaround Time of the process.
     */
    int getTAT();

    /**
     * @brief Gets the Remaining Time of the process.
     *
     * @return The Remaining Time of the process.
     */
    int getRemTime();

    /**
     * @brief Gets the Priority of the process.
     *
     * @return The Priority of the process.
     */
    int getP();

    /**
     * @brief Gets the Queue of the process.
     *
     * @return The Queue of the process.
     */
    int getQ();

    /**
     * @brief Sets the Completion Time (CT) of the process.
     *
     * @param CT The new Completion Time to set.
     */
    void setCT(int CT);

    /**
     * @brief Sets the Response Time (RT) of the process.
     *
     * @param RT The new Response Time to set.
     */
    void setRT(int RT);

    /**
     * @brief Sets the Remaining Time of the process.
     *
     * @param remTime The new Remaining Time to set.
     */
    void setRemTime(int remTime);

    /**
     * @brief Sets the Turnaround Time (TAT) of the process.
     *
     * @param TAT The new Turnaround Time to set.
     */
    void setTAT(int TAT);

    /**
     * @brief Sets the Waiting Time (WT) of the process.
     *
     * @param WT The new Waiting Time to set.
     */
    void setWT(int WT);
};



#endif //PROCESS_H
