#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int potPins[] = {A1, A2, A3, A6, A7};
const int numPots = 5;

const int servoMin = 150;
const int servoMax_180 = 600;
const int servoMax_360 = 1000;
const int threshold = 5;
const int servoChannel[] = {0, 1, 2, 3, 4};

int lastPotValues[numPots] = {0};

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  for (int i = 0; i < numPots; i++) {
    int potValue = analogRead(potPins[i]);
    int mappedValue = map(potValue, 0, 1023, servoMin, (i == 0 ? servoMax_360 : servoMax_180));

    if (abs(potValue - lastPotValues[i]) > threshold) {
      lastPotValues[i] = potValue;

      int targetPulse = mappedValue;
      int currentPulse = pwm.getPWM(servoChannel[i]);
      int step = (targetPulse > currentPulse) ? 5 : -5;

      for (int pulse = currentPulse; abs(targetPulse - pulse) > abs(step); pulse += step) {
        pwm.setPWM(servoChannel[i], 0, pulse);
        delay(20);
      }

      pwm.setPWM(servoChannel[i], 0, targetPulse);
    }
  }
  delay(100);
}
