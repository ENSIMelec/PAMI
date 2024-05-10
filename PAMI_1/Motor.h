#include <Arduino.h>
#include "main.h"

void moteur_gauche_direction(bool dir);
void moteur_droit_direction(bool dir);
void moteur_droit_break(bool activ);
void moteur_gauche_break(bool activ);
void moteur_gauche_freeWheel(bool activ);
void moteur_droit_freeWheel(bool activ);