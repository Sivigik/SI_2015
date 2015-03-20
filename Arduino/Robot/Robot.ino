#include "controlePatte.h"

/*DEFINITION DES PINS
*/
const uint8_t moteur1_IN1 = 4;
const uint8_t moteur1_IN2 = 6;
const uint8_t moteur1_OUT1 = 3;
const uint8_t moteur1_OUT2 = 5;
/*
const uint8_t moteur2_IN1 = 10;
const uint8_t moteur2_IN2 = 24;
const uint8_t moteur2_PWM = 3;
const uint8_t moteur2_SENS = 30;

const uint8_t moteur3_IN1 = 11;
const uint8_t moteur3_IN2 = 25;
const uint8_t moteur3_PWM = 5;
const uint8_t moteur3_SENS = 31;

const uint8_t moteur4_IN1 = 12;
const uint8_t moteur4_IN2 = 26;
const uint8_t moteur4_PWM = 6;
const uint8_t moteur4_SENS = 32;

const uint8_t moteur5_IN1 = 13;
const uint8_t moteur5_IN2 = 27;
const uint8_t moteur5_PWM = 7;
const uint8_t moteur5_SENS = 34;

const uint8_t moteur6_IN1 = 22;
const uint8_t moteur6_IN2 = 28;
const uint8_t moteur6_PWM = 8;
const uint8_t moteur6_SENS = 35;*/

ControlePatte patte1(moteur1_IN1, moteur1_IN2, moteur1_OUT1, moteur1_OUT2);
/*ControlePatte patte1(moteur2_PWM, moteur2_IN1, moteur2_IN2, moteur2_SENS);
ControlePatte patte1(moteur3_PWM, moteur3_IN1, moteur3_IN2, moteur3_SENS);
ControlePatte patte1(moteur4_PWM, moteur4_IN1, moteur4_IN2, moteur4_SENS);
ControlePatte patte1(moteur5_PWM, moteur5_IN1, moteur5_IN2, moteur5_SENS);
ControlePatte patte1(moteur6_PWM, moteur6_IN1, moteur6_IN2, moteur6_SENS);
*/
void setup()
{
        Serial.begin(9600);
	patte1.changePhase(STOP);
}

void loop()
{
	patte1.regulation();
}
