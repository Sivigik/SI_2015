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

const uint8_t pin_Rx = 36;


ControlePatte patte1(moteur1_IN1, moteur1_IN2, moteur1_OUT1, moteur1_OUT2);
ControlePatte patte2(moteur2_IN1, moteur2_IN2, moteur2_OUT1, moteur2_OUT2);
ControlePatte patte3(moteur3_IN1, moteur3_IN2, moteur3_OUT1, moteur3_OUT2);
ControlePatte patte4(moteur4_IN1, moteur4_IN2, moteur4_OUT1, moteur4_OUT2);
ControlePatte patte5(moteur5_IN1, moteur5_IN2, moteur5_OUT1, moteur5_OUT2);
ControlePatte patte6(moteur6_IN1, moteur6_IN2, moteur6_OUT1, moteur6_OUT2);

int time_b = 0;

ControlePatte* gauche[] = {
	&patte1,
	&patte2,
	&patte3
};
ControlePatte* droite[] = {
	&patte4,
	&patte5,
	&patte6,
};
ControlePatte* impaire[] = {
	&patte1,
	&patte3,
	&patte5,
};
ControlePatte* paire[] = {
	&patte2,
	&patte4,
	&patte6,
};

uint8_t ordre_dir = 0;
uint8_t ordre_vit = 0;

void initPattes();
void prepareMarche();
void setVitesse();
void avance();
void arrete();
void recule();
void interpreteOrdre();
void va_gauche();
void va_droite();

void setup()
{

#ifdef DEBUG
    Serial.begin(9600);
#endif
    dinfo("Déboguage.");

    initPattes();

    // réception radio
    vw_setup(2000); 
    vw_set_rx_pin(pin_Rx);
    vw_rx_start();

}

void loop()
{
	uint8_t buf[2]; 
    uint8_t buflen = 2;
	if (vw_wait_rx_max(10)) // attente de reception d'ordre pendant 10ms
	{
		if (vw_get_message(buf, &buflen)) // copie le message et vérifie qu'il n'est pas corrompu
		{
			ordre_dir = buf[0];
			ordre_vit = buf[1];
			interpreteOrdre();
		}
	}

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

	dinfo("Inversion du sens de rotation des pattes de gauche.");
	for(int i=0; i<3; i++)
		gauche[i]->reverse();

	dinfo("Positionnement des pattes.");

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
		impaire[i]->changePhase(PRET_HAUT);
	for(i=0;i<3;i++)
		paire[i]->changePhase(PRET_BAS);
}

void interpreteOrdre()
{
	if (ordre_dir & 1)
		va_gauche();
	if (ordre_dir & 2)
		va_droite();
	if (ordre_dir & 4)
		avance();
	if (ordre_dir & 8)
		recule();
	if (!(ordre_dir & 12))
		arrete();
	setVitesse();
}

void setVitesse() {
	patte1.changeVitesse(ordre_vit);
	patte2.changeVitesse(ordre_vit);
	patte3.changeVitesse(ordre_vit);
	patte4.changeVitesse(ordre_vit);
	patte5.changeVitesse(ordre_vit);
	patte6.changeVitesse(ordre_vit);
}
void avance() {
	patte1.changePhase(MARCHE_AV);
	patte2.changePhase(MARCHE_AV);
	patte3.changePhase(MARCHE_AV);
	patte4.changePhase(MARCHE_AV);
	patte5.changePhase(MARCHE_AV);
	patte6.changePhase(MARCHE_AV);
}
void arrete() {
	patte1.changePhase(STOP);
	patte2.changePhase(STOP);
	patte3.changePhase(STOP);
	patte4.changePhase(STOP);
	patte5.changePhase(STOP);
	patte6.changePhase(STOP);
}
void recule() {
	patte1.changePhase(MARCHE_AR);
	patte2.changePhase(MARCHE_AR);
	patte3.changePhase(MARCHE_AR);
	patte4.changePhase(MARCHE_AR);
	patte5.changePhase(MARCHE_AR);
	patte6.changePhase(MARCHE_AR);
}

void va_gauche() {
	// à faire
}
void va_droite() {
	// à faire
}
