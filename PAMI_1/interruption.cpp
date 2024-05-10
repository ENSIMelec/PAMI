#include "interruption.h"
#include <Arduino.h>
#include "main.h"
#include "Motor.h"

float epsilonDistance = 2;
float epsilonAngle = PI / 180 / 2;
unsigned int interrupt_tick = 0;
float delta_recalage = 10;

float vitesse_D = 0;
float vitesse_G = 0;

bool angle_ok = false;
bool distance_ok = false;

long last_tick_gauche = 0;
long last_tick_droit = 0;
short count = 0;
/*************************************/
/*****FONCTION ÉCHANTILLONAGE*********/
/*************************************/
void Update_IT_callback(void) {
  /****Calcul des vitesses des moteurs*******/
  long tick_now_droit = tick_droit;
  long tick_now_gauche = tick_gauche;

  vitesse_D = (float)(tick_now_droit - last_tick_droit) * coefVitesseD*1.05;
  vitesse_G = (float)(tick_now_gauche - last_tick_gauche) * coefVitesseG;
  /******************************************/
  angle += (vitesse_D - vitesse_G) / 100;
  distance += (vitesse_D + vitesse_G) / 2 * dt;

  if (abs(distance) >= abs(cmd_distance) && angle != 0 && (!distance_ok || distance_ok && angle_ok)) {
    if (angle > 0) {
      cmd_vitesse_D -= 100;
      cmd_vitesse_G += 100;
    } else {
      cmd_vitesse_D -= 100;
      cmd_vitesse_G += 100;
    }
  }

  if (abs(distance) >= abs(cmd_distance) && !distance_ok) {
    if (cmd_angle > 0) {
      cmd_vitesse_G = -400;
      cmd_vitesse_D = 400;
    } else {
      cmd_vitesse_G = 400;
      cmd_vitesse_D = -400;
    }
    angle = 0;
    distance_ok = true;

  } else if (abs(angle) >= abs(cmd_angle) && !angle_ok && distance_ok) {
    cmd_vitesse_G = 0;
    cmd_vitesse_D = 0;
    distance = 0;
    cmd_distance = 10000;
    cmd_vitesse_G = 1000;
    cmd_vitesse_D = 1000;
    angle_ok = true;
  } else if (abs(distance) >= abs(cmd_distance) && angle_ok && distance_ok) {
    cmd_vitesse_G = 0;
    cmd_vitesse_D = 0;
  }

  /****Calcul des PID Vitesse*******/
  PID_vitesse_G.Compute();
  PID_vitesse_D.Compute();
  /*********************************/

  /****Commande des moteurs ajout avec une deadzone*******/
  moteur_droit_direction((Output_PID_vitesse_D >= 0));
  moteur_gauche_direction((Output_PID_vitesse_G >= 0));

  if (abs(Output_PID_vitesse_G) > 10)
    analogWrite(PWM_G, abs(Output_PID_vitesse_G));
  else
    analogWrite(PWM_G, 0);

  if (abs(Output_PID_vitesse_D) > 10)
    analogWrite(PWM_D, abs(Output_PID_vitesse_D));
  else
    analogWrite(PWM_D, 0);
  /*****************************/

  /****Sauvegarde des positions*****/
  last_tick_gauche = tick_now_gauche;
  last_tick_droit = tick_now_droit;
  /********************************/
  // Serial.print("diff: ");
  // Serial.println(vitesse_D);
  // Serial.println(vitesse_G);
  // Serial.print("angle:");
  // Serial.println(angle);
  // Serial.print("distance");
  // Serial.println(distance);
  Update_IT = true;
}
/*************************************/
/*************************************/
/*************************************/


void Stop_match_callback() {
  cmd_vitesse_G = 0;
  cmd_vitesse_D = 0;
  Serial.println("Stop du temps");
  analogWrite(PWM_G, 0);
  analogWrite(PWM_D, 0);
  while (1)
    ;
}

void handleEncoderDroit() {
  if (digitalRead(CodDB) == digitalRead(CodDA)) {
    tick_droit++;
  } else {
    tick_droit--;
  }
}

void handleEncoderGauche() {
  if (digitalRead(CodGB) == digitalRead(CodGA)) {
    tick_gauche++;
  } else {
    tick_gauche--;
  }
}