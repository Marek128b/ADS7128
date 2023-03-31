#include <Arduino.h>
#include <Wire.h>
#include "ADS7128.h"

ADS7128::ADS7128(int address)
{
    this->address = address;
    // this->wireBus = 0;
}

ADS7128::ADS7128(int address, uint8_t bus)
{
    this->address = address;
    // this->wireBus = bus;
}

void ADS7128::begin()
{
    Wire.begin(address);
}

void ADS7128::begin(int SDA, int SCL, int frequency)
{
    Wire.begin(SDA, SCL, frequency);
}

void ADS7128::setAdcNr(byte nr)
{
    this->adcNr = nr;
    Wire.write((address << 1) + 0);   // write to Address
    Wire.write(0b00001000);           // writing data to I2C device address
    Wire.write(CHANNEL_SEL_REGISTER); // register address
    Wire.write(0b0000 + nr);          // register data
    Wire.endTransmission();
}

int16_t ADS7128::readADC()
{
    int16_t output;

    // Wire.write((address << 1) + 1); // read from Address
    Wire.requestFrom(address, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = Wire.read() << 8 | Wire.read();
        Serial.print("Register value: ");
        Serial.println(output);
    }

    return output;
}