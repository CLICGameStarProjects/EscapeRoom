#include <SoftwareSerial.h>

const int MAX_LEVEL = 6;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;

int velocity = 1000;
int boutonStart = A4;
int boutonBleu = A0;
int boutonJaune = A1;
int boutonRouge = A2;
int boutonVert = A3;
int ledBleu = 5;
int ledJaune = 4;
int ledRouge = 3;
int ledVerte = 2;

void setup() {
  Serial.begin(9600);
  //set up boutons
  pinMode(boutonBleu, INPUT);
  pinMode(boutonJaune, INPUT);
  pinMode(boutonRouge, INPUT);
  pinMode(boutonVert, INPUT);
  
  //set up led
  pinMode(ledBleu, OUTPUT);
  pinMode(ledJaune, OUTPUT);
  pinMode(ledRouge, OUTPUT);
  pinMode(ledVerte, OUTPUT);

  //allume toutes les leds
  digitalWrite(ledBleu, HIGH);
  digitalWrite(ledJaune, HIGH);
  digitalWrite(ledRouge, HIGH);
  digitalWrite(ledVerte, HIGH);
}

void loop(){
  if (level == 1){
    //génère une séquence
    generate_sequence();
  }  
  //Si on appuis sur le bouton lance la séquence ou si on a gagné le lvl d'avant
  if (digitalRead(boutonStart) == LOW || level != 1){
    //montre la séquence  
    show_sequence();
    //enregistre ta séquence
    get_sequence();
  }
}

void show_sequence(){
  //éteint toutes les leds
  digitalWrite(ledBleu, LOW);
  digitalWrite(ledJaune, LOW);
  digitalWrite(ledRouge, LOW);
  digitalWrite(ledVerte, LOW);
  
  //montre la séquence
  for (int i = 0; i < level; i++){
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void get_sequence(){
  //indique si la séquence est correct
  int flag = 0;

  for (int i = 0; i < level; i++){
    flag = 0;
    while(flag == 0){
      if (digitalRead(boutonBleu) == LOW){
        digitalWrite(ledBleu, HIGH);
        your_sequence[i] = 5;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
      digitalWrite(ledBleu, LOW);
      }

      if (digitalRead(boutonJaune) == LOW){
        digitalWrite(ledJaune, HIGH);
        your_sequence[i] = 4;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
      digitalWrite(ledJaune, LOW);
      }

      if (digitalRead(boutonRouge) == LOW){
        digitalWrite(ledRouge, HIGH);
        your_sequence[i] = 3;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]){
         wrong_sequence();
         return;
        } 
        digitalWrite(ledRouge, LOW);
      }

      if (digitalRead(boutonVert) == LOW){
        digitalWrite(ledVerte, HIGH);
        your_sequence[i] = 2;
        flag = 1;
        delay(200);
        if (your_sequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
        digitalWrite(ledVerte, LOW);
      }

    }
  }
  right_sequence();
}

void generate_sequence(){
  //générer une sequence aléatoire
  randomSeed(millis()); 
  for (int i = 0; i < MAX_LEVEL; i++){
    sequence[i] = random(2,6);
  }
}

void wrong_sequence(){
  /*for (int i = 0; i < 3; i++){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(250);
  }*/

  //Son défaite  
  Serial.println("dommage");
  //Retour départ  
  digitalWrite(ledBleu, LOW);
  digitalWrite(ledJaune, LOW);
  digitalWrite(ledRouge, LOW);
  digitalWrite(ledVerte, LOW);
  delay(500);

  digitalWrite(ledBleu, HIGH);
  digitalWrite(ledJaune, HIGH);
  digitalWrite(ledRouge, HIGH);
  digitalWrite(ledVerte, HIGH);
  delay(500);

  digitalWrite(ledBleu, LOW);
  digitalWrite(ledJaune, LOW);
  digitalWrite(ledRouge, LOW);
  digitalWrite(ledVerte, LOW);
  delay(500);
   
  level = 1;
  velocity = 1000;
  
}

void right_sequence(){
  /*digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(250);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(500);
  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(500);*/
  
  if (level < MAX_LEVEL){
    //led clignotes
    digitalWrite(ledBleu, LOW);
    digitalWrite(ledJaune, LOW);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVerte, LOW);
    delay(500);

    digitalWrite(ledBleu, HIGH);
    digitalWrite(ledJaune, HIGH);
    digitalWrite(ledRouge, HIGH);
    digitalWrite(ledVerte, HIGH);
    delay(500);

    digitalWrite(ledBleu, LOW);
    digitalWrite(ledJaune, LOW);
    digitalWrite(ledRouge, LOW);
    digitalWrite(ledVerte, LOW);
    delay(500);
    Serial.println("encore un effort");
    level++;
  }   
  
  //Condition de voctoire (j'ai ajouté)
  if (level == MAX_LEVEL){
    //led clignote 3 fois;
    for (int i = 0; i < 3; i++){
      digitalWrite(ledBleu, HIGH);
      digitalWrite(ledJaune, HIGH);
      digitalWrite(ledRouge, HIGH);
      digitalWrite(ledVerte, HIGH);
      delay(250);

      digitalWrite(ledBleu, LOW);
      digitalWrite(ledJaune, LOW);
      digitalWrite(ledRouge, LOW);
      digitalWrite(ledVerte, LOW);
      delay(250);
    }
    
    //Son de victoire
    //Déclanche le moteur
    Serial.println("gg bro");
  }
  //Augmente la difficulté
  velocity -= 50;   
}