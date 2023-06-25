#include <Arduino.h>
#include <Wire.h>

#define SYSTEM_STATUS_REGISTER 0x00 // default: 0x81

#define CHANNEL_SEL_REGISTER 0x11 // ADC channel select register nr
#define RECENT_CH2_LSB 0xA4

//----------------------------------------------------------------Declarations----------------------------------------------------------------------------
void scanningI2C();
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200); // start the serial monitor with a baudrate of 115200 Bit/s

  Serial.println("start setup");

  // scanningI2C();
  Wire.begin();

  // reading a Register
  Wire.beginTransmission(0x17);
  Wire.write(0b00010000);             // read Register
  Wire.write(SYSTEM_STATUS_REGISTER); // Send the register address to read from
  Wire.endTransmission(false);
  Wire.requestFrom(0x17, 1);
  if (Wire.available() >= 1)
  {
    byte data = Wire.read(); // Read the received data
    Serial.print("0x");
    Serial.println(data, HEX); // Display the data
  }
  Wire.endTransmission(); // End the communication with the device
  Serial.println("done read SYSTEM_STATUS");
  Serial.println("----------------------------------------------------------------------------------------");

  // Writing to a Register
  Wire.beginTransmission(0x17);
  Wire.write(0b00001000);           // write Register
  Wire.write(CHANNEL_SEL_REGISTER); // Send the register address to write to
  Wire.write(0b10);                 // AIN2
  Wire.endTransmission();

  // Reading from ADC
  Wire.beginTransmission(0x17);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.requestFrom(0x17, 2);
  if (Wire.available() == 2)
  {
    int data = Wire.read(); // Read the received data
    data = ((data << 8) + Wire.read()) >> 4;
    Serial.println(data); // Display the data
  }
  Wire.endTransmission(); // End the communication with the device
  Serial.println("done read ADC");
  Serial.println("----------------------------------------------------------------------------------------");

  Serial.println("done setup");
}

void loop()
{
  // Reading from ADC
  Wire.beginTransmission(0x17);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.requestFrom(0x17, 2);
  if (Wire.available() == 2)
  {
    int data = Wire.read(); // Read the received data
    data = ((data << 8) + Wire.read()) >> 4;
    Serial.println(data); // Display the data
  }
  Wire.endTransmission(); // End the communication with the device
  delay(100);
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
