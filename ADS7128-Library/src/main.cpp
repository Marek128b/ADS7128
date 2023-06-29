#include <Arduino.h>
#include <Wire.h>

#include <ADS7128.h>

ADS7128 ADC; // ADS7128 Object

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

  for (byte i = 0; i < 8; i++) //loop through all ADCs
  {
    ADC.setAdcNr(i); //set the ADC number to read from 
    uint16_t in;
    Serial.printf("ADC%d: ", i);
    Serial.print(in = ADC.readADC()); //read the ADC value and store it in a uint16_t variable 
    Serial.print(" -> Voltage: ");
    Serial.println(ADC.getVoltage(in)); //convert the ADC value to a voltage if the Maximum Input Voltage is 3V3
  }

  delay(2000);
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
    }
  }
  Serial.println("Scanning complete");
}
