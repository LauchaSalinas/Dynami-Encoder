#include "Dynami_Buttons.h"

Dynami_Buttons::Dynami_Buttons() : button1(PIN_BUTTON1), button2(PIN_BUTTON2) {}

void Dynami_Buttons::buttonsSetup()
{
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void Dynami_Buttons::buttonsLoop()
{
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first

  if (button1.isPressed())
  {
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  }

  if (button2.isPressed())
  {
    pressedTim = millis();
    isPressin = true;
    isLongDetecte = false;
  }
  shortPressL();
  shortPressR();
  longPressL();
  longPressR();
}

bool Dynami_Buttons::shortPressL()
{
  if (button1.isReleased())
  {
    isPressing = false;
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if (pressDuration < SHORT_PRESS_TIME)
      dynamiMediator->button1ShortPress();
    return true;
  }
  return false;
}

bool Dynami_Buttons::shortPressR()
{
  if (button2.isReleased())
  {
    isPressin = false;
    releasedTim = millis();

    long pressDuratio = releasedTim - pressedTim;

    if (pressDuratio < SHORT_PRESS_TIME)
      dynamiMediator->button2ShortPress();
    return true;
  }
  return false;
}

bool Dynami_Buttons::longPressL()
{
  if (isPressing == true && isLongDetected == false)
  {
    long pressDuration = millis() - pressedTime;

    if (pressDuration > LONG_PRESS_TIME)
    {
      isLongDetected = true;
      dynamiMediator->button1LongPress();
      return true;
    }
  }
  return false;
}

bool Dynami_Buttons::longPressR()
{
  if (isPressin == true && isLongDetecte == false)
  {
    long pressDuratio = millis() - pressedTim;

    if (pressDuratio > LONG_PRESS_TIME)
    {
      isLongDetecte = true;
      dynamiMediator->button2LongPress();
      return true;
    }
  }
  return false;
}
