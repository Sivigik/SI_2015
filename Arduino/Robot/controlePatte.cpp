#include "controlePatte.h"


ControlePatte::ControlePatte(uint8_t pin_capteur1, uint8_t pin_capteur2, uint8_t pin_out1, uint8_t pin_out2)
{
	this->pin_in1 = pin_capteur1;
	this->pin_in2 = pin_capteur2;
	this->pin_out1 = pin_out1;
	this->pin_out2 = pin_out2;

	this->phase = STOP;
	this->vitesse = 0;
}
void ControlePatte::changeVitesse(uint8_t nouvelle_vitesse)
{
	this->vitesse = vitesse;
}
void ControlePatte::regulation()
{
	if (this->phase == STOP)
		this->stopMode();
	else
		this->marcheMode();
}
void ControlePatte::changePhase(uint8_t phase)
{
	this->phase = phase;
}
void ControlePatte::stopMode()
{
	bool capteur_1 = digitalRead(this->pin_in1);
	bool capteur_2 = digitalRead(this->pin_in2);

	if ((capteur_1 && !capteur_2) || (!capteur_1 && !capteur_2))
	{
		analogWrite(this->pin_out1, 0);
		analogWrite(this->pin_out2, 255);
Serial.println("SENS2");
	}
	else if (!capteur_1 && capteur_2)
	{
		analogWrite(this->pin_out2, 0);
		analogWrite(this->pin_out1, 255);
Serial.println("SENS1");
	}
	else
	{
		analogWrite(this->pin_out1, 0);
		analogWrite(this->pin_out2, 0);
Serial.println("ARRET");
	}
}
bool ControlePatte::isZero()
{
	return digitalRead(this->pin_in1) && digitalRead(this->pin_in2);
}
void ControlePatte::marcheMode()
{

}
