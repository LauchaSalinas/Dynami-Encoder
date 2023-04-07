#pragma once

#include <iostream>
#include "./abstractions/Mediator.h"
#include "./abstractions/State.h"

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class View_Reps : public State
{
public:
    void Button1ShortPress() override;
    void Button2ShortPress() override;
    void Button3ShortPress() override;
    void Button1LongPress() override;
    void Button2LongPress() override;
    void Button3LongPress() override;
};

class MenuSelectOptionState : public State
{
public:
    void Button1ShortPress() override;
    void Button2ShortPress() override;
    void Button3ShortPress() override;
    void Button1LongPress() override;
    void Button2LongPress() override;
    void Button3LongPress() override;
};

class Select_Chars : public State
{
public:
    void Button1ShortPress() override;
    void Button2ShortPress() override;
    void Button3ShortPress() override;
    void Button1LongPress() override;
    void Button2LongPress() override;
    void Button3LongPress() override;
};

class WeightInputState : public State
{
public:
    void Button1ShortPress() override;
    void Button2ShortPress() override;
    void Button3ShortPress() override;
    void Button1LongPress() override;
    void Button2LongPress() override;
    void Button3LongPress() override;
};

class IdleState : public State
{
public:
    void Button1ShortPress() override;
    void Button2ShortPress() override;
    void Button3ShortPress() override;
    void Button1LongPress() override;
    void Button2LongPress() override;
    void Button3LongPress() override;
};

// Reading
// MenuOpen(SelectOption)
// Iddle
// AvailableSSIDs(SelectOption)
// InputPassword(SelectChars)
// SetWeight(SelectNums)
// 