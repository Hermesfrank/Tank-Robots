/*
BLE Gamepad joystick control for tank
Edited: FBH
Date: 2019-07-18
Adapting previous code base that used an Arduino-based custom joystick
to use DFRobot Gamepad joystick controller; using DFRobot GoBLE mobile app example
for the RoMeo BLE board in the tank from the product page on DFRobot Devastator site;
there is a Gamepad Wiki which is called Basic Respones for reference;
additionally, changing motor control code to use both right and left
joystick Y axis-only (rather than singkle joystick X & Y axis) so can do
true tank drive/steering w/throttle control.
*/

#include <DFRobotBLEGamepad.h>

int speedPin_MLeft = 6;                                              
int speedPin_MRight = 5;                                              
int directionPin_MLeft = 7;                                            
int directionPin_MRight = 4;                                           

DFRobotBLEGamepad myDFRobotBLEGamepad;
                                   
int joystickLeftY, joystickRightY;

void setup() {
  Serial.begin(115200);
  myDFRobotBLEGamepad.begin(Serial);    
}

void loop() {  

  if ( myDFRobotBLEGamepad.available() ) {                               

    joystickRightY = myDFRobotBLEGamepad.readJoystickLeftY();                       
    joystickLeftY = myDFRobotBLEGamepad.readJoystickRightY(); 
    
    if (joystickLeftY >= 200) {
      Serial.println("left forward");
      digitalWrite(speedPin_MLeft, 255);
      digitalWrite(directionPin_MLeft, LOW);
    }
    if (joystickLeftY > 0 & joystickLeftY <= 50) {                                     
      Serial.println("left reverse");
      digitalWrite(speedPin_MLeft, 255);        // map(joystickLeftY, 120, 1, 0, 255));
      digitalWrite(directionPin_MLeft, HIGH);
    }
    if (joystickLeftY = 0 || (joystickLeftY > 50 & joystickLeftY < 200)) {
      Serial.println("left stop");
      digitalWrite(speedPin_MLeft, 0);
      digitalWrite(directionPin_MLeft, LOW);
    }
    
    if (joystickRightY >= 200) {                                       
      Serial.println("right forward");
      digitalWrite(speedPin_MRight, 255);
      digitalWrite(directionPin_MRight, LOW);
    }
    if (joystickRightY > 0 & joystickRightY <= 50) {                                    
      Serial.println("right reverse");
      digitalWrite(speedPin_MRight, 255);             // map(joystickRightY, 120, 1, 0, 255));
      digitalWrite(directionPin_MRight, HIGH);
    }
    if (joystickRightY = 0 || (joystickRightY > 50 & joystickRightY < 200)) {
      Serial.println("right stop");
      digitalWrite(speedPin_MRight, 0);
      digitalWrite(directionPin_MRight, LOW);
    }
  }
}
