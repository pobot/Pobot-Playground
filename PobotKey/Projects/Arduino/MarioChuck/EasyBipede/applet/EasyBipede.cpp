#include <MegaServo.h>
#include <Wire.h>

#include "Sequences.h"

// \u00e0 partir de combien de millisecondes on passe en mode automatique (5000 = 5 secondes)
#define DELAY_SWITCHMODE  5000

#define FORWARD  0
#define BACKWARD 1
#define LEFT 2
#define RIGHT 3

#define INCREMENT  1
#define DELAY_UPDATE  15

#include "WProgram.h"
void setup();
void loop();
void sendCapteurs();
void updatePosition();
void changeConsigne();
MegaServo Servos[4]; // 4 servos

/////// commun 

int consigne[4]; // 4 consignes mises \u00e0 jour selon la commande
int position[4]; // 4 vrai position du servo

/////// le mode automatique

long millisLastReceived = millis(); // derni\u00e8re r\u00e9ception d'un caract\u00e8re

long millisLastChanged = millis();

int curIndex = 0; // l'indice de la commande en cours dans la s\u00e9quence en cours 
int curMode = FORWARD; // la s\u00e9quence en cours
int reqMode = FORWARD; // la s\u00e9quence demand\u00e9e


/////// le mode contr\u00f4l\u00e9 

char cmd[4]; // 4 octets de commande re\u00e7ue au fur et \u00e0 mesure
int indice = 0;

/**
 * Configuration de l'Arduino
 */
void setup()
{
  // la liaison s\u00e9rie
  Serial.begin(9600);

  // les servomoteurs

  // left leg
  Servos[0].attach(8); // genou
  Servos[1].attach(11); // hanche
  // right leg
  Servos[2].attach(10); // genou
  Servos[3].attach(9); // hanche

}


void loop()
{
  if (Serial.available()) 
  {    
    // se souvenir de la r\u00e9ception
    millisLastReceived = millis();

    char rec = Serial.read();
    switch (rec)
    {
    case 'p':      
      indice = 0;
      changeConsigne();
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      cmd[indice++] = rec;
      break;
    }
  }

  // test si on est en mode automatique ou contr\u00f4l\u00e9
  if ( (millis() - millisLastReceived) > DELAY_SWITCHMODE)
  {
    // mode automatique

    // test si on est en train de parcourir la s\u00e9quence
    if (curMode == reqMode || curIndex != 0)
    {
      if ((millis() - millisLastChanged) > 1000) 
      {
        millisLastChanged = millis();
        // on continue
        cmd[0] = 48+sequences[curMode][curIndex][0];
        cmd[1] = 48+sequences[curMode][curIndex][1];
        cmd[2] = 48+sequences[curMode][curIndex][2];
        cmd[3] = 48+sequences[curMode][curIndex][3];
        changeConsigne();

        curIndex++;
        if (curIndex >= nombreCommandes[curMode])
        {
          curIndex = 0;
        }

      }    
    } 

    // atteindre le mode souhait\u00e9

    if (curMode != reqMode) 
    {
      // les s\u00e9quences en cours et souhait\u00e9e sont diff\u00e9rentes
      // mais peut \u00eatre qu'on a atteint le d\u00e9but de la s\u00e9quence, moment propice pour changer
      if (curIndex == 0)
      {
        curMode = reqMode; // changement de s\u00e9quence        
      }
    }

    // changer de mode
    if (curIndex ==0)       // on ne teste que lorsque l'index est \u00e0 0 (robot \u00e0 plat)
    {
      int val = analogRead(0) + analogRead(1);
      if (curMode != FORWARD && val < 1000)
      {
        reqMode = FORWARD;
        Serial.println("Forward");
      }     
      
      if (curMode != BACKWARD && val > 1000) {
        reqMode = BACKWARD;
        Serial.println("Backward");
      }
    }

  } 
  else {
    // mode normal


  }

  // mise \u00e0 jour de la position
  updatePosition();

  // envoi des capteurs
  sendCapteurs();

  // attente
  delay(DELAY_UPDATE);

}

void sendCapteurs()
{
  Serial.print(analogRead(0));
  Serial.print(" ");
  Serial.print(analogRead(1));
  Serial.print(" ");
  Serial.println();  
}

void updatePosition()
{
  for (int i = 0; i < 4 ; i++) {
    if (consigne[i] > position[i] + INCREMENT) 
    {
      position[i] = position[i] + INCREMENT;
      Servos[i].write(position[i]);
    }
    if (consigne[i] < position[i] - INCREMENT)
    {
      position[i] = position[i] - INCREMENT;  
      Servos[i].write(position[i]);
    }
  }
}

/**
 * Prends en compte la nouvelle commande re\u00e7ue 
 * et traduis en consignes de servomoteur
 */
void changeConsigne()
{  
  //
  if (cmd[0] != '0') 
  {
    consigne[0] = 18*(10-(cmd[0]-48));
  }
  if (cmd[1] != '0') 
  {
    consigne[1] = 18*(cmd[1]-48);
  }
  if (cmd[2] != '0') 
  {
    consigne[2] = 18*(cmd[2]-48);
  }
  if (cmd[3] != '0') 
  {
    consigne[3] = 18*(cmd[3]-48);
  }

}



int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

