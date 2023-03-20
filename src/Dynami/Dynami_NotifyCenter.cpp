
#include "Dynami_NotifyCenter.h"

Dynami_NotifyCenter::Dynami_NotifyCenter()
{
}

void Dynami_NotifyCenter::notifyCenterSetup()
{
  Serial.begin(115200);
  Serial.println("Dinamy Started");
}

void Dynami_NotifyCenter::debugPrint(const char *str)
{
  Serial.println(str);
}

void Dynami_NotifyCenter::debugPrint(char *str, long vl)
{
  Serial.print(str);
  Serial.println(vl);
}

void Dynami_NotifyCenter::debugPrint(char *str, int vl)
{
  Serial.print(str);
  Serial.println(vl);
}


void Dynami_NotifyCenter::debugPrint(int vl)
{
  Serial.println(vl);
}

void Dynami_NotifyCenter::debugPrint(String str)
{
  Serial.println(str);
}

void Dynami_NotifyCenter::SerialNotifyNewRep(int sets, int actualRep, int targetRep, long maxEncodedValue, long encoderValue, int tiempoTotal, int tiempoPicoTotal, int tiempoRetorno, char *velocity)
{
  Serial.print("SET: ");
  Serial.print(sets);
  Serial.print(" REP: ");
  Serial.print(actualRep);
  Serial.print("/");
  Serial.println(targetRep);
  Serial.print("Max Valor: ");
  Serial.println(maxEncodedValue);
  Serial.print("Valor final: ");
  Serial.println(encoderValue);
  Serial.print("Tiempo Total: ");
  Serial.println(tiempoTotal);
  Serial.print("Tiempo Pico: ");
  Serial.print(tiempoPicoTotal);
  Serial.print("\t Tiempo Retorno: ");
  Serial.println(tiempoRetorno);
  Serial.print("Velocidad: ");
  Serial.println(velocity);
  Serial.println();
}
