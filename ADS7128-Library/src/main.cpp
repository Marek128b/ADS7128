#include <Arduino.h>
#include <Wire.h>

#include <ADS7128.h>

#define SYSTEM_STATUS_REGISTER 0x00 // default: 0x81

#define CHANNEL_SEL_REGISTER 0x11 // ADC channel select register nr
#define RECENT_CH2_LSB 0xA4

ADS7128 ADC;

//----------------------------------------------------------------Declarations----------------------------------------------------------------------------
void scanningI2C();
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200); // start the serial monitor with a baudrate of 115200 Bit/s

  Serial.println("start setup");

  ADC.begin();

  Serial.print("SYSTEM_STATUS: 0b");
  Serial.println(ADC.readSYSTEM_STATUS_REGISTER(), BIN);
  Serial.print("SYSTEM_STATUS: 0x");
  Serial.println(ADC.readSYSTEM_STATUS_REGISTER(), HEX);

  ADC.setAdcNr(0b10);

  ADC.setOversamplingRatio(0b111);
  Serial.print("Oversampling Ratio: 0b");
  Serial.println(ADC.getOversamplingRatio(), BIN);
  /*
  ADC.setAppendID(0b1);
  int id;
  Serial.print("ADC data: 0x");
  Serial.println(ADC.readADCandID(&id), HEX); //not working !!!!
  Serial.print("ID: ");
  Serial.printf("%d\r\n", id);

  Serial.println("done setup");
  ADC.setAppendID(0b0);*/
}

void loop()
{
  Serial.println(ADC.readADC());
  delay(200);
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
