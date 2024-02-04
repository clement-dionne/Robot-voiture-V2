#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#include <SoftwareSerial.h>


SoftwareSerial HC06(13,12);
String messageRecu;

const byte TRIGGER_PIN = 3; // Broche TRIGGER
const byte ECHO_PIN = 4;    // Broche ECHO

const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;


int V = 80;

float Xvoiture = 0;
float Yvoiture = 0;

int RotationVoiture = 0;

long measure;
float distance_mm;
float cm;

//////////////////////////////////// setup //////////////////////

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  Serial.begin(9600);
  HC06.begin(9600); 
  pinMode(2, OUTPUT); 
 }
 
///////////////////////////// loop ///////////

/*      CMD :
 *       
 *       1 - TEST Functions : --------------------------
 *       
 *       TestMotors( NewVitesse );  Tester les fonctions 'Moov' avec une vitesse 'NewVitesse' donnée
 *       
 *       2 - Sensors INFO Functions : --------------------------
 *       
 *       RadarAvant();  Recuperer en Cm la distance de l'obstacle le plus proche
 *              
 *       3 - Moov Functions : --------------------------
 *       
 *       Avant();       Avancer
 *       Arr();         Reculer
 *       Droite();      Tourner a droite
 *       Gauche();      "       " gauche
 *       
 *       AvantD();      Avancer a droite
 *       AvantG();      "       " gauche
 *       
 *       ArrD();        Reculer a droite
 *       ArrG();        "       " gauche
 *       
 *       STOP();        Arreter les moteurs
 *       
 *       4 - OTHER Functions : --------------------------
 *       
 */

void loop() {
  Avant();
  delay(250);
  STOP();

  Arr();
  delay(250);
  STOP();
}

void STOP(){
  analogWrite(ENA,LOW);
  analogWrite(ENB,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);  
}

void ArrG(){
  analogWrite(ENA,V%2);
  analogWrite(ENB,V);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void ArrD(){
  analogWrite(ENA,V);
  analogWrite(ENB,V%2);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void AvantG(){
  analogWrite(ENA,V%2);
  analogWrite(ENB,V);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void AvantD(){
  analogWrite(ENA,V);
  analogWrite(ENB,V%2);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void Gauche(){
  V = 119;
  analogWrite(ENA,V);
  analogWrite(ENB,V);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(676);
  V = 80;
}

void Droite(){
  V = 119;
  analogWrite(ENA,V);
  analogWrite(ENB,V);
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);  
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,HIGH); 
  delay(685);
  V = 80;
}

void Arr(){
  analogWrite(ENB,V);
  analogWrite(ENA,V);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
}

void Avant(){
  analogWrite(ENB,V);
  analogWrite(ENA,V);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(250);
}

void TestMotors(int TestV){
  V = TestV;
  Avant();
  delay(500);
  Arr();
  delay(500);
  Droite();
  delay(500);
  Gauche();
  delay(500);
  AvantD();
  delay(500);
  AvantG();
  delay(500);
  ArrD();
  delay(500);
  ArrG();
  delay(500);
  STOP();
  delay(500);
  V = 250;
}

float RadarAvant(){
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  distance_mm = measure / 2.0 * SOUND_SPEED;
  cm = distance_mm / 10.0, 2;
  return cm ;    
}

/*  
  if( distance < 30 && distance > 1 ){
    
    Arr();
    V = 119;
    Droite();
    delay(275);
    V = 80;
       
  }

 
  if(distance < 100 && distance > 30){
    
      V = 80;
      Avant();
    
  }
  if(distance < 200 && distance > 100){
    
      V = 120;
      Avant();
    
  }

  if(distance < 400 && distance > 200){
    
      V = 180;
      Avant();
    
  }
  
////////////////////////////////////////////////

  char c = HC06.read();
  messageRecu += c;
  if (messageRecu.length() >0)
  {
      Serial.println(messageRecu);
      if (messageRecu.indexOf("SetX=")) {  }
      messageRecu="";
  }
*/
