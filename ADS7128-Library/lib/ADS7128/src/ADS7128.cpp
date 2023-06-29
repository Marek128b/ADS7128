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
    Wire.beginTransmission(address);  // write to Address
    Wire.write(0b00001000);           // writing data to I2C device address
    Wire.write(CHANNEL_SEL_REGISTER); // register address
    Wire.write(0b0000 + nr);          // register data
    Wire.endTransmission();
}

uint16_t ADS7128::readADC()
{
    uint16_t output;

    Wire.requestFrom(address, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = (Wire.read() << 8 | Wire.read()) >> 4;
    }

    return output;
}

/*
NOTE!! you need to activate the added ID with
*/
uint16_t ADS7128::readADCandID(int *ID)
{
    uint16_t output;

    Wire.requestFrom(address, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = Wire.read() << 8 | Wire.read();
    }

    ID = (int *)((output << 12) >> 12);

    return output >> 4;
}

void ADS7128::setAppendID(byte type) // NOT WORKING!!!
{
    Wire.beginTransmission(address);  // write to Address
    Wire.write(0b00001000);           // writing data to I2C device address
    Wire.write(DATA_CFG_REGISTER);    // register address
    Wire.write(0b00 + type + 0b0000); // register data
    Wire.endTransmission();
}

uint8_t ADS7128::readSYSTEM_STATUS_REGISTER()
{
    byte data;
    Wire.beginTransmission(0x17);
    Wire.write(0b00010000);             // read Register
    Wire.write(SYSTEM_STATUS_REGISTER); // Send the register address to read from
    Wire.endTransmission(false);
    Wire.requestFrom(0x17, 1);
    if (Wire.available() >= 1)
    {
        data = Wire.read(); // Read the received data
    }
    Wire.endTransmission(); // End the communication with the device
    return data;
}

void ADS7128::setOversamplingRatio(byte ratio)
{
    Wire.beginTransmission(address); // write to Address
    Wire.write(0b00001000);          // writing data to I2C device address
    Wire.write(OSR_CFG_REGISTER);    // register address
    Wire.write(0b00000 + ratio);     // register data
    Wire.endTransmission();
}

byte ADS7128::getOversamplingRatio()
{
    byte data;
    Wire.beginTransmission(0x17);
    Wire.write(0b00010000);       // read Register
    Wire.write(OSR_CFG_REGISTER); // Send the register address to read from
    Wire.endTransmission(false);
    Wire.requestFrom(0x17, 1);
    if (Wire.available() >= 1)
    {
        data = Wire.read(); // Read the received data
    }
    Wire.endTransmission(); // End the communication with the device
    return data;
}

byte ADS7128::getRegisterData(uint8_t id)
{
    byte data;
    Wire.beginTransmission(0x17);
    Wire.write(0b00010000); // read Register
    Wire.write(id);         // Send the register address to read from
    Wire.endTransmission(false);
    Wire.requestFrom(0x17, 1);
    if (Wire.available() >= 1)
    {
        data = Wire.read(); // Read the received data
    }
    Wire.endTransmission(); // End the communication with the device
    return data;
}

float ADS7128::getVoltage()
{
    return MAX_INPUT_VOLTAGE / (pow(2, 12) - 1) * readADC(); // returns a float that represents a input voltage to the set ADC Input
}

float ADS7128::getVoltage(uint16_t in)
{
    return MAX_INPUT_VOLTAGE / (pow(2, 12) - 1) * in;
}

void ADS7128::setMAX_INPUT_VOLTAGE(float in)
{
    this->MAX_INPUT_VOLTAGE = in;
}

float ADS7128::getMAX_INPUT_VOLTAGE()
{
    return MAX_INPUT_VOLTAGE;
}
