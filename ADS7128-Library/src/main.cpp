#include <Arduino.h>
#include <Wire.h>

//----------------------------------------------------------------Declarations----------------------------------------------------------------------------
void scanningI2C();
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200); // start the serial monitor with a baudrate of 115200 Bit/s

  Serial.println("start setup");

  // scanningI2C();
  Wire.begin();

  Wire.beginTransmission(0x17);
  Wire.write(0b00010000); // Send the register address to read from
  Wire.write(0x00);
  Serial.println(Wire.endTransmission(false));
  /*
  0: success.
  1: data too long to fit in transmit buffer.
  2: received NACK on transmit of address.
  3: received NACK on transmit of data.
  4: other error.
  5: timeout
  */

  Wire.requestFrom(0x17, 1);
  if (Wire.available() >= 1)
  {
    Serial.println("Wire is available");
    byte data = Wire.read();   // Read the received data
    Serial.print("0x");
    Serial.println(data, HEX); // Display the data
  }
  Serial.println(Wire.endTransmission()); // End the communication with the device

  Serial.println("done setup");
}

void loop()
{
}

//----------------------------------------------------------------Functions------------------------------------------------------------------------------
void scanningI2C()
{
  byte error, address;

  Serial.println("Scanning...");
  Wire.begin();

  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Device found at address 0x"); // 0x17 = 23 = 0b0010111
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    } /*else{
       Serial.print("Error at address 0x");
       if (address < 16)
         Serial.print("0");
       Serial.println(address, HEX);
     }*/
  }

  Serial.println("Scanning complete");
}