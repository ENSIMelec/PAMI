#include "main.h"
#include "PID.h"
#include <digitalWriteFast.h>

extern PID PID_vitesse_G;
extern PID PID_vitesse_D;

void Update_IT_callback(void);

void handleEncoderDroit();
void handleEncoderGauche();
void Update_callback();
void Stop_match_callback();