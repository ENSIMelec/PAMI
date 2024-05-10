#include "Motor.h"
#include "main.h"
/*******FOCNTION POUR GERER LES MOTEUR********/
void moteur_gauche_direction(bool dir)
{
    digitalWrite(DIR_G_1, dir);
    digitalWrite(DIR_G_2, !dir);
}
void moteur_droit_direction(bool dir)
{
    digitalWrite(DIR_D_1, dir);
    digitalWrite(DIR_D_2, !dir);
}
void moteur_droit_break(bool activ)
{
    digitalWrite(DIR_D_1, activ);
    digitalWrite(DIR_D_2, activ);
}
void moteur_gauche_break(bool activ)
{
    digitalWrite(DIR_G_1, activ);
    digitalWrite(DIR_G_2, activ);
}
void moteur_gauche_freeWheel(bool activ)
{
    digitalWrite(DIR_G_1, !activ);
    digitalWrite(DIR_G_2, !activ);
}
void moteur_droit_freeWheel(bool activ)
{
    digitalWrite(DIR_D_1, !activ);
    digitalWrite(DIR_D_2, !activ);
}
/*********************************************/
