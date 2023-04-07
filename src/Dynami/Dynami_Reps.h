#ifndef Dynami_Reps_h
#define Dynami_Reps_h

// #include "Dynami_Mediator.h"
// class Dynami_Mediator; // probably not neccesary
#include <vector>
#include "./resources/Rep.h"

class Dynami_Reps
{
public:
    Dynami_Reps();
    void AddNewRep(double newRepMPV, double newRepMV, double newRepPV, double newRepROM, unsigned int newRepPower);
    void AddNewRep(rep newRep);
    void DeleteRep(unsigned int index);
    void DeleteAllReps();
    rep GetRepInfo(unsigned int index);
    int GetRepCounter() { return this->repCounter; }
    rep GetRepMean(){return meanRep;}
    rep GetRepBest(){return bestRep;}

private:
    std::vector<rep> repVector;
    rep bestRep = {0, 0, 0, 0, 0};
    rep meanRep = {0, 0, 0, 0, 0};
    int repCounter = -1;
    void CalculateBestRep(rep targetRep, bool newRep);
    void CalculateMeanRep(rep targetRep, bool newRep);
};

#endif // #define Dynami_Rep_h