#ifndef Dynami_MediatedComponent_h
#define Dynami_MediatedComponent_h


#include "Dynami_Mediator.h"
/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */

class Dynami_Mediator;
class MediatedComponent
{
public:
    Dynami_Mediator *dynamiMediator;
    void set_mediator(Dynami_Mediator *mediator)
    {
        this->dynamiMediator = mediator;
    }
};

#endif