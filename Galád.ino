// HC-SR04, ultazvukovy senzor, nastavenie pinov
const int vysielaciPin = 17;
const int prijimaciPin = 16;
//sirenie zvuku
#define SOUND_VELOCITY 0.034
//#define CM_TO_INCH 0.393701
// definovanie premennych (trvanie, vzdialenost, 5x LED, 1x Generator zvuku)
long trvanie; 
float vzdialenostCm;
int led10cm = 2;
int led15cm = 5;
int led20cm = 4;
int led25cm = 18;
int led35cm = 19;
int gen = 21;

void setup() {
  // Zapnutie seriovej komunikacie pre vypis na obrazovku a nastavanie pinov (vstup/vystup)
  Serial.begin(115200); 
  pinMode(vysielaciPin, OUTPUT);
  pinMode(prijimaciPin, INPUT);
  pinMode(led10cm, OUTPUT);
  pinMode(led15cm, OUTPUT);
  pinMode(led20cm, OUTPUT);
  pinMode(led25cm, OUTPUT);
  pinMode(led35cm, OUTPUT);
  pinMode(gen, OUTPUT);
}

void loop() {
  digitalWrite(vysielaciPin, LOW);
  delayMicroseconds(2);
  digitalWrite(vysielaciPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(vysielaciPin, LOW);
  
  trvanie = pulseIn(prijimaciPin, HIGH);
  
  // Vypocet vzdialenosti / 2
  vzdialenostCm = trvanie * SOUND_VELOCITY/2;
  
  
  // Vypisanie vzdialenosti na monitor
  Serial.print("Vzdialenost (cm): ");
  Serial.println(vzdialenostCm);
  // Podmienky pre vypocet vzdialenosti a rozsvietenie LED, gen.
if (vzdialenostCm <= 10) {
    digitalWrite(led10cm, HIGH); 
    digitalWrite(led15cm, LOW);
    digitalWrite(led20cm, LOW);
    digitalWrite(led25cm, LOW); 
    digitalWrite(led35cm, LOW);   
} else if (vzdialenostCm > 10 && vzdialenostCm <= 15) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH); 
    digitalWrite(led20cm, LOW);  
    digitalWrite(led25cm, LOW);
    digitalWrite(led35cm, LOW);
} else if (vzdialenostCm > 15 && vzdialenostCm <= 20) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH);  
    digitalWrite(led20cm, HIGH); 
    digitalWrite(led25cm, LOW);
    digitalWrite(led35cm, LOW);
} else if (vzdialenostCm > 20 && vzdialenostCm <= 25) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH);  
    digitalWrite(led20cm, HIGH); 
    digitalWrite(led25cm, HIGH);
    digitalWrite(led35cm, LOW);
} else if (vzdialenostCm > 25 && vzdialenostCm <= 35) {
    digitalWrite(led10cm, HIGH);  
    digitalWrite(led15cm, HIGH);  
    digitalWrite(led20cm, HIGH);
    digitalWrite(led25cm, HIGH);
    digitalWrite(led35cm, HIGH);
    tone (gen, 300,500);
    noTone(gen);  
}
else {
    digitalWrite(led10cm, LOW);
    digitalWrite(led15cm, LOW);
    digitalWrite(led20cm, LOW);
    digitalWrite(led25cm, LOW);
    digitalWrite(led35cm, LOW);
}
  delay(1000);
}