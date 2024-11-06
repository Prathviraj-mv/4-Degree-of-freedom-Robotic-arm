#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;
const int potPin4 = A3;
const int potPin5 = A4;

const int servoPin1 = 3;
const int servoPin2 = 5;
const int servoPin3 = 6;
const int servoPin4 = 9;
const int servoPin5 = 10;

void setup() {
  // Attach each servo to its pin
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
}

void loop() {
  // Read each potentiometer and set corresponding servo position
  int potValue1 = analogRead(potPin1);
  int angle1 = map(potValue1, 0, 1023, 0, 180);
  servo1.write(angle1);

  int potValue2 = analogRead(potPin2);
  int angle2 = map(potValue2, 0, 1023, 0, 180);
  servo2.write(angle2);

  int potValue3 = analogRead(potPin3);
  int angle3 = map(potValue3, 0, 1023, 0, 180);
  servo3.write(angle3);

  int potValue4 = analogRead(potPin4);
  int angle4 = map(potValue4, 0, 1023, 0, 180);
  servo4.write(angle4);

  int potValue5 = analogRead(potPin5);
  int angle5 = map(potValue5, 0, 1023, 0, 180);
  servo5.write(angle5);

  delay(15); // Short delay to allow the servos to move smoothly
}
