#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN 150
#define SERVO_MAX 600
#define SMOOTHNESS 5  // Reduce to make smoother and less twitchy
#define THRESHOLD 10   // Threshold for potentiometer changes
#define DEADZONE 5     // Deadzone to avoid tiny changes

const int potPins[] = {A1, A2, A3, A6, A7};
int potValues[5] = {0, 0, 0, 0, 0};
int lastPotValues[5] = {0, 0, 0, 0, 0};

const int servoChannels[] = {0, 1, 2, 3, 4};

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);  // Frequency for servos
  for (int i = 0; i < 5; i++) {
    potValues[i] = analogRead(potPins[i]);
  }
}

void loop() {
  int totalAngle = 0;

  for (int i = 0; i < 5; i++) {
    int potValue = analogRead(potPins[i]);

    // Apply deadzone to reduce small changes and avoid jitter
    if (abs(potValue - lastPotValues[i]) > THRESHOLD) {
      lastPotValues[i] = potValue;
      if (i == 4) {  // A7 (base), 360-degree range
        potValues[i] = map(potValue, 0, 1023, 0, 360);
      } else {  // Other servos, 180-degree range
        potValues[i] = map(potValue, 0, 1023, 0, 180);
      }
    }

    totalAngle += potValues[i];
  }

  // Update servos with smoothed values
  for (int i = 0; i < 5; i++) {
    int currentAngle = potValues[i];
    int pulseWidth;

    if (i == 4) {  // A7 (base), 360 degrees
      pulseWidth = map(currentAngle, 0, 360, SERVO_MIN, SERVO_MAX);
    } else {  // Other servos, 180 degrees
      pulseWidth = map(currentAngle, 0, 180, SERVO_MIN, SERVO_MAX);
    }

    moveServoSmoothly(servoChannels[i], pulseWidth);
  }

  delay(20);  // Shorter delay for more responsiveness
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
