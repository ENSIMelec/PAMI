#include "./MeEncoderNew.h"

MeEncoderNew moteurGauche(0x18, SLOT1);   //  motor at slot1
MeEncoderNew moteurDroit(0x18, SLOT2);   //  motor at slot2

void setup()
{
  moteurGauche.begin();
  moteurDroit.begin();
  Serial.begin(115200);
}

void loop()
{
  moteurGauche.runSpeed(-150);
  moteurDroit.runSpeed(50);
  delay(3000);
  moteurGauche.runSpeed(0);
  moteurDroit.runSpeed(0);
  delay(2000);
}