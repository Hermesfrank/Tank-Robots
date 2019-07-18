/*
# Edited: FBH
# Date: 2019-07-18
# Coding using DFRobot BLE/iPhone example from Devastator product page for the RoMeo BLE board
# integrated with code from educs8.tv example for using HC-05 BT modules; placing HC-05
# on tank in lieu of using the integrated BLE of the RoMeo BLE; implement Software.Serial
# for the standard serial since the embedded BLE is connected to the RoMeo BLE TX/RX pins.
# Single joystick control.
*/

                                                                      // include libraries
#include <SoftwareSerial.h>                                           // using this to avoid conflict with embedded BLE
#include <Servo.h>

                                                                      // assign motor pins and direction pins
int speedPin_M1 = 5;                                                  // M1 Speed Control
int speedPin_M2 = 6;                                                  // M2 Speed Control
int directionPin_M1 = 4;                                              // M1 Direction Control
int directionPin_M2 = 7;                                              // M2 Direction Control

int joystickX, joystickY;                                             // create joystick variables

SoftwareSerial mySerial(10, 11);                                      // RX uses pin D10, TX D11 

void setup() {                                                        // the setup function runs once
  mySerial.begin(38400);                                              // serial communication speed
}

void loop() {                                                         // the main loop
  if (mySerial.available()) {                                         // check for a bluetooth connection
    
    while (mySerial.available() >= 2) {                               // make sure the serial buffer has enough data
      joystickX = mySerial.read();                                    // read joystick x value
      delay (10);
      joystickY = mySerial.read();                                    // ead joystick y value
    }
    delay (10); 

    if (joystickY > 196) {                                            // if joystick y > 196 then turn left at speed 250
      Serial.println("turn left");
      carTurnLeft(250, 250);
    }
    else if (joystickY < 64) {                                        // if joystick y < 64 then turn right at speed 250
      Serial.println("turn right");
      carTurnRight(250, 250);
    }
    else if (joystickX > 196) {                                       // if joystick x > 196 then go forward at speed 500
      Serial.println("move forward");
      carAdvance(500, 500);
    }
    else if (joystickX < 64) {                                        // if joystick x <64 then go backward at speed 500
      Serial.println("move backward");
      carBack(500, 500);
    }
    else {
      carStop();                                                      // or else stop
    }
  }
}

                                                                      // tank movement functions

void carStop() {                                                      // totor Stop
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M2, LOW);
}

void carTurnLeft(int leftSpeed, int rightSpeed) {                     // turn Left
  analogWrite (speedPin_M2, leftSpeed);                               // typical PWM Speed Control
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}

void carTurnRight(int leftSpeed, int rightSpeed) {                    // turn Right
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carBack(int leftSpeed, int rightSpeed) {                         // move backward
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}
void carAdvance(int leftSpeed, int rightSpeed) {                      // move forward
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}
