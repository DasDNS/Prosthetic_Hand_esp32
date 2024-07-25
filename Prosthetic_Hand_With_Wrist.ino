//Five servo motors for the five fingers - connected to 5 rotary switches (potentiometers)
//A servo motor to control all five fingers at once - connected to a rotary switch (potentiometer)
//A differential drive for the wrist - powered by 2 DC motors with a motor drive - controlled by a joystick

//Define two DC motor pins 
#define IN1_PIN 12; //direction of Motor A
#define IN2_PIN 11; //direction of Motor A
#define ENA_PIN 13; //speed of Motor A
#define IN3_PIN 10; //direction of Motor B
#define IN4_PIN 9; //direction of Motor B
#define ENB_PIN 8; //speed of motor B

int motorSpeedA = 0;
int motorSpeedB = 0;


void setup() {

  // Set up DC motor pins
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

}

void loop() {

  joystickControl();
  
}

void joystickControl () {

  int xAxis = analogRead(4); //Read X-axis (VRx)
  int yAxis = analogRead(5); //Read Y-axis (VRy)

  //Y-axis for forward/backward control
  if (yAxis < 470) { //joystick is pushed backward

    //set Motor A backward
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    //set Motor B backward
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);

    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
    //mapping motor speeds from Y-axis value (0-470) to the PWM range

  } else if (yAxis > 550) { //joystick is pushed forward

    //set Motor A forward
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
    //set Motor B forward
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);

    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    //mapping motor speeds from Y- axis value (550-1023) to the PWM range

  } else {
    //is Y-axis value is between 470 and 550, stop both motors.
    motorSpeedA = 0;
    motorSpeedB = 0;

  }

  //X-axis for left/right control
  if (xAxis < 470) { //joystick is moved left
    //Adjust the motor speeds based on X-axis values (0-255)
    int xMapped = map(xAxis, 470, 0, 0, 255);
    //Subtract the mapped X-axis value from motorSpeedA and add it to motorSpeedB
    motorSpeedA -= xMapped;
    motorSpeedB += xMapped;
    //ensuring motor speeds stay within the valid range (0-255)
    if (motorSpeedA < 0) motorSpeedA = 0;
    if (motorSpeedB > 255) motorSpeedB = 255;

  } else if (xAxis > 550) { //joystick is moved right
    //Adjust the motor speeds based on X-axis values (0-255)
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    //Add the mapped X-axis value from motorSpeedB and subtarct it to the motorSpeedA
    motorSpeedB += xMapped;
    motorSpeedA -= xMapped;
    //ensuring motor speeds stay within the valid range (0-255)
    if (motorSpeedA > 255) motorSpeedA = 255;
    if (motorSpeedB < 0) motorSpeedB = 0;

  }
  //set motor speeds
  analogWrite(ENA_PIN, motorSpeedA);
  analogWrite(ENB_PIN, motorSpeedB);

}
