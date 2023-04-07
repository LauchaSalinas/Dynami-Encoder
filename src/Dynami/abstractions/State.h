#pragma once
#include <iostream>

#include "./../Dynami_Mediator.h"

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */

class Dynami_Mediator;

class State
{
public:

    virtual ~State()
    {
    }

    virtual void Button1ShortPress() = 0;
    virtual void Button2ShortPress() = 0;
    virtual void Button3ShortPress() = 0;
    virtual void Button1LongPress() = 0;
    virtual void Button2LongPress() = 0;
    virtual void Button3LongPress() = 0;

    void set_context(Dynami_Mediator *context)
    {
        context_ = context;
    }

protected:
    Dynami_Mediator *context_;
};