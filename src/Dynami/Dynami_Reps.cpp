#include "Dynami_Reps.h"

Dynami_Reps::Dynami_Reps()
{
}

void Dynami_Reps::AddNewRep(double newRepMPV, double newRepMV, double newRepPV, double newRepROM, unsigned int newRepPower)
{
    rep newRep = {newRepMPV, newRepMV, newRepPV, newRepROM, newRepPower};
    repCounter++;
    this->repVector.push_back(newRep);
    CalculateBestRep(newRep, true);
    CalculateMeanRep(newRep, true);
    return;
}
void Dynami_Reps::AddNewRep(rep newRep)
{
    repCounter++;
    this->repVector.push_back(newRep);
    CalculateBestRep(newRep, true);
    CalculateMeanRep(newRep, true);
    return;
}

void Dynami_Reps::DeleteRep(unsigned int index)
{
    if (index > repCounter)
        return;
    repCounter--;
    rep repToDelete = repVector[index];
    this->repVector.erase(repVector.begin() + index);
    if (index == 0)
    {
        bestRep = {0, 0, 0, 0, 0};
        meanRep = {0, 0, 0, 0, 0};
    }
    else
    {
        CalculateBestRep(repToDelete, false);
        CalculateMeanRep(repToDelete, false);
    }
    return;
}

void Dynami_Reps::DeleteAllReps(void)
{
    this->repVector.clear();
    repCounter = -1;
    bestRep = {0, 0, 0, 0, 0};
    meanRep = {0, 0, 0, 0, 0};
    return;
}

rep Dynami_Reps::GetRepInfo(unsigned int index)
{
    if (index > repCounter)
        return rep{0, 0, 0, 0};
    return repVector[index];
}

void Dynami_Reps::CalculateBestRep(rep targetRep, bool newRep)
{
    if (newRep)
    {
        if (targetRep.MPV > bestRep.MPV)
            bestRep.MPV = targetRep.MPV;
        if (targetRep.MV > bestRep.MV)
            bestRep.MV = targetRep.MV;
        if (targetRep.PV > bestRep.PV)
            bestRep.PV = targetRep.PV;
        if (targetRep.ROM > bestRep.ROM)
            bestRep.ROM = targetRep.ROM;
        if (targetRep.Power > bestRep.Power)
            bestRep.Power = targetRep.Power;
    }
    else
    {
        if (targetRep.MPV == bestRep.MPV ||
            targetRep.MV == bestRep.MV ||
            targetRep.PV == bestRep.PV ||
            targetRep.ROM == bestRep.ROM ||
            targetRep.Power == bestRep.Power)
        {
            for (rep &repElement : repVector)
            {
                if (repElement.MPV > bestRep.MPV)
                    bestRep.MPV = repElement.MPV;
                if (repElement.MV > bestRep.MV)
                    bestRep.MV = repElement.MV;
                if (repElement.PV > bestRep.PV)
                    bestRep.PV = repElement.PV;
                if (repElement.ROM > bestRep.ROM)
                    bestRep.ROM = repElement.ROM;
                if (repElement.Power > bestRep.Power)
                    bestRep.Power = repElement.Power;
            }
        }
    }
}

void Dynami_Reps::CalculateMeanRep(rep targetRep, bool newRep)
{
    if (newRep)
    {
        meanRep.MPV = (meanRep.MPV * repCounter + targetRep.MPV) / (repCounter + 1);
        meanRep.MV = (meanRep.MV * repCounter + targetRep.MV) / (repCounter + 1);
        meanRep.PV = (meanRep.PV * repCounter + targetRep.PV) / (repCounter + 1);
        meanRep.ROM = (meanRep.ROM * repCounter + targetRep.ROM) / (repCounter + 1);
        meanRep.Power = (meanRep.Power * repCounter + targetRep.Power) / (repCounter + 1);
    }
    // for delete
    else
    {
        meanRep.MPV = (meanRep.MPV * (repCounter + 1) - targetRep.MPV) / repCounter;
        meanRep.MV = (meanRep.MV * (repCounter + 1) - targetRep.MV) / repCounter;
        meanRep.PV = (meanRep.PV * (repCounter + 1) - targetRep.PV) / repCounter;
        meanRep.ROM = (meanRep.ROM * (repCounter + 1) - targetRep.ROM) / repCounter;
        meanRep.Power = (meanRep.Power * (repCounter + 1) - targetRep.Power) / repCounter;
    }
}