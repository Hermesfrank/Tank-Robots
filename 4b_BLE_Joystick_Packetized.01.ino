/* 
BLE Arduino with Custom Joystick Packetized.01
Code adaptation: FBH
Date: 2019-07-18
Added packet protocol for data integrity
Code base uses my previous code for the imbedded BLE of RoMeo BLE board
*/

int xAxis, yAxis;

void setup() {
  Serial.begin(115200);                     // Communication rate of the BLE module
}
void loop() {
  xAxis = analogRead(A0);                   // Read Joysticks X-axis
  yAxis = analogRead(A1);                   // Read Joysticks Y-axis

  if (xAxis == 60 || xAxis == 62) {
    xAxis = 61;
  }
  
  if (yAxis == 60 || yAxis == 62) {
    yAxis = 61;
  }

                                            // Send the values via packets to the serial port
  Serial.write("<");                        // Unique header character                                          
  Serial.write(xAxis/4);                    // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.write(",");
  Serial.write(yAxis/4);
  Serial.write(">");                        // Unique ending character
  delay(100);
                                            // Uncomment to check output of joystick values to Serial Monitor
/*
  Serial.print("X-axis: ");
  Serial.print(xAxis);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(yAxis);
  Serial.print("\n\n");
  delay(500);
*/ 
}
