
#include "main.h"
#include "Motor.h"
#include "interruption.h"

volatile long tick_droit = 0;
volatile long tick_gauche = 0;
volatile bool Update_IT = false;

float angle = 0;
float distance = 0;

const float dt = 100e-3;
const float MATCH_TIME = 10;

const float wheel_perimeter = PI * 69.2;
float coefVitesseG = wheel_perimeter / 960.0 / dt;
float coefVitesseD = wheel_perimeter / 960.0 / dt;

float Output_PID_vitesse_G = 0;  // Valeur sortante du PID vitesse moteur gauche, une PMW donc
float Output_PID_vitesse_D = 0;  // Valeur sortante du PID vitesse moteur droit, une PMW donc
float cmd_vitesse_G = 0;         // commande vitesse moteur gauche en mm/ms
float cmd_vitesse_D = 0;

float Kp_G = 0.51, Ki_G =0.5, Kd_G = 0;  // coefficients PID vitesse moteur gauche
float Kp_D = 0.51, Ki_D = 0.5, Kd_D = 0;  // coefficients PID vitesse moteur droit

PID PID_vitesse_G(&vitesse_G, &Output_PID_vitesse_G, &cmd_vitesse_G, dt, Kp_G, Ki_G, Kd_G, DIRECT);
PID PID_vitesse_D(&vitesse_D, &Output_PID_vitesse_D, &cmd_vitesse_D, dt, Kp_D, Ki_D, Kd_D, DIRECT);

void setup() {
  Serial.begin(115200);

  pinMode(PWM_D, OUTPUT);
  pinMode(DIR_D_1, OUTPUT);
  pinMode(DIR_D_2, OUTPUT);

  pinMode(PWM_G, OUTPUT);
  pinMode(DIR_G_1, OUTPUT);
  pinMode(DIR_G_2, OUTPUT);

  pinMode(CodDB, INPUT_PULLUP);
  pinMode(CodDA, INPUT_PULLUP);
  pinMode(CodGB, INPUT_PULLUP);
  pinMode(CodGA, INPUT_PULLUP);

  // digitalWrite(DIR_G_1, LOW);
  // digitalWrite(DIR_G_1, LOW);
  // digitalWrite(DIR_D_1, LOW);
  // digitalWrite(DIR_D_2, LOW);

  //PID_vitesse_D.SetOutputLimits(-255, 255, 10);
  //PID_vitesse_G.SetOutputLimits(-255, 255, 10);

  attachInterrupt(digitalPinToInterrupt(CodDB), handleEncoderDroit, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CodGB), handleEncoderGauche, CHANGE);

  /******Initialisation de l'interruption pour l'échantillonnage************/
  TIM_TypeDef *Instance = TIM6;
  HardwareTimer *MyTim = new HardwareTimer(Instance);
  MyTim->setOverflow(1 / dt, HERTZ_FORMAT);
  MyTim->attachInterrupt(Update_IT_callback);
  MyTim->resume();
  /**************************************************************************/

  // /******interruption pour début match************/
  // TIM_TypeDef *Instance = TIM7;
  // HardwareTimer *MyTim = new HardwareTimer(Instance);
  // MyTim->setOverflow(1 / MATCH_TIME, HERTZ_FORMAT);
  // MyTim->attachInterrupt(Stop_match_callback);
  // MyTim->resume();
  // /**************************************************************************/

  PID_vitesse_D.SetMode(AUTOMATIC);
  PID_vitesse_G.SetMode(AUTOMATIC);
}

void loop() {
  if (Update_IT) {
    Update_callback();
  }




  
}
