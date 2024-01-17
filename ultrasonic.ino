#define TrigPin 11
#define EchoPin 10
#include <avr/interrupt.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
long duration;
int distance;

void setup()
{

  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  PCICR |= B00000100; // Enable interrupts on PD port
  PCMSK2 |= B00010000; // Trigger interrupts on pins D4 (Hit a)
  
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
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(EchoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  
  Serial.print("Distance: ");
  Serial.println(distance);

  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.print(distance);

  if (distance <=50){
    lcd.setCursor(0, 0);
  	lcd.print("Distance:");
  	lcd.print(distance);
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