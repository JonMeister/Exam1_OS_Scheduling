//
// Created by jonat on 04/10/2024.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Process.h"
#include <queue>
#include <string>

class Algorithm {

public:
    Algorithm();
    ~Algorithm()=default;
    void FCFS(std::vector<Process*> processVector,int& time1);
    void SJF(std::vector<Process*> processVector,int& time1);
    void STCF(std::vector<Process*> processVector,int& time1);
    void RR(std::vector<Process*> processVector,int q,int& time1);
    void MLQ(std::vector<Process*> processes, int q, std::string highPriorityAlgorithm, std::string lowPriorityAlgorithm);
    void getAverage(std::vector<Process*> processVector);


};



#endif //ALGORITHM_H
