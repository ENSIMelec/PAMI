#include "./MeEncoderNew.h"

MeEncoderNew motor1(0x18, SLOT1);   //  motor at slot1
MeEncoderNew motor2(0x18, SLOT2);   //  motor at slot2

void setup()
{
  motor1.begin();
  motor2.begin();
  Serial.begin(115200);
}

void loop()
{
  motor1.runSpeed(-150);
  motor2.runSpeed(50);
  delay(3000);
  motor1.runSpeed(0);
  motor2.runSpeed(0);
  delay(2000);
}