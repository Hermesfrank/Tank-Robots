/* Arduino Wireless Control using Arduino and HC-05 Bluetooth
   Use AT mode to set joystick as MASTER and tank as SLAVE

   Original code by Dejan Nedelkovski, www.HowToMechatronics.com
   Adapted by: FBH
   Last edited 2019-07-18
*/
int xAxis, yAxis;                 // setup variables for the joystick axis

void setup() {
  Serial.begin(38400);            // initiate Bluetooth module
}
void loop() {
  xAxis = analogRead(A0);         // Read Joysticks X-axis
  yAxis = analogRead(A1);         // Read Joysticks Y-axis

                                  // Send the values via the serial port to the slave HC-05 Bluetooth device
  Serial.write(xAxis/4);          // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
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
  delay(20);                      // spacing for serial buffer
}
