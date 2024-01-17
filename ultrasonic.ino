#define TrigPin 11
#define EchoPin 10
#define IR1Pin A0

#include <avr/interrupt.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
long duration;
int distance;

void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
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
  }
  
  else 
  {
  lcd.setCursor(0,0);
  lcd.print("In Delivery");
  }



  if (distance <=50){
    lcd.setCursor(0,1);
    lcd.print("Obstacle!");
    Serial.print("Distance: ");
  	Serial.println(distance);
  }

  else{
    lcd.setCursor(0,1);
    lcd.print("          ");
  }
}
