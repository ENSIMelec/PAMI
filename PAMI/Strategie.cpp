#include "Strategie.h"
int deplacement = 0;

void jaune_1()
{
    if (deplacement == 0)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = 900;
        deplacement += 1;
    }
    else if (deplacement == 1 && distance >= 200)
    {
        deplacement += 1;
        distance = 0;
    }

    else if (angle < PI / 3 && deplacement == 2)

    {
        cmd_vitesse_G = -900;
        cmd_vitesse_D = +900;
        deplacement += 1;
        distance = 0;
    }
    else if (deplacement == 2 &&angle = PI / 3)
    {
        deplacement += 1;
        distance = 0;
    }

    else if (distance < 200 && deplacement == 3)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = 900;
        deplacement += 1;
        angle = 0;
        distance = 0;
    }
    else if (deplacement == 3 &&distance = 200)
    {
        deplacement += 1;
        distance = 0;
    }

    else if (angle < 2 * PI / 3 && deplacement == 4)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = -900;
        deplacement += 1;
        distance = 0;
    }
    else if (deplacement == 4 &&angle = 2 * PI / 3)
    {
        deplacement += 1;
        distance = 0;
    }
    else if (distance < 1800 && deplacement == 5)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = 900;
        deplacement += 1;
        angle = 0;
        distance = 0;
    }
    else if (deplacement == 5 &&distance = 1800)
    {
        deplacement += 1;
        distance = 0;
    }
}

void bleu_1()
{
    if (deplacement == 0)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = 900;
        deplacement += 1;
    }
    else if (deplacement == 1 && distance >= 200)
    {
        deplacement += 1;
        distance = 0;
    }

    else if (angle < PI / 3 && deplacement == 2)

    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = -900;
        deplacement += 1;
        distance = 0;
    }
    else if (deplacement == 2 &&angle = PI / 3)
    {
        deplacement += 1;
        distance = 0;
    }

    else if (distance < 200 && deplacement == 3)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = 900;
        deplacement += 1;
        angle = 0;
        distance = 0;
    }
    else if (deplacement == 3 &&distance = 200)
    {
        deplacement += 1;
        distance = 0;
    }

    else if (angle < 2 * PI / 3 && deplacement == 4)
    {
        cmd_vitesse_G = -900;
        cmd_vitesse_D = 900;
        deplacement += 1;
        distance = 0;
    }
    else if (deplacement == 4 &&angle = 2 * PI / 3)
    {
        deplacement += 1;
        distance = 0;
    }
    else if (distance < 1800 && deplacement == 5)
    {
        cmd_vitesse_G = 900;
        cmd_vitesse_D = 900;
        deplacement += 1;
        angle = 0;
        distance = 0;
    }
    else if (deplacement == 5 &&distance = 1800)
    {
        deplacement += 1;
        distance = 0;
    }
}

void jaune_2()
{
}
void bleu_2()
{
}

void Pami1()
{
    if (strat)
        jaune_1();
    else
        bleu_1();
}

void Pami2()
{
    if (strat)
        jaune_2();
    else
        bleu_2();
}