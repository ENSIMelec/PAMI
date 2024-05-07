#include "Strategie.h"
int deplacement = 0;

void jaune_1() {

  

  // else if (angle < PI / 3 && deplacement == 2)

  // {
  //   cmd_vitesse_G = -864;
  //   cmd_vitesse_D = +864;
  //   deplacement += 1;
  //   distance = 0;
  // } else if (deplacement == 1 && distance >= 200) {
  //   cmd_vitesse_G = 0;
  //   cmd_vitesse_D = 0;
  //   deplacement += 1;
  //   distance = 0;
  // } else if (distance < 200 && deplacement == 3) {
  //   cmd_vitesse_G = 864;
  //   cmd_vitesse_D = 864;
  //   deplacement += 1;
  // } else if (deplacement == 4 && distance >= 200) {
  //   cmd_vitesse_G = 0;
  //   cmd_vitesse_D = 0;
  //   deplacement += 1;
  //   distance = 0;
  // } else if (angle < 2 * PI / 3 && deplacement == 5) {
  //   cmd_vitesse_G = 864;
  //   cmd_vitesse_D = -864;
  //   deplacement += 1;
  // } else if (deplacement == 6 && distance >= 200) {
  //   cmd_vitesse_G = 0;
  //   cmd_vitesse_D = 0;
  //   deplacement += 1;
  //   distance = 0;
  // } else if (distance < 1800 && deplacement == 7) {
  //   cmd_vitesse_G = 864;
  //   cmd_vitesse_D = 964;
  //   deplacement += 1;
  //   angle = 0;
  //   distance = 0;
  // } else if (deplacement == 8 && distance >= 200) {
  //   cmd_vitesse_G = 0;
  //   cmd_vitesse_D = 0;
  //   deplacement += 1;
  //   distance = 0;
  // }
}

void bleu_1() {
  
}

void jaune_2() {
}
void bleu_2() {
}

void Pami1() {
  if (strat)
    jaune_1();
  else
    bleu_1();
}

void Pami2() {
  if (strat)
    jaune_2();
  else
    bleu_2();
}