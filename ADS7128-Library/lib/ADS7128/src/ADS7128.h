#include <Arduino.h>
#include <Wire.h>

#ifndef __ADS7128__
#define __ADS7128__

//Datasheet TI: https://www.ti.com/lit/ds/symlink/ads7128.pdf?ts=1680180539961&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FADS7128%253FkeyMatch%253DADS7128IRTER%2526tisearch%253Dsearch-everything%2526usecase%253DOPN 

class ADS7128
{
private:
#define SYSTEM_STATUS_REGISTER 0x00 //default: 0x81, 

#define CHANNEL_SEL_REGISTER 0x11 // ADC channel select register nr

#define RECENT_CH0_LSB_REGISTER 0xA0 // Lower 8 bits of the last conversion
#define RECENT_CH0_MSB_REGISTER 0xA1 // MSB aligned first 8 bits of the last conversion
#define RECENT_CH1_LSB_REGISTER 0xA2 // Lower 8 bits of the last conversion
#define RECENT_CH1_MSB_REGISTER 0xA3 // MSB aligned first 8 bits of the last conversion
#define RECENT_CH2_LSB_REGISTER 0xA4 // Lower 8 bits of the last conversion
#define RECENT_CH2_MSB_REGISTER 0xA5 // MSB aligned first 8 bits of the last conversion
#define RECENT_CH3_LSB_REGISTER 0xA6 // Lower 8 bits of the last conversion
#define RECENT_CH3_MSB_REGISTER 0xA7 // MSB aligned first 8 bits of the last conversion
#define RECENT_CH4_LSB_REGISTER 0xA8 // Lower 8 bits of the last conversion
#define RECENT_CH4_MSB_REGISTER 0xA9 // MSB aligned first 8 bits of the last conversion
#define RECENT_CH5_LSB_REGISTER 0xAA // Lower 8 bits of the last conversion
#define RECENT_CH5_MSB_REGISTER 0xAB // MSB aligned first 8 bits of the last conversion
#define RECENT_CH6_LSB_REGISTER 0xAC // Lower 8 bits of the last conversion
#define RECENT_CH6_MSB_REGISTER 0xAD // MSB aligned first 8 bits of the last conversion
#define RECENT_CH7_LSB_REGISTER 0xAE // Lower 8 bits of the last conversion
#define RECENT_CH7_MSB_REGISTER 0xAF // MSB aligned first 8 bits of the last conversion

    //TwoWire wireBus; // set the wireBus object
    uint8_t wire;    // Bus nr
    int address;     // 7Bit I2C Slave address
    int adcNr;       // ADC0-7

public:
    ADS7128(int address = 0b0010111);
    ADS7128(int address, uint8_t wire);

    // begin the Wire with default settings: I2C_SCL = GPIO22, I2C_SDA = GPIO21
    void begin();

    //begin the Wire using SDA, SCL and frequency
    void begin(int SDA, int SCL, int frequency);

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
    int16_t readADC();
};

#endif