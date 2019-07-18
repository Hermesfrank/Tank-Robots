/*
BLE TANK CUSTOM JOYSTICK PACKETIZED
Code adaptation: FBH
Date: 2019-07-18
Added packet protocol for data integrity
Code base uses my previous code for the imbedded BLE of RoMeo BLE board
*/

                                                                    // assign motor pins and direction pins
int speedPin_M1 = 5;                                                // M1 Speed Control
int speedPin_M2 = 6;                                                // M2 Speed Control
int directionPin_M1 = 4;                                            // M1 Direction Control
int directionPin_M2 = 7;                                            // M2 Direction Control

const byte numBytes = 32;                                           // set up for packet/array
byte receivedBytes[numBytes];
byte numReceived = 0;
boolean newData = false;

int joystickX = 127;
int joystickY = 127;

void setup() {
  Serial.begin(115200);                                             // initiate serial communication speed
}

void loop() {
    recvBytesWithStartEndMarkers();                                 // get dat and place elements into an array
    useNewData();                                                   // place joystick values into variables
    moveTank();                                                     // use joysticks to run tank
}

void recvBytesWithStartEndMarkers() {  
    static boolean recvInProgress = false;
    static byte ndx = 0;
    byte startMarker = 0x3C;
    byte endMarker = 0x3E;
    byte rb;
 
    while (Serial.available() > 0 && newData == false) {
        rb = Serial.read();

        if (recvInProgress == true) {
            if (rb != endMarker) {
                receivedBytes[ndx] = rb;
                ndx++;
                if (ndx >= numBytes) {
                    ndx = numBytes - 1;
                }
            }
            else {
                receivedBytes[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                numReceived = ndx;  // save the number for use when printing
                ndx = 0;
                newData = true;
            }
        }

        else if (rb == startMarker) {
            recvInProgress = true;
        }
    }
}

void useNewData() {
      if (newData == true) {
        for (byte n = 0; n < numReceived; n++) {
          joystickX = receivedBytes[0];
          // byte 1 is the separating comma
          joystickY = receivedBytes[2];
        }
        newData = false;  
      }
}      

void moveTank() {
    if (joystickY > 196) {                                          // if joystick y > 196 then turn right at speed 175
      Serial.println("turn right");
      carTurnRight(175, 175);
    }
    else if (joystickY < 64) {                                      // if joystick y < 64 then turn left at speed 175
      Serial.println("turn left");
      carTurnLeft(175, 175);
    }
    else if (joystickX > 196) {                                     // if joystick x > 196 then go backward at speed 255
      Serial.println("move backward");
      carAdvance(255, 255);
    }
    else if (joystickX < 64) {                                      // if joystick x <64 then go forward at speed 255
      Serial.println("move forward");
      carBack(255, 255);
    }
    else {
      carStop();                                                    // or else stop
      Serial.println("stopped");
    }
}

void carStop() {                                                    // motor Stop
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M2, LOW);
}

void carTurnLeft(int leftSpeed, int rightSpeed) {                   // turn Left
  analogWrite (speedPin_M2, leftSpeed);                             // typical PWM Speed Control
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carTurnRight(int leftSpeed, int rightSpeed) {                  // turn Right
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}

void carBack(int leftSpeed, int rightSpeed) {                       // move backward
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}
void carAdvance(int leftSpeed, int rightSpeed) {                    // move forward
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}
