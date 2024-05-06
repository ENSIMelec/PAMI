#include "main.h"
#include "Motor.h"
#include "interruption.h"
#include <HCSR04.h>
#include <Servo.h>

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

float Output_PID_vitesse_G = 0; // Valeur sortante du PID vitesse moteur gauche, une PMW donc
float Output_PID_vitesse_D = 0; // Valeur sortante du PID vitesse moteur droit, une PMW donc
float cmd_vitesse_G = 0;        // commande vitesse moteur gauche en mm/ms
float cmd_vitesse_D = 0;

float Kp_G = 0.7, Ki_G = 0, Kd_G = 0; // coefficients PID vitesse moteur gauche
float Kp_D = 0.9, Ki_D = 0, Kd_D = 0; // coefficients PID vitesse moteur droit

int interval_sensor = 0; // Interval de mesure de la distance (100 ms)
bool strat;
UltraSonicDistanceSensor distanceSensor(A6, A3);

Servo myservo; // create servo object to control a servo

PID PID_vitesse_G(&vitesse_G, &Output_PID_vitesse_G, &cmd_vitesse_G, dt, Kp_G, Ki_G, Kd_G, DIRECT);
PID PID_vitesse_D(&vitesse_D, &Output_PID_vitesse_D, &cmd_vitesse_D, dt, Kp_D, Ki_D, Kd_D, DIRECT);

HardwareTimer *MyTim;

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial begin");
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

  pinMode(jack_pin, INPUT_PULLUP);
  pinMode(strat_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CodDB), handleEncoderDroit, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CodGB), handleEncoderGauche, CHANGE);

  /******Initialisation de l'interruption pour l'échantillonnage************/
  TIM_TypeDef *Instance = TIM6;
  MyTim = new HardwareTimer(Instance);
  MyTim->setOverflow(1 / dt, HERTZ_FORMAT);
  MyTim->attachInterrupt(Update_IT_callback);
  MyTim->resume();
  /**************************************************************************/

  /******interruption pour début match************/
  Instance = TIM7;
  HardwareTimer *TIM_Stop = new HardwareTimer(Instance);
  TIM_Stop->setOverflow(10000000, MICROSEC_FORMAT);
  TIM_Stop->attachInterrupt(Stop_match_callback);
  /**************************************************************************/

  PID_vitesse_D.SetMode(AUTOMATIC);
  PID_vitesse_G.SetMode(AUTOMATIC);

  Serial.println("attente jack");
  while (digitalRead(jack_pin))
    ;
  strat = digitalRead(strat_pin);
  Serial.print("demarer avec start ");
  Serial.println(strat);
  delay(100);
  Serial.println("fin des 9 secondes");
  // TIM_Stop->resume();
  Serial.println("demarage timer temps");

  cmd_vitesse_G = 500;
  cmd_vitesse_D = 500;
}

void loop()
{
  if (Update_IT)
  {
    Update_callback();
    if (interval_sensor > 10)
    {
      distance = distanceSensor.measureDistanceCm();
      // Vérifier si la distance est inférieure à 30 cm
      // if (distance < 30 && distance > 0)
      // {
      //   // Arrêter tous les mouvements
      //   cmd_vitesse_G = 0;
      //   cmd_vitesse_D = 0;
      //   myservo.write(0); // Arrêter le servomoteur
      //   Serial.println("Arret");
      // }
      interval_sensor = 0;
    }
  }
}
