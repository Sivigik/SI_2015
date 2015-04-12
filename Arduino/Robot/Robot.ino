#include "VirtualWire.h"
#include "controlePatte.h"

/*DEFINITION DES PINS
*/
const uint8_t moteur1_IN1 = 4;
const uint8_t moteur1_IN2 = 6;
const uint8_t moteur1_OUT1 = 3;
const uint8_t moteur1_OUT2 = 5;

const uint8_t moteur2_IN1 = 10;
const uint8_t moteur2_IN2 = 24;
const uint8_t moteur2_OUT1 = 3;
const uint8_t moteur2_OUT2 = 30;

const uint8_t moteur3_IN1 = 11;
const uint8_t moteur3_IN2 = 25;
const uint8_t moteur3_OUT1 = 5;
const uint8_t moteur3_OUT2 = 31;

const uint8_t moteur4_IN1 = 12;
const uint8_t moteur4_IN2 = 26;
const uint8_t moteur4_OUT1 = 6;
const uint8_t moteur4_OUT2 = 32;

const uint8_t moteur5_IN1 = 13;
const uint8_t moteur5_IN2 = 27;
const uint8_t moteur5_OUT1 = 7;
const uint8_t moteur5_OUT2 = 34;

const uint8_t moteur6_IN1 = 22;
const uint8_t moteur6_IN2 = 28;
const uint8_t moteur6_OUT1 = 8;
const uint8_t moteur6_OUT2 = 35;


ControlePatte patte1(moteur1_IN1, moteur1_IN2, moteur1_OUT1, moteur1_OUT2);
ControlePatte patte2(moteur2_IN1, moteur2_IN2, moteur2_OUT1, moteur2_OUT2);
ControlePatte patte3(moteur3_IN1, moteur3_IN2, moteur3_OUT1, moteur3_OUT2);
ControlePatte patte4(moteur4_IN1, moteur4_IN2, moteur4_OUT1, moteur4_OUT2);
ControlePatte patte5(moteur5_IN1, moteur5_IN2, moteur5_OUT1, moteur5_OUT2);
ControlePatte patte6(moteur6_IN1, moteur6_IN2, moteur6_OUT1, moteur6_OUT2);

int time_b = 0;

const ControlePatte* gauche[] = {
	&patte1,
	&patte2,
	&patte3
};
const ControlePatte* droite[] = {
	&patte4,
	&patte5,
	&patte6,
};
const ControlePatte* impaire[] = {
	&patte1,
	&patte3,
	&patte5,
};
const ControlePatte* paire[] = {
	&patte2,
	&patte4,
	&patte6,
};

void initPattes();
void prepareMarche();

void setup()
{

#ifdef DEBUG
    Serial.begin(9600);
#endif
    dinfo("Déboguage.");

    initPattes();

}

void loop()
{
	patte1.regulation();
}

void initPattes()
{
	dinfo("Initialisation des pattes.");

	patte1.changePhase(STOP);
	patte2.changePhase(STOP);
	patte3.changePhase(STOP);
	patte4.changePhase(STOP);
	patte5.changePhase(STOP);
	patte6.changePhase(STOP);

	uint8_t zero = 0;

	while(zero != 7)
	{
		patte1.regulation();
		if(patte1.isZero())
			zero |= 1 << 0;
		patte2.regulation();
		if(patte2.isZero())
			zero |= 1 << 1;
		patte3.regulation();
		if(patte3.isZero())
			zero |= 1 << 2;
		patte4.regulation();
		if(patte4.isZero())
			zero |= 1 << 3;
		patte5.regulation();
		if(patte5.isZero())
			zero |= 1 << 4;
		patte6.regulation();
		if(patte6.isZero())
			zero |= 1 << 5;
	}
	dinfo("Les pattes sont au repos.");
}
void prepareMarche()
{
	int i;
	for(i=0;i<3;i++)
		impaire[i].changePhase(PRET_HAUT);
	for(i=0;i<3;i++)
		paire[i].changePhase(PRET_BAS);
}