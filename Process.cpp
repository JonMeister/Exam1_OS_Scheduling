//
// Created by jonat on 04/10/2024.
//

#include "Process.h"

#include <string>

Process::Process(std::string name, int BT, int AT,int Q,int P) {
    this->name = name;
    this -> BT = BT;
    this -> AT = AT;
    this -> remTime=BT;
    this -> P = P;
    this -> Q = Q;
    this -> CT=0;
    this -> RT=-1;
    this -> WT=0;
}
std::string Process::getName() {return name;}
int Process::getBT() {return BT;}
int Process::getAT() {return AT;}
int Process::getCT() {return CT;}
int Process::getRT() {return RT;}
int Process::getWT() {return TAT-BT;}
int Process::getTAT() {return CT-AT;}
int Process::getRemTime() {return remTime;}
int Process::getP() {return P;}
int Process::getQ() {return Q;}



void Process::setCT(int CT) {this->CT = CT;}
void Process::setRT(int RT) {this->RT = RT;}
void Process::setTAT(int TAT) {this->TAT = TAT;}
void Process::setWT(int WT) {this->WT = WT;}
void Process::setRemTime(int remTime) {this -> remTime = remTime;}


