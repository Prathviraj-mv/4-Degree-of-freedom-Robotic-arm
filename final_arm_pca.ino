#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN 150
#define SERVO_MAX 600
#define DEADZONE 10
#define STEP_ANGLE 5

const int potPins[] = {A1, A2, A3, A6, A7};
const int servoChannels[] = {0, 1, 2, 3, 4};
int lastPotValues[5];
int targetAngles[5] = {0, 0, 0, 0, 0};
int currentAngles[5] = {0, 0, 0, 0, 0};

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);

  for (int i = 0; i < 5; i++) {
    lastPotValues[i] = analogRead(potPins[i]);
    
    targetAngles[i] = map(lastPotValues[i], 0, 1023, 0, (i == 4 ? 360 : 180));
    targetAngles[i] -= (targetAngles[i] % STEP_ANGLE);
    currentAngles[i] = targetAngles[i];
    
    int initialPulse = map(currentAngles[i], 0, (i == 4 ? 360 : 180), SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servoChannels[i], 0, initialPulse);
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    int potValue = analogRead(potPins[i]);

    if (abs(potValue - lastPotValues[i]) > DEADZONE) {
      lastPotValues[i] = potValue;

      targetAngles[i] = map(potValue, 0, 1023, 0, (i == 4 ? 360 : 180));
      targetAngles[i] -= (targetAngles[i] % STEP_ANGLE);
    }
    
    if (currentAngles[i] < targetAngles[i]) {
      currentAngles[i] += STEP_ANGLE;
    } else if (currentAngles[i] > targetAngles[i]) {
      currentAngles[i] -= STEP_ANGLE;
    }
    
    int pulseWidth = map(currentAngles[i], 0, (i == 4 ? 360 : 180), SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servoChannels[i], 0, pulseWidth);
  }
  delay(50); // Slow movement
}
