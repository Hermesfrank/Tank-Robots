/* 
BLE Joystick
Edited: FBH
Date: 2019-07-18
Code base uses my previous where I used educs8.tv example for using HC-05 modules;
so, here I remove HC-05 from joystick and replace with a DFRobot BLE module;
change baud rate to 115200.
Single joystick control.
*/

int xAxis, yAxis;

void setup() {
  Serial.begin(115200);                     // Communication rate of the BLE module
}
void loop() {
  xAxis = analogRead(A0);                   // Read Joysticks X-axis
  yAxis = analogRead(A1);                   // Read Joysticks Y-axis

                                            // Send the values via the serial port to the slave Romeo BLE device
  Serial.write(xAxis/4);                    // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.write(yAxis/4);

                                            // Uncomment to check output of joystick values
/*
  Serial.print("X-axis: ");
  Serial.print(xAxis);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(yAxis);
  Serial.print("\n\n");
  delay(500);
*/ 
  delay(20);
}
