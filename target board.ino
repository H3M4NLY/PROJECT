#define Hit_aPin 4 //define digital I/O pin D4 for Hit A
#define Hit_bPin 2 //define digital I/O pin D2 for Hit B
int counterA = 0; //number of hits received from Target board A
int counterB = 0; //number of hits received from Target board B


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Hit_aPin, INPUT_PULLUP); //Use Hit_aPin as digital INPUT_PULLUP pin
pinMode(Hit_bPin, INPUT_PULLUP); //Use Hit_bPin as digital INPUT_PULLUP pin
PCICR |= B00000100; // Enable interrupts on PD port (D0 to D7)
PCMSK2 |= B00010100; // Trigger interrupts on pins D2 and D4
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("hit a score is: ")
;
Serial.print(counterA);
Serial.println("\nhit b score is: ");
Serial.print(counterB);
Serial.println("\nready for next hit");
delay(1000);
}
//Below is the interrupt function to detect Hit a(pin D4)and Hit b (pin D2)
ISR (PCINT2_vect)
{
if (!digitalRead(Hit_bPin)) // if Hit_bPin is 0, Target B receives hit
counterB ++; //increase counterB by 1
else if (!digitalRead(Hit_aPin)) // if Hit_aPin is 0, Target A receives hit
counterA ++; //increase counterA by 1
}
