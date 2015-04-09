#include <VirtualWire.h>

#define DEBUG

#ifdef DEBUG
#define dinfo(msg) Serial.println(msg)
#define dvar(var) Serial.print(#var);Serial.print(":");Serial.println(var)
#else
#define dinfo(msg)
#define dvar(var)
#endif

#define DIR 0
#define VITESSE 1

#define GAUCHE 0
#define DROITE 1
#define AVANT 2
#define ARRIERE 3 

uint8_t toSend[] = {0, 0};

const uint8_t bp_avance = 2;
const uint8_t bp_recule = 3;
const uint8_t bp_gauche = 4;
const uint8_t bp_droite = 5;
const uint8_t potar = 0;

void readValues();

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
    dinfo("Déboguage.");

    pinMode(bp_avance, OUTPUT);
    pinMode(bp_recule, OUTPUT);
    pinMode(bp_gauche, OUTPUT);
    pinMode(bp_droite, OUTPUT);
 
    vw_setup(2000);
}
 
void loop()
{
    dinfo("LECTURE DES VALEURS");

    readValues();

    dinfo("TRANSMISSION");


    vw_send(toSend, 2);
    vw_wait_tx();

    dinfo("FIN");

    delay(500);
}

void readValues()
{
    toSend[VITESSE] = analogRead(potar);

    if (!digitalRead(bp_recule))
    {
        if(!toSend[DIR]&(1<<AVANT))
            toSend[DIR] |= (1<<ARRIERE);
        
        toSend[DIR] &= ~(1<<AVANT);
    }

    if (!digitalRead(bp_avance))
    {
        if(!toSend[DIR]&(1<<ARRIERE))
            toSend[DIR] |= (1<<AVANT);
        
        toSend[DIR] &= ~(1<<ARRIERE);
    }

    if (!digitalRead(bp_gauche))
    {
        toSend[DIR] |= (1<<GAUCHE);
        toSend[DIR] &= ~(1<<DROITE);
    }

    if (!digitalRead(bp_droite))
    {
        toSend[DIR] |= (1<<DROITE);
        toSend[DIR] &= ~(1<<GAUCHE);
    }

}