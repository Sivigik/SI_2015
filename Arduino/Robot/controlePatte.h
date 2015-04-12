#ifndef H_PATTE
#define H_PATTE

//#define DEBUG

#ifdef DEBUG
#define dinfo(msg) Serial.println(msg)
#define dvar(var) Serial.print(#var);Serial.print(":");Serial.println(var)
#else
#define dinfo(msg)
#define dvar(var)
#endif

#include "Arduino.h"
#include "settings.h"

/////PHASES/////

#define STOP 0
#define MARCHE_AV 1
#define MARCHE_AR 2

#define PRET_HAUT 3
#define PRET_BAS 4

////////////////

/////SENS DE MARCHE/////

#define SENS_1 HIGH
#define SENS_2 LOW

////////////////



class ControlePatte
{
public:
	ControlePatte(uint8_t pin_capteur1, uint8_t pin_capteur2, uint8_t pin_out1, uint8_t pin_out2);
	void changeVitesse(uint8_t nouvelle_vitesse);
	void regulation();
	void changePhase(uint8_t phase);
	void stopMode();
	void marcheMode();
	bool isZero();
	bool finPhase();
private:
	uint8_t pin_out1;
	uint8_t pin_in1;
	uint8_t pin_in2;
	uint8_t pin_out2;

	uint8_t phase;
	uint8_t vitesse_h;
	uint8_t vitesse_s;
};
#endif
