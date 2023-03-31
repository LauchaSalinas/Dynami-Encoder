#include "Dynami_Display.h"

Dynami_Display::Dynami_Display()
{
}

void Dynami_Display::setEnergySaveRef(Dynami_EnergySave *esref)
{
  dynamiEnergySave = esref;
}

void Dynami_Display::displaySetup()
{
  delay(250);                         // wait for the OLED to power up
  display.begin(i2c_Address, true);   // Address 0x3C default
  display.clearDisplay();             // Vaciamos el contenido de la pantalla
  display.setTextSize(2);             // Elegimos el tamaño del texto a 2
  display.setTextColor(SH110X_WHITE); // Color del texto blanco
  display.setCursor(0, 0);            // Colocamos el cursor al principio
  display.println("DYNAMI");          // Mostramos un texto
  display.setTextSize(1);             // Cambiamos el tamaño del texto a 1
  display.println(" ");
  display.println("SE TU MEJOR VERSION");
  display.display(); // Encendemos la pantalla con todo lo anterior
  display.clearDisplay();
  display.setCursor(0, 0);   // Colocamos el cursor al principio
  display.println("READY!"); // Mostramos un texto
  display.display();
  // displayBT();
  // display.setFont(&FreeMonoBold12pt7b);
  displayTemplate();
}

void Dynami_Display::displayLoop()
{
  // Charging battery routine

  batteryDisplayStatusChanged();
  if (boolDisplayBatteryCharging)
    displayBatteryChargingService();
}

void Dynami_Display::displayTemplate()
{
  display.clearDisplay();
  display.display();

  display.setTextColor(SH110X_WHITE);

  // POT
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.print("---");

  display.setCursor(25, 25);
  display.setTextSize(1);
  display.print("POT");

  // REP
  display.setCursor(76, 0);
  display.setTextSize(1);
  display.print("0/1");

  // ROM
  display.setCursor(80, 16);
  display.setTextSize(1);
  display.print("---");

  display.setCursor(80, 25);
  display.setTextSize(1);
  display.print("ROM");

  // PV
  display.setCursor(0, 35);
  display.setTextSize(1);
  display.print("---");

  display.setCursor(10, 44);
  display.setTextSize(1);
  display.print("PKV");

  // MV
  display.setCursor(40, 35);
  display.setTextSize(1);
  display.print("---");
  display.setCursor(50, 44);
  display.setTextSize(1);
  display.print("MV");

  // MPV
  display.setCursor(80, 35);
  display.setTextSize(1);
  display.print("---");

  display.setCursor(85, 44);
  display.setTextSize(1);
  display.print("MPV");

  // OPTIONS

  display.setCursor(0, 57);
  display.setTextSize(1);
  display.print("RSET");

  display.setCursor(45, 57);
  display.setTextSize(1);
  display.print("PREV");

  display.setCursor(85, 57);
  display.setTextSize(1);
  display.print("NEXT");

  display.display();
  // displayRep();
  displayBattery();
  displayArrow();
}

void Dynami_Display::displayMPV(double MPV)
{
  display.fillRect(80, 35, 25, 7, 0);
  display.setCursor(80, 35);
  display.setTextSize(1);
  display.printf("%4.2f", MPV);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayMV(double MV)
{
  display.fillRect(40, 35, 25, 7, 0);
  display.setCursor(40, 35);
  display.setTextSize(1);
  display.printf("%4.2f", MV);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayPV(double PV)
{
  display.fillRect(0, 35, 25, 7, 0);
  display.setCursor(0, 35);
  display.setTextSize(1);
  display.printf("%4.2f", PV);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayRep(unsigned int reps, unsigned int totalReps)
{
  repPosition = reps;
  display.fillRect(76, 0, 30, 7, 0);
  display.setCursor(76, 0);
  display.setTextSize(1);
  if (reps <= totalReps)
  {
    display.printf("%02d/%02d", reps, totalReps);
  }
  if (reps == totalReps+ 1)
  {
    display.printf("%s", "BEST");
  }
  if (reps == totalReps+ 2)
  {
    display.printf("%s", "MEAN");
  }

  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayROM(double ROM)
{
  display.fillRect(80, 16, 25, 7, 0);
  display.setCursor(80, 16);
  display.setTextSize(1);
  display.printf("%4.1f", ROM);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayPower(double Power)
{
  display.fillRect(0, 0, 60, 25, 0);
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.printf("%3.0f", Power);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::turnOFFDisplay()
{
  display.clearDisplay();
  display.display();
}

void Dynami_Display::turnONDisplay()
{
  displayTemplate();
}

void Dynami_Display::displayBT()
{
  display.drawBitmap(114, 0, bt_icon, LOGO16_WIDTH, LOGO16_HEIGHT, 1);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayBTOFF()
{
  display.fillRect(114, 0, LOGO16_WIDTH, LOGO16_HEIGHT, 0);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayEmptyBattery()
{
  display.drawFastHLine(117, 22, 6, 1);
  display.drawRect(114, 23, 12, 18, 1);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::clearBatteryIcon()
{ // check this function should be in more places
  display.fillRect(114, 22, 12, 19, 0);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::clearBatteryCells()
{ // check this function should be in more places
  display.fillRect(115, 24, 10, 16, 0);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayBatteryNotCharging()
{
  int cellsQty = 3; // int cellsQty = dynami.getCellsQty(); // NEEDS REFACTOR
  for (int i = 0; i < cellsQty; i++)
  {
    display.drawFastHLine(117, 37 - (i * 3), 6, 1);
    display.drawFastHLine(117, 38 - (i * 3), 6, 1);
  }
  dynamiEnergySave->energySaveModeDisplay();
}

void blinkLastCell()
{
}

void Dynami_Display::displayBatteryCharging()
{
  chargingCellsQty++;
  if (chargingCellsQty >= 6)
  {
    chargingCellsQty = 1;
    clearBatteryCells();
  }
  for (int i = 0; i < chargingCellsQty; i++)
  {
    display.drawFastHLine(117, 37 - (i * 3), 6, 1);
    display.drawFastHLine(117, 38 - (i * 3), 6, 1);
  }
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayBatteryChargingService()
{
  if (millis() > batteryCellBlinkLastCheckTime + blinkTime)
  {
    displayBatteryCharging();
    batteryCellBlinkLastCheckTime = millis();
  }
}

void Dynami_Display::batteryDisplayStatusChanged()
{
  if (boolDisplayBatteryCharging != boolDisplayBatteryChargingLast)
  {
    displayBattery();
    boolDisplayBatteryChargingLast = boolDisplayBatteryCharging;
  }
}

void Dynami_Display::setDisplayBatteryCharging(bool b)
{
  boolDisplayBatteryCharging = b;
}

void Dynami_Display::displayBattery()
{
  clearBatteryIcon();
  displayEmptyBattery();
  if (boolDisplayBatteryCharging)
  {
    chargingCellsQty = 0; // sets cell at 0 so it starts charging from the bottom
    displayBatteryCharging();
  }
  else
  {
    displayBatteryNotCharging();
  }
}

void Dynami_Display::displayArrowChanged()
{
  clearArrow();
  displayArrow();
}

void Dynami_Display::clearArrow()
{
  display.fillRect(114, 45, 127, 63, 0);
  dynamiEnergySave->energySaveModeDisplay();
}

void Dynami_Display::displayArrow()
{
  bool directionUp = dynamiMediator->getArrowDirectionUp(); // NEEDS REFACTOR

  int x, y, d;
  if (!directionUp)
  {
    x = 114;
    y = 45;
    d = 1;
  }
  else
  {
    x = 125;
    y = 64;
    d = -1;
  }

  // DIRECTION

  int offd = 0;

  for (int i = 0; i < 3; i++)
  {
    int drawLenght = 2;
    if (d == -1)
      offd = -drawLenght;
    display.drawFastVLine((0 * d) + x, 0 * d + y + offd + (i * d * 6), drawLenght, 1);
    drawLenght = 3;
    if (d == -1)
      offd = -drawLenght;
    display.drawFastVLine((1 * d) + x, 0 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((2 * d) + x, 1 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((3 * d) + x, 2 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((4 * d) + x, 3 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((5 * d) + x, 4 * d + y + offd + (i * d * 6), drawLenght, 1);
    drawLenght = 2;
    if (d == -1)
      offd = -drawLenght;
    display.drawFastVLine((0 + 11) * d + x, 0 * d + y + offd + (i * d * 6), drawLenght, 1);
    drawLenght = 3;
    if (d == -1)
      offd = -drawLenght;
    display.drawFastVLine((-1 + 11) * d + x, 0 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((-2 + 11) * d + x, 1 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((-3 + 11) * d + x, 2 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((-4 + 11) * d + x, 3 * d + y + offd + (i * d * 6), drawLenght, 1);
    display.drawFastVLine((-5 + 11) * d + x, 4 * d + y + offd + (i * d * 6), drawLenght, 1);
  }
  dynamiEnergySave->energySaveModeDisplay();
}
