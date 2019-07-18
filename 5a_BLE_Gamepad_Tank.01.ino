/*
BLE Gamepad joystick control for tank
Edited: FBH
Date: 2019-07-18
Adapting previous code base that used an Arduino-based custom joystick
to use DFRobot Gamepad joystick controller; using DFRobot GoBLE mobile app example
for the RoMeo BLE board in the tank from the product page on DFRobot Devastator site;
there is a Gamepad Wiki which is called Basic Respones for reference
*/

#include <DFRobotBLEGamepad.h>

int speedPin_M1 = 6;    
int speedPin_M2 = 5;  
int directionPin_M1 = 7;    
int directionPin_M2 = 4;  

DFRobotBLEGamepad myDFRobotBLEGamepad;                                   
int joystickRightX, joystickRightY;  

void setup() {
  Serial.begin(115200);  
  myDFRobotBLEGamepad.begin(Serial);    
 }

void loop() {
  
  if ( myDFRobotBLEGamepad.available() ) {
    
    joystickRightX = myDFRobotBLEGamepad.readJoystickRightX();                       
    joystickRightY = myDFRobotBLEGamepad.readJoystickRightY(); 

    if (joystickRightX > 0 && joystickRightX < 100) { 
      Serial.println("turn right");
      carTurnRight(175, 175);
    }
    else if (joystickRightX > 150) { 
      Serial.println("turn left");
      carTurnLeft(175, 175);
    }
    else if (joystickRightY > 150) { 
      Serial.println("move forward");
      carAdvance(255, 255);
    }
    else if (joystickRightY > 0 && joystickRightY < 100) {  
      Serial.println("move backward");
      carBack(255, 255);
    }
    else {
      carStop(); 
    }
  }
}

void carStop() { 
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M1, HIGH);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M2, HIGH);
}

void carTurnLeft(int leftSpeed, int rightSpeed) {
  analogWrite (speedPin_M2, leftSpeed);          
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carTurnRight(int leftSpeed, int rightSpeed) { 
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}

void carBack(int leftSpeed, int rightSpeed) { 
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}
void carAdvance(int leftSpeed, int rightSpeed) { 
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}
