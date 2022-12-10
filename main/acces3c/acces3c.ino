//#include <Servo.h>

//Il s'agit de l'accès "Speedrun". On observe que les LEDs rouge et verte clignotent 
//en alternance. Si on appuie avec succès sur le bouton blanc lorsque la LED verte 
//est active trois fois d’affilée, la porte s’ouvre.
//#include <Servo.h>
//Servo myServo; //bibliothèque pour utiliser le servomoteur

int ledRouge = 12;
int ledVerte = 25;
int buzzer = 19;
int button = 18;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ledRouge, OUTPUT); //led rouge
  pinMode(ledVerte, OUTPUT); //led verte
  pinMode(buzzer, OUTPUT); //Buzzer

  //myServo.attach(9) //Moteur
  //myServo.write(90); //initialization

  pinMode(button, INPUT); //Bouton

}

int counter = 0; //quand bouton appuyé et que la vert s'allume +1, quand rouge s'allume et quand on appuie alors que le counter est différent de 3, 0

void loop() {
  // put your main code here, to run repeatedly:
  //boutonAppuye = digitalRead(button); //march que si on a 7??? //si bouton actif ce sera HIGH, sinon LOW

  //utiliser random(2) qui prend un nombre entre 0 et 1, si on a 0 la led rouge s'allume, sinon la verte
  int controlLumiere = random(2);

  if(controlLumiere == 1){
    counter += 1;
    digitalWrite(ledVerte, HIGH);
    delay(700);
    digitalWrite(ledVerte, LOW);
    delay(200);
  } else{
    digitalWrite(ledRouge, HIGH);
    delay(700);
    digitalWrite(ledRouge,LOW);
    delay(200);
    counter = 0;
  }

  if (counter == 3 && digitalRead(button) == HIGH){ //succès
    //myServo.write(0); //on verra après pour l'angle
     //voir si on ajoute un reset ou pas (juste appelé setup? ou faire une autre fonction?)
    Serial.println("succès");
    tone(buzzer, 450);
    delay(500);
    noTone(buzzer);

  } else if(counter == 3 && digitalRead(button) == LOW) {
      counter = 0;
  
  }
    else if(counter != 3 && digitalRead(button) == HIGH){
      Serial.println("echec"); 
      counter = 0;
      tone(buzzer,200);
      delay(500);
      noTone(buzzer);  
  }

  
}

//void reset() {
  //myServo.write(180);
//}