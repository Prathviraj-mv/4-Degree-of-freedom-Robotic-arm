#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN 150
#define SERVO_MAX 600
#define SMOOTHNESS 5
#define THRESHOLD 10
#define DEADZONE 5

const int potPins[] = {A1, A2, A3, A6, A7};
int potValues[5];
int lastPotValues[5];
const int servoChannels[] = {0, 1, 2, 3, 4};

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);

  for (int i = 0; i < 5; i++) {
    potValues[i] = analogRead(potPins[i]);
    lastPotValues[i] = potValues[i];

    int mappedValue;
    if (i == 4) { // A7 (360 degrees)
      mappedValue = map(potValues[i], 0, 1023, 0, 360);
    } else { // Other servos (180 degrees)
      mappedValue = map(potValues[i], 0, 1023, 0, 180);
    }
    int initialPulse = map(mappedValue, i == 4 ? 0 : 0, i == 4 ? 360 : 180, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servoChannels[i], 0, initialPulse);
  }
}

void loop() {
  int potA1 = analogRead(potPins[0]);
  int potA2 = analogRead(potPins[1]);
  int potA3 = analogRead(potPins[2]);
  int potA6 = analogRead(potPins[3]);
  int potA7 = analogRead(potPins[4]);

  if (abs(potA1 - lastPotValues[0]) > THRESHOLD) {
    lastPotValues[0] = potA1;
    potValues[0] = map(potA1, 0, 1023, 0, 180);
  }
  if (abs(potA2 - lastPotValues[1]) > THRESHOLD) {
    lastPotValues[1] = potA2;
    potValues[1] = map(potA2, 0, 1023, 0, 180);
  }
  if (abs(potA3 - lastPotValues[2]) > THRESHOLD) {
    lastPotValues[2] = potA3;
    potValues[2] = map(potA3, 0, 1023, 0, 180);
  }
  if (abs(potA6 - lastPotValues[3]) > THRESHOLD) {
    lastPotValues[3] = potA6;
    potValues[3] = map(potA6, 0, 1023, 0, 180);
  }
  if (abs(potA7 - lastPotValues[4]) > THRESHOLD) {
    lastPotValues[4] = potA7;
    potValues[4] = map(potA7, 0, 1023, 0, 360);
  }

  int pulseWidthA1 = map(potValues[0], 0, 180, SERVO_MIN, SERVO_MAX);
  moveServoSmoothly(servoChannels[0], pulseWidthA1);

  int pulseWidthA2 = map(potValues[1], 0, 180, SERVO_MIN, SERVO_MAX);
  moveServoSmoothly(servoChannels[1], pulseWidthA2);

  int pulseWidthA3 = map(potValues[2], 0, 180, SERVO_MIN, SERVO_MAX);
  moveServoSmoothly(servoChannels[2], pulseWidthA3);

  int pulseWidthA6 = map(potValues[3], 0, 180, SERVO_MIN, SERVO_MAX);
  moveServoSmoothly(servoChannels[3], pulseWidthA6);

  int pulseWidthA7 = map(potValues[4], 0, 360, SERVO_MIN, SERVO_MAX);
  moveServoSmoothly(servoChannels[4], pulseWidthA7);

  delay(20);
}

void moveServoSmoothly(int channel, int targetPulse) {
  static int currentPulse[5] = {SERVO_MIN, SERVO_MIN, SERVO_MIN, SERVO_MIN, SERVO_MIN};

  if (currentPulse[channel] != targetPulse) {
    if (currentPulse[channel] < targetPulse) {
      currentPulse[channel] += SMOOTHNESS;
    } else {
      currentPulse[channel] -= SMOOTHNESS;
    }

    if (currentPulse[channel] > SERVO_MAX) {
      currentPulse[channel] = SERVO_MAX;
    }
    if (currentPulse[channel] < SERVO_MIN) {
      currentPulse[channel] = SERVO_MIN;
    }

    pwm.setPWM(channel, 0, currentPulse[channel]);
  }
}
