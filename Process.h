//
// Created by jonat on 04/10/2024.
//

#ifndef PROCESS_H
#define PROCESS_H
#include <string>


class Process {
protected:
    std::string name;
    int BT;
    int AT;
    int CT;
    int RT;
    int WT;
    int TAT;
    int remTime;
    int P;
    int Q;
public:
    Process(std::string name, int BT, int AT,int Q,int P);
    std::string getName();

    int getBT();
    int getAT();
    int getCT();
    int getRT();
    int getWT();
    int getTAT();
    int getRemTime();
    int getP();
    int getQ();

    void setCT(int CT);
    void setRT(int RT);
    void setRemTime(int remTime);
    void setTAT(int TAT);
    void setWT(int WT);

};



#endif //PROCESS_H
