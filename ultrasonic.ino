#define TrigPin 11
#define EchoPin 10
#define IR1Pin A0

#include <avr/interrupt.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
long duration;
int distance;
#define motorPin_IN2 6 //Connect to Arduino pin 6
#define motorPin_IN1 9 //Connect to Arduino pin 9
#define motorPin_IN4 3 //Connect to Arduino pin 3
#define motorPin_IN3 5 //Connect to Arduino pin 5


void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(motorPin_IN4, OUTPUT);
  pinMode(motorPin_IN3, OUTPUT);
  pinMode(motorPin_IN2, OUTPUT);
  pinMode(motorPin_IN1, OUTPUT);
  
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  interrupts();
}


void loop()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TrigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  
  duration = pulseIn(EchoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds

  distance = duration * 0.034 / 2; // Calculating the distance
  
  Serial.print("Distance: "); // Prints the distance on the Serial Monitor
  Serial.println(distance);

  if (digitalRead(IR1Pin)==0) {
    lcd.setCursor(0,0);
    lcd.print("STOP           ");
    digitalWrite(motorPin_IN2, LOW);
    digitalWrite(motorPin_IN1, LOW);
    digitalWrite(motorPin_IN4, LOW);
    digitalWrite(motorPin_IN3, LOW);
    delay(500);
  }
  
  else 
  {
    lcd.setCursor(0,0);
    lcd.print("In Delivery");
    digitalWrite(motorPin_IN2, HIGH);
    digitalWrite(motorPin_IN1, LOW);
    digitalWrite(motorPin_IN4, LOW);
    digitalWrite(motorPin_IN3, HIGH);

  }

 for (;;){
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  duration = pulseIn(EchoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculating the distance
  
  if (distance >=50){
    lcd.setCursor(0,1);
    lcd.print("          ");
    break;
    delay(20);
  }

  else if (distance !=0 ){
    lcd.setCursor(0,1);
    lcd.print("Obstacle!");
    Serial.print("Distance: ");
    Serial.println(distance);
    digitalWrite(motorPin_IN2, LOW);
    digitalWrite(motorPin_IN1, LOW);
    digitalWrite(motorPin_IN4, LOW);
    digitalWrite(motorPin_IN3, LOW);
    delay(20);
  }
  
  }
  }



 
