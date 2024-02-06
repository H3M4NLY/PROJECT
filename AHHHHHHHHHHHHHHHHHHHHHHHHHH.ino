#include <LiquidCrystal_I2C.h>

#include <LiquidCrystal.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define LS A0     // left sensor

#define RS A1    // right sensor


/*-------defining Outputs------*/

#define LM1 6      // left motor back

#define LM2 9     // left motor front

#define RM1 5     // right motor back

#define RM2 3       // right motor front

#define Hit_aPin 4 //define digital I/O pin D4 for Hit A

#define Hit_bPin 2 //define digital I/O pin D2 for Hit B

void moveforward(void);
void moveright(void);
void moveleft(void);
void stopyes(void);


int counterA = 0;
int counterB = 0;

void setup()
{
  Serial.begin(9600);

  TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

  PCICR |= B00000100; // Enable interrupts on PD port
  PCMSK2 |= B00010100; // Trigger interrupts on pins D2 and D4
  
  pinMode(Hit_aPin, INPUT_PULLUP); //Use Hit_aPin as digital INPUT_PULLUP pin
  
  pinMode(Hit_bPin, INPUT_PULLUP); //Use Hit_bPin as digital INPUT_PULLUP pin
  
  pinMode(LS, INPUT);

  pinMode(RS, INPUT);

  pinMode(LM1, OUTPUT);

  pinMode(LM2, OUTPUT);

  pinMode(RM1, OUTPUT);

  pinMode(RM2, OUTPUT);

  
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();

  interrupts();

}

void moveforward()
{
  
    digitalWrite(LM1, LOW);
    analogWrite(LM2, 150);
    digitalWrite(RM1, LOW);
    analogWrite(RM2, 150);
    delay(20);

}

void moveright(){


    digitalWrite(LM1, HIGH);

    digitalWrite(LM2, HIGH);

    digitalWrite(RM1, LOW);

    analogWrite(RM2, 150);

  
}

void stopyes(){
  
    digitalWrite(LM1, HIGH);

    analogWrite(LM2, HIGH);

    digitalWrite(RM1, HIGH);

    analogWrite(RM2, HIGH);
}

void moveleft(){

    digitalWrite(LM1, LOW);

    analogWrite(LM2, 150);

    digitalWrite(RM1, HIGH);

    digitalWrite(RM2, HIGH);

  
}

void loop(){
Serial.print("A:");
Serial.println(digitalRead(4));
Serial.print("/n B:");
Serial.println(digitalRead(2));

lcd.setCursor(0,0);
lcd.print("Deliveries Pending");
lcd.println(counterA);
lcd.setCursor(0,1);
lcd.print("Deliveries Complete:");
lcd.println(counterB);

moveforward();

  if(!(digitalRead(LS)) && !(digitalRead(RS)))     // Move Forward

  {
    moveforward();

  }

  

   else if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right

  {
    
    moveleft();

  }

  

  else if(digitalRead(LS) && !(digitalRead(RS)))     // turn left

  {


    moveright();


  }

  

  else if(digitalRead(LS) && digitalRead(RS))     // stop

  {
    stopyes();
  }
  }
  
ISR (PCINT2_vect) {
  if (!digitalRead(2)){
    counterA++;
    
  }
  else if (!digitalRead(4)){
    counterB++;
  }
}
