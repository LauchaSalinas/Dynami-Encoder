#include "Dynami_States.h"

void View_Reps::Button1ShortPress()
{
    Serial.println("ConcreteStateA handles request1.");
    context_->PrevRep();
}

void View_Reps::Button2ShortPress()
{
    Serial.println("ConcreteStateA handles request2.");
    context_->programRepCancelled();
}
void View_Reps::Button3ShortPress()
{
    Serial.println("ConcreteStateA handles request3.");
    context_->NextRep();
}
void View_Reps::Button1LongPress() { context_->OpenMainMenu(); };
void View_Reps::Button2LongPress() { context_->ResetRepVector(); };
void View_Reps::Button3LongPress() { context_->SwapMainParameter(); };

void MenuSelectOptionState::Button1ShortPress()
{
    Serial.println("ConcreteStateB handles request1.");
    context_->PrevOption();
}
void MenuSelectOptionState::Button2ShortPress()
{
    Serial.println("ConcreteStateB handles request2.");
    context_->SelectOptionMainMenu();
}
void MenuSelectOptionState::Button3ShortPress()
{
    Serial.println("ConcreteStateB handles request3.");
    context_->NextOption();
}
void MenuSelectOptionState::Button1LongPress(){};
void MenuSelectOptionState::Button2LongPress(){};
void MenuSelectOptionState::Button3LongPress(){};

void Select_Chars::Button1ShortPress()
{
    Serial.println("ConcreteStateC handles request1.");
    context_->PrevChar();
}
void Select_Chars::Button2ShortPress()
{
    context_->SelectChar();
    Serial.println("ConcreteStateC handles request2.");
}
void Select_Chars::Button3ShortPress()
{
    context_->NextChar();
    Serial.println("ConcreteStateC handles request2.");
}
void Select_Chars::Button1LongPress(){};
void Select_Chars::Button2LongPress(){context_->ConfirmString();};
void Select_Chars::Button3LongPress(){};

void WeightInputState::Button1ShortPress()
{
    Serial.println("WeightInputState handles request1.");
    context_->PrevNumber();
}
void WeightInputState::Button2ShortPress()
{
    Serial.println("WeightInputState handles request2.");
    context_->SelectNumber();
}

void WeightInputState::Button3ShortPress()
{
    Serial.println("WeightInputState handles request3.");
    context_->NextNumber();
}
void WeightInputState::Button1LongPress(){};
void WeightInputState::Button2LongPress(){};
void WeightInputState::Button3LongPress(){};

void IdleState::Button1ShortPress(){};
void IdleState::Button2ShortPress(){};
void IdleState::Button3ShortPress(){};
void IdleState::Button1LongPress(){};
void IdleState::Button2LongPress(){};
void IdleState::Button3LongPress(){};