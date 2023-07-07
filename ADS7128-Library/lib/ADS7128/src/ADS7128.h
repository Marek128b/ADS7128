#include <Arduino.h>
#include <Wire.h>

#ifndef __ADS7128__
#define __ADS7128__

// Datasheet TI: https://www.ti.com/lit/ds/symlink/ads7128.pdf?ts=1680180539961&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FADS7128%253FkeyMatch%253DADS7128IRTER%2526tisearch%253Dsearch-everything%2526usecase%253DOPN

class ADS7128
{
private:
  float MAX_INPUT_VOLTAGE = 3.3;

  int address; // 7Bit I2C Slave address
  int adcNr;   // ADC0-7

  void startReadRegister(uint16_t registerAddress);
  void startWriteRegister(uint16_t registerAddress);

public:
#define SYSTEM_STATUS_REGISTER 0x00 // default: 0x81

#define CHANNEL_SEL_REGISTER 0x11 // ADC channel select register nr

#define DATA_CFG_REGISTER 0x02
#define OSR_CFG_REGISTER 0x03

#define PIN_CFG_REGISTER 0x05       // AIN/GPIO[7:0]  0b = Channel is configured as analog input. 1b = Channel is configured as GPIO. Default: 0x00
#define GPIO_CFG_REGISTER 0x07      // Configure GPIO[7:0]  0b = GPIO is configured as digital input. 1b = GPIO is configured as digital output. Default: 0x00
#define GPO_DRIVE_CFG_REGISTER 0x09 // Configure GPO[7:0] as open-drain or push-pull. 0b = output is open-drain. 1b = Pushpull driver is used for digital output. Default: 0x00

  /*
  DECAP
    |
   R1
    |--ADDR
   R2
    |
  GND

  |R1(1)   |R2(1)       |Address
  |--------|------------|-------------------------|
  |0 Ω     |DNP(2)      |0010111b (17h) //Default |
  |11 kΩ   |DNP(2)      |0010110b (16h)           |
  |33 kΩ   |DNP(2)      |0010101b (15h)           |
  |100 kΩ  |DNP(2)      |0010100b (14h)           |
  |DNP(2)  |DNP(2)      |0010000b (10h)           |
  |DNP(2)  |11 kΩ       |0010001b (11h)           |
  |DNP(2)  |33 kΩ       |0010010b (12h)           |
  |DNP(2)  |100 kΩ      |0010011b (13h)           |
  */
  ADS7128(int address = 0b0010111);
  ADS7128(int address, uint8_t wire);

  // begin the Wire with default settings: I2C_SCL = GPIO22, I2C_SDA = GPIO21
  void begin();
  // begin the Wire using SDA, SCL and frequency
  void begin(int SDA, int SCL, int frequency);

  // AIN/GPIO[7:0]  0b = analog input. 1b = GPIO. Default: 0x00
  void configurePins(byte analogGPIO);
  // reads Pin Config. AIN/GPIO[7:0]  0b = analog input. 1b = GPIO. Default: 0x00
  byte readPinConfig();

  // GPIO[7:0]  0b = digital input. 1b = digital output. Default: 0x00
  void configureGPIO(byte GPIO);
  // reads GPIO config. GPIO[7:0]  0b = digital input. 1b = digital output. Default: 0x00
  byte readGPIOConfig();

  // GPO[7:0] as open-drain or push-pull. 0b = open-drain. 1b = Pushpull driver is used. Default: 0x00
  void configureGPODrive(byte GPO_Drive);
  // reads GPO Drive register
  byte readGPODriveConfig();

  /*sets the ADC Number to read from
  0b = AIN0
  1b = AIN1
  10b = AIN2
  11b = AIN3
  100b = AIN4
  101b = AIN5
  110b = AIN6
  111b = AIN7
  1000b = Reserved.
  */
  void setAdcNr(byte nr);

  /*read the data from the before selected Analog Input default AIN0
   */
  uint16_t readADC();

  /*
  returns ADC data and the channel ID when activated
  */
  uint16_t readADCandID(int *ID);

  /*
  Append 4-bit channel ID or status flags to output data.
  0b = Channel ID and status flags are not appended to ADC data.
  1b = 4-bit channel ID is appended to ADC data.
  10b = 4-bit status flags are appended to ADC data.
  11b = Reserved.
  */
  void setAppendID(byte type); // NOT WORKING

  /*
  returns the SYSTEM STATUS REGISTER
  */
  uint8_t readSYSTEM_STATUS_REGISTER();

  /*
  Selects the oversampling ratio for ADC conversion result.
  0b = No averaging
  1b = 2 samples
  10b = 4 samples
  11b = 8 samples
  100b = 16 samples
  101b = 32 samples
  110b = 64 samples
  111b = 128 samples
  */
  void setOversamplingRatio(byte ratio);
  /*
   Selects the oversampling ratio for ADC conversion result.
   0b = No averaging
   1b = 2 samples
   10b = 4 samples
   11b = 8 samples
   100b = 16 samples
   101b = 32 samples
   110b = 64 samples
   111b = 128 samples
   */
  byte getOversamplingRatio();

  // reads one byte of a requested register
  byte getRegisterData(byte id);
  // writes one byte to the selected register
  void setRegisterData(byte id, byte data);

  // returns the Voltage that is set on a Analog Input
  float getVoltage();
  // returns the Voltage that  set on a Analog Input
  float getVoltage(uint16_t in);

  // set and read the MAX_INPUT_VOLTAGE
  void setMAX_INPUT_VOLTAGE(float in);
  float getMAX_INPUT_VOLTAGE();
};

#endif