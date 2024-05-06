
#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

/******Pin********/
#define PWM_D D6
#define DIR_D_1 A1
#define DIR_D_2 A0

#define PWM_G D3
#define DIR_G_1 D5
#define DIR_G_2 D4

#define CodDB D11
#define CodDA D12
#define CodGB D10
#define CodGA D9

#define jack_pin D0
#define strat_pin D2
/******************/

/******ECHANTILLONAGE********/
extern const float dt;
extern volatile bool Update_IT;
/****************************/

/******CONSIGNES PID**********/
extern float cmd_vitesse_G; // commande vitesse moteur gauche en mm/ms
extern float cmd_vitesse_D; // commande vitesse moteur droite en mm/ms
/*****************************/

/********Coef Vitesse ******/
extern float coefVitesseG;
extern float coefVitesseD;
/**************************/

/********Coef Angle****/
extern float empattementRoueCodeuse;
extern float coefAngle;
/**********************/

/******COEFICIENTS PID************/
extern float Kp_G, Ki_G, Kd_G; // coefficients PID vitesse moteur gauche
extern float Kp_D, Ki_D, Kd_D; // coefficients PID vitesse moteur droit
/*********************************/

/*****Sauvegarde des positions*****/
extern volatile long tick_droit;
extern volatile long tick_gauche;
/**********************************/

/******Constante mesuré************/
extern float vitesse_G; // vitesse gauche
extern float vitesse_D; // vitesse droite
extern float angle;     // angle
extern float distance;  // distance
/**********************************/

/******Corection PID************/
extern float Output_PID_vitesse_G; // Valeur sortante du PID vitesse moteur gauche, une PMW donc
extern float Output_PID_vitesse_D; // Valeur sortante du PID vitesse moteur droit, une PMW donc
/*******************************/

/***Rampe PID************/
extern float angle_final;
extern float distance_final;
/*********************/

extern HardwareTimer *MyTim;
extern unsigned long timeSetup;

extern int interval_sensor;
/*************************/

#endif