#define RLED_PIN    2
#define GLED_PIN    3
#define POWER_PIN   7
#define SIGNAL_PIN  A5
#define THRESHOLD   300
int bouton = 5;

int value = 0;

void setup() {
  pinMode(bouton,INPUT);
  pinMode(RLED_PIN,   OUTPUT);
  pinMode(GLED_PIN,   OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW);
  digitalWrite(RLED_PIN,   HIGH);
  digitalWrite(GLED_PIN,   LOW);
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);
  //delay(10);
  value = analogRead(SIGNAL_PIN);
  digitalWrite(POWER_PIN, LOW);
  if(digitalRead(bouton)==HIGH){
    if (value > THRESHOLD) {
      digitalWrite(GLED_PIN, HIGH);
      digitalWrite(RLED_PIN, LOW);
      //Son Vicrtoire
      //Moteur
    } else {
      digitalWrite(RLED_PIN, HIGH);
      digitalWrite(GLED_PIN, LOW);
      //son défaite
    } 
  }
}
