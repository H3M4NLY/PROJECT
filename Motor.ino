#define motor_board_input_pin_IN4 6 
#define motor_board_input_pin_IN3 9
#define motor_board_input_pin_IN2 5 
#define motor_board_input_pin_IN1 3 
void Full_speed_forward();
void Full_speed_backward();
void From_0_to_100_forward();
void From_100_to_0_backward();
void brake();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(motor_board_input_pin_IN4, OUTPUT);
pinMode(motor_board_input_pin_IN3, OUTPUT);
pinMode(motor_board_input_pin_IN2, OUTPUT);
pinMode(motor_board_input_pin_IN1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Full_speed_forward();
brake();
delay(1000);
Full_speed_backward();
brake();
delay(1000);
From_0_to_100_forward();
brake();
delay(1000);
From_100_to_0_backward();
brake();
delay(1000);
}

void Full_speed_forward(){
Serial.println("Full speed forward for 2s");
digitalWrite(motor_board_input_pin_IN2, HIGH);
digitalWrite(motor_board_input_pin_IN1, LOW);
digitalWrite(motor_board_input_pin_IN4, HIGH);
digitalWrite(motor_board_input_pin_IN3, LOW);
delay(2000);
}
void Full_speed_backward(){
Serial.println("Full speed backward for 2s");
digitalWrite(motor_board_input_pin_IN2, LOW);
digitalWrite(motor_board_input_pin_IN1, HIGH);
digitalWrite(motor_board_input_pin_IN4, LOW);
digitalWrite(motor_board_input_pin_IN3, HIGH);
delay(2000);
}

void From_0_to_100_forward(){
Serial.println("0 to 100% speed forward");
for (int i=0;i<=255;i++){
digitalWrite(motor_board_input_pin_IN1, LOW);
analogWrite(motor_board_input_pin_IN2, i);
digitalWrite(motor_board_input_pin_IN3, LOW);
analogWrite(motor_board_input_pin_IN4, i);
delay(20);
}
}

void From_100_to_0_backward(){
Serial.println("100% to 0 speed backward");
for (int i=0;i<=255;i++){ 
digitalWrite(motor_board_input_pin_IN1, HIGH);
analogWrite(motor_board_input_pin_IN2, i); //when i=0, the motor at fullspeed backward initially
digitalWrite(motor_board_input_pin_IN3, HIGH);
analogWrite(motor_board_input_pin_IN4, i);


delay(20);
}
}
void brake(){
Serial.println("Brake");
digitalWrite(motor_board_input_pin_IN1, LOW);
digitalWrite(motor_board_input_pin_IN3, LOW);
analogWrite(motor_board_input_pin_IN2, LOW);
digitalWrite(motor_board_input_pin_IN4, LOW);
}
