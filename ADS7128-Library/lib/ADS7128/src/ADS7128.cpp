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

//------------------------------------------------------------------------------Basic Function to Read and Wright  a Register--------------------------------------------------------------------
void startReadRegister(uint16_t registerAddress)
{
    Wire.beginTransmission(registerAddress); // write to Address
    Wire.write(0b000010000);                 // reading data to I2C device address
    Wire.write(PIN_CFG_REGISTER);            // register address
    Wire.endTransmission();                  // end Transmission I2C
}

//------------------------------------------------------------------------------Begin------------------------------------------------------------------------------------------------------------
void ADS7128::begin()
{
    Wire.begin();
}

void ADS7128::begin(int SDA, int SCL, int frequency)
{
    Wire.begin(SDA, SCL, frequency);
}
//-------------------------------------------------------------------------------Pins Config as Analog or Digital--------------------------------------------------------------------------------
void ADS7128::configurePins(byte analogGPIO)
{
    Wire.beginTransmission(address); // write to Address
    Wire.write(0b00001000);          // writing data to I2C device address
    Wire.write(PIN_CFG_REGISTER);    // register address
    Wire.write(analogGPIO);          // register data
    Wire.endTransmission();
}

byte ADS7128::readPinConfig()
{
    byte output;
    startReadRegister(PIN_CFG_REGISTER);

    Wire.requestFrom(address, 1); // requesting two bytes from the I2C address
    if (Wire.available())
    {
        output = Wire.read();
        Serial.print("Register value: ");
        Serial.println(output);
    }
    return output;
}
//-------------------------------------------------------------------------------GPIO as Input or Output----------------------------------------------------------------------------------------
void ADS7128::configureGPIO(byte GPIO)
{
    Wire.beginTransmission(address); // write to Address
    Wire.write(0b00001000);          // writing data to I2C device address
    Wire.write(GPIO_CFG_REGISTER);   // register address
    Wire.write(GPIO);                // register data
    Wire.endTransmission();
}

byte ADS7128::readGPIOConfig()
{
    byte output;
    startReadRegister(GPIO_CFG_REGISTER);

    Wire.requestFrom(address, 1); // requesting two bytes from the I2C address
    if (Wire.available())
    {
        output = Wire.read();
        Serial.print("Register value: ");
        Serial.println(output);
    }
    return output;
}
//--------------------------------------------------------------------------------GPO Drive pull-up or external--------------------------------------------------------------------------------
void ADS7128::configureGPODrive(byte GPO_Drive)
{
    Wire.beginTransmission(address);    // write to Address
    Wire.write(0b00001000);             // writing data to I2C device address
    Wire.write(GPO_DRIVE_CFG_REGISTER); // register address
    Wire.write(GPO_Drive);              // register data
    Wire.endTransmission();
}

byte ADS7128::readGPODriveConfig()
{
    byte output;
    startReadRegister(GPO_DRIVE_CFG_REGISTER);

    Wire.requestFrom(address, 1); // requesting two bytes from the I2C address
    if (Wire.available())
    {
        output = Wire.read();
        Serial.print("Register value: ");
        Serial.println(output);
    }
    return output;
}
//--------------------------------------------------------------------------------ADC read and config------------------------------------------------------------------------------------------
void ADS7128::setAdcNr(byte nr)
{
    this->adcNr = nr;
    // Wire.write((address << 1) + 0);   // write to Address
    Wire.beginTransmission(address);  // write to Address
    Wire.write(0b00001000);           // writing data to I2C device address
    Wire.write(CHANNEL_SEL_REGISTER); // register address
    Wire.write(0b0000 + nr);          // register data
    Wire.endTransmission();
}

uint16_t ADS7128::readADC()
{
    uint16_t output;

    // Wire.write((address << 1) + 1); // read from Address
    Wire.requestFrom(address, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = Wire.read() << 8 | Wire.read();
        Serial.print("Register value: ");
        Serial.println(output >> 4);
    }

    return (output >> 4);
}