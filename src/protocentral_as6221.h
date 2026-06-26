//////////////////////////////////////////////////////////////////////////////////////////
//
//  ProtoCentral AS6221 Arduino Library
//
//  Arduino library for the ProtoCentral AS6221 wearable body temperature sensor (QWIIC),
//  based on the ams OSRAM AS6221 factory-calibrated digital temperature sensor.
//
//      Accuracy   : +/-0.09 C (20 C - 42 C)
//      Resolution : 16-bit, 0.0078125 C / LSB
//      Interface  : I2C, 8 selectable addresses (0x48 - 0x4F)
//
//  Author: Ashwin Whitchurch
//  Copyright (c) 2026 Protocentral Electronics
//
//  SPDX-License-Identifier: MIT
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//  For more information, visit https://github.com/Protocentral/protocentral_as6221_arduino
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROTOCENTRAL_AS6221_H
#define PROTOCENTRAL_AS6221_H

#include <Arduino.h>
#include <Wire.h>

// Default I2C address (ADD0/ADD1 tied to GND). Range 0x48 – 0x4F.
#define AS6221_DEFAULT_ADDRESS 0x48

// Register map (AS621x family)
#define AS6221_REG_TVAL   0x00  // Temperature value (read-only, 16-bit)
#define AS6221_REG_CONFIG 0x01  // Configuration register
#define AS6221_REG_TLOW   0x02  // Low-temperature threshold
#define AS6221_REG_THIGH  0x03  // High-temperature threshold

// 1 LSB of the temperature register, in degrees Celsius
#define AS6221_LSB_C 0.0078125f

class ProtocentralAS6221 {
  public:
    explicit ProtocentralAS6221(uint8_t address = AS6221_DEFAULT_ADDRESS);

    // Start I2C and confirm the sensor responds. Returns true on success.
    bool begin(TwoWire &wirePort = Wire);

    // Read temperature in degrees Celsius.
    float readTemperatureC();

    // Read temperature in degrees Fahrenheit.
    float readTemperatureF();

    // Read/write the 16-bit configuration register.
    uint16_t readConfig();
    void     writeConfig(uint16_t value);

  private:
    uint8_t   _address;
    TwoWire  *_i2cPort;

    uint16_t readRegister16(uint8_t reg);
    void     writeRegister16(uint8_t reg, uint16_t value);
};

#endif // PROTOCENTRAL_AS6221_H
