#include "./MeEncoderNew.h"

MeEncoderNew motor1(0x18, SLOT1);   //  motor at slot1
MeEncoderNew motor2(0x18, SLOT2);   //  motor at slot2

void setup()
{
  motor1.begin();
  motor2.begin();
  Serial.begin(115200);


  // Créer des variables pour stocker les valeurs des PID de vitesse
  float p1, i1, d1;
  float p2, i2, d2;

  // Appeler la fonction pour obtenir les PID de vitesse du premier moteur
  motor1.getSpeedPID(&p1, &i1, &d1);

  // Appeler la fonction pour obtenir les PID de vitesse du deuxième moteur
  motor2.getSpeedPID(&p2, &i2, &d2);

  // Afficher les valeurs des PID de vitesse pour chaque moteur
  Serial.println("PID Speed Motor 1:");
  Serial.print("P: "); Serial.println(p1);
  Serial.print("I: "); Serial.println(i1);
  Serial.print("D: "); Serial.println(d1);

  Serial.println("PID Speed Motor 2:");
  Serial.print("P: "); Serial.println(p2);
  Serial.print("I: "); Serial.println(i2);
  Serial.print("D: "); Serial.println(d2);
}

void loop()
{
  motor2.moveTo(360, 200);
  motor1.moveTo(360, 200);
  delay(5000);
  motor2.moveTo(0, 0);
  motor1.moveTo(0, 0);
  delay(10000);
}
