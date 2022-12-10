#include <SoftwareSerial.h>

//déclaration des variables
int seq[8] = {};
int timeDelay = 250;
int bouton = A0;

int switch0 = 1;
int switch1 = 2;
int switch2 = 3;
int switch3 = 4;
int switch4 = 5;
int switch5 = 6;
int switch6 = 7;
int switch7 = 8;

int led0 = 9;
int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;
int led5 = A1;
int led6 = A2;
int led7 = A3;


void setup() {
    Serial.begin(9600);
  // séquence aléatoire pour les cables
  Serial.println("Séquence : ");
  for (int i=0; i<8; i++){
    randomSeed(analogRead(SDA));
    seq[i]=random(0,2);
    //récupérer la séquence générée
    Serial.print(seq[i]);
  }
  //set up bouton 
  pinMode(bouton,INPUT);
  //set up switch
  pinMode(switch0, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);
  pinMode(switch5, INPUT);
  pinMode(switch6, INPUT);
  pinMode(switch7, INPUT);  
  //set up LED
  pinMode(led0, OUTPUT); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);  
  pinMode(led7, OUTPUT);
}

void loop() {
    // vérifie la séquence rentrée par le joueur
  if(digitalRead(bouton)== HIGH){
    if((digitalRead(switch0)==seq[0]) && (digitalRead(switch1)==seq[1]) && digitalRead(switch2)==seq[2] && digitalRead(switch3)==seq[3] && 
        digitalRead(switch4)==seq[4] && digitalRead(switch5)==seq[5] && digitalRead(switch6)==seq[6] && digitalRead(switch7)==seq[7]){
    //Débloquer moteur
    //son de victoire
    }
    else{
    //son de défaite   
   }
  }

  //une des switch mis sur 1
  if (digitalRead(switch0) == HIGH){
    digitalWrite(led0, HIGH);  
    delay(timeDelay);
  }
  if (digitalRead(switch1) == HIGH){
    digitalWrite(led1, HIGH);  
    delay(timeDelay);
  }
  if (digitalRead(switch2) == HIGH){
    digitalWrite(led2, HIGH);   
    delay(timeDelay);
  }
  if (digitalRead(switch3) == HIGH){
    digitalWrite(led3, HIGH); 
    delay(timeDelay);
  }
  if (digitalRead(switch4) == HIGH){
    digitalWrite(led4, HIGH);  
    delay(timeDelay);
  }
  if (digitalRead(switch5) == HIGH){
    digitalWrite(led5, HIGH);  
    delay(timeDelay);
  }
  if (digitalRead(switch6) == HIGH){
    digitalWrite(led6, HIGH); 
    delay(timeDelay);
  }
  if (digitalRead(switch7) == HIGH){
    digitalWrite(led7, HIGH); 
    delay(timeDelay);
  }

  //une des switch mis sur 0
  if (digitalRead(switch0) == LOW){
    digitalWrite(led0, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch1) == LOW){
    digitalWrite(led1, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch2) == LOW){
    digitalWrite(led2, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch3) == LOW){
    digitalWrite(led3, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch4) == LOW){
    digitalWrite(led4, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch5) == LOW){
    digitalWrite(led5, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch6) == LOW){
    digitalWrite(led6, LOW);
    delay(timeDelay);
  }
  if (digitalRead(switch7) == LOW){
    digitalWrite(led7, LOW);
    delay(timeDelay);
  }  
}


