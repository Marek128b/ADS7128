#include <Arduino.h>

#include <ADS7128.h> //inclunding ADS7128 Library

ADS7128 ADC = ADS7128(0b0010111); // create a ADS7128 object and give it a I2C address default: 0b0010111

void setup()
{
  Serial.begin(115200); // start the serial monitor with a baudrate of 115200 Bit/s
  ADC.begin();          // begin the ADS7128 object
}

void loop()
{
  ADC.setAdcNr(0b10);                         // select the ADC2 of the ADS7128
  int16_t outputADC = ADC.readADC();          // read the data from the before selected ADC
  Serial.printf("ADC output: %d", outputADC); // output the data to the Serial Monitor
}