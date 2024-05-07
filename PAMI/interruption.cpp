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

/*************************************/
/*****FONCTION ÉCHANTILLONAGE*********/
/*************************************/
void Update_IT_callback(void) {
  Update_IT = true;
}
/*************************************/
/*************************************/
/*************************************/

void Update_callback() {

  /****Calcul des vitesses des moteurs*******/
  long tick_now_droit = tick_droit;
  long tick_now_gauche = tick_gauche;

  vitesse_D = (float)(tick_now_droit - last_tick_droit) * coefVitesseD;
  vitesse_G = (float)(tick_now_gauche - last_tick_gauche) * coefVitesseG;
  /******************************************/
  angle += (vitesse_D - vitesse_G) / 2000;  // /98
  distance += (vitesse_D + vitesse_G) / 2 * dt * 0.6;

  if (abs(distance) >= abs(cmd_distance) && !distance_ok) {
    cmd_vitesse_G = 0;
    cmd_vitesse_D = 0;
    delay(100);
    cmd_vitesse_G = -1000;
    cmd_vitesse_D = 1000;
    distance_ok = true;
  } else if (abs(angle) >= abs(cmd_angle) && !angle_ok && distance_ok) {
    cmd_vitesse_G = 0;
    cmd_vitesse_D = 0;
    delay(100);
    distance = 0;
    cmd_distance = 500;
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
  interval_sensor++;
  Update_IT = false;
}

void Stop_match_callback() {
  MyTim->detachInterrupt();
  Output_PID_vitesse_D = 0;
  Output_PID_vitesse_G = 0;
  Serial.println("Stop du temps");
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