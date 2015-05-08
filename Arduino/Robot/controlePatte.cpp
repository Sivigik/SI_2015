#include "controlePatte.h"


ControlePatte::ControlePatte(uint8_t pin_capteur1, uint8_t pin_capteur2, uint8_t pin_out1, uint8_t pin_out2)
{
	pinMode(pin_capteur1, INPUT);
	pinMode(pin_capteur2, INPUT);
	pinMode(pin_out1, OUTPUT);
	pinMode(pin_out2, OUTPUT);

	this->pin_in1 = pin_capteur1;
	this->pin_in2 = pin_capteur2;
	this->pin_out1 = pin_out1;
	this->pin_out2 = pin_out2;

	this->phase = STOP;
	this->vitesse_h = 0;
	this->vitesse_s = 0;

	this->reversed = false;
}
void ControlePatte::changeVitesse(uint8_t nouvelle_vitesse)
{
	this->vitesse_h = nouvelle_vitesse*(2*PI - PORTION_SOL)/(PORTION_SOL*RAYON_PATTE);
	this->vitesse_s = nouvelle_vitesse/RAYON_PATTE;
}
void ControlePatte::regulation()
{
	if (this->phase == STOP)
		this->stopMode();
	else if(this->phase == MARCHE_AV || this->phase == MARCHE_AR)
		this->marcheMode();
	else if(this->phase == PRET_HAUT || this->phase == PRET_BAS)
		this->pretMode();
}
void ControlePatte::changePhase(uint8_t phase)
{
	this->phase = phase;
}
void ControlePatte::stopMode()
{
	bool capteur_1 = digitalRead(this->pin_in1);
	bool capteur_2 = digitalRead(this->pin_in2);

	if ((capteur_1 && !capteur_2) || (capteur_1 && capteur_2))
	{
		if(this->reversed) {
			analogWrite(this->pin_out1, 255);
			analogWrite(this->pin_out2, 0);
		}
		else {
			analogWrite(this->pin_out1, 0);
			analogWrite(this->pin_out2, 255);
		}
	}
	else if (!capteur_1 && capteur_2)
	{
		if(this->reversed) {
			analogWrite(this->pin_out2, 255);
			analogWrite(this->pin_out1, 0);
		}
		else {
			analogWrite(this->pin_out2, 0);
			analogWrite(this->pin_out1, 255);
		}
	}
	else
	{
		analogWrite(this->pin_out1, 0);
		analogWrite(this->pin_out2, 0);
	}
}
bool ControlePatte::isZero()
{
	return !digitalRead(this->pin_in1) && !digitalRead(this->pin_in2);
}
void ControlePatte::marcheMode()
{
	bool capteur_1 = digitalRead(this->pin_in1);
	bool capteur_2 = digitalRead(this->pin_in2);

	if(capteur_1 && capteur_2)
	{
		// On est en l'air
		if (this->phase == MARCHE_AV) {
			if(this->reversed) {
				analogWrite(this->pin_out1, this->vitesse_h);
				analogWrite(this->pin_out2, 0);
			}
			else {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, this->vitesse_h);
			}
		}
		else
		{
			if(this->reversed) {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, this->vitesse_h);
	
			}
			else {
				analogWrite(this->pin_out1, this->vitesse_h);
				analogWrite(this->pin_out2, 0);
			}
		}
	}
	else
	{
		// On est au sol
		if (this->phase == MARCHE_AV) {
			if(this->reversed) {
				analogWrite(this->pin_out1, this->vitesse_s);
				analogWrite(this->pin_out2, 0);
			}
			else {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, this->vitesse_s);
			}
		}
		else
		{
			if (this->reversed) {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, this->vitesse_s);
			}
			else {
				analogWrite(this->pin_out1, this->vitesse_s);
				analogWrite(this->pin_out2, 0);
			}
		}
	}
}
void ControlePatte::pretMode()
{
	bool capteur_1 = digitalRead(this->pin_in1);
	bool capteur_2 = digitalRead(this->pin_in2);

	if(this->phase == PRET_HAUT)
	{
		if (capteur_2) {
			if (this->reversed) {
				analogWrite(this->pin_out1, 255);
				analogWrite(this->pin_out2, 0);
			}
			else {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, 255);
			}
		}
		else
		{
			if (this->reversed) {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, 255);
			}
			else {
				analogWrite(this->pin_out1, 255);
				analogWrite(this->pin_out2, 0);
			}
		}
	}
	if(this->phase == PRET_BAS)
	{
		if (capteur_1) {
			if (this->reversed) {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, 255);
			}
			else {
				analogWrite(this->pin_out1, 255);
				analogWrite(this->pin_out2, 0);
			}
		}
		else
		{
			if (this->reversed) {
				analogWrite(this->pin_out1, 255);
				analogWrite(this->pin_out2, 0);
			}
			else {
				analogWrite(this->pin_out1, 0);
				analogWrite(this->pin_out2, 255);
			}
		}
	}

}

void ControlePatte::reverse()
{
	this->reversed = !this->reversed;
}