//////////////////////////////////////////////////////////////////////////////////////////
//
//  ProtoCentral AS6221 Arduino Library
//
//  Arduino library for the ProtoCentral AS6221 wearable body temperature sensor (QWIIC).
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
//////////////////////////////////////////////////////////////////////////////////////////

#include "protocentral_as6221.h"

ProtocentralAS6221::ProtocentralAS6221(uint8_t address)
  : _address(address), _i2cPort(&Wire) {}

bool ProtocentralAS6221::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;
  _i2cPort->begin();

  // Probe the sensor on the bus.
  _i2cPort->beginTransmission(_address);
  return (_i2cPort->endTransmission() == 0);
}

float ProtocentralAS6221::readTemperatureC() {
  // Temperature register is 16-bit two's complement, LSB = 0.0078125 °C.
  int16_t raw = (int16_t)readRegister16(AS6221_REG_TVAL);
  return raw * AS6221_LSB_C;
}

float ProtocentralAS6221::readTemperatureF() {
  return readTemperatureC() * 1.8f + 32.0f;
}

uint16_t ProtocentralAS6221::readConfig() {
  return readRegister16(AS6221_REG_CONFIG);
}

void ProtocentralAS6221::writeConfig(uint16_t value) {
  writeRegister16(AS6221_REG_CONFIG, value);
}

uint16_t ProtocentralAS6221::readRegister16(uint8_t reg) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  if (_i2cPort->endTransmission(false) != 0) {
    return 0;
  }

  _i2cPort->requestFrom(_address, (uint8_t)2);
  if (_i2cPort->available() < 2) {
    return 0;
  }

  uint8_t msb = _i2cPort->read();  // MSB first
  uint8_t lsb = _i2cPort->read();
  return ((uint16_t)msb << 8) | lsb;
}

void ProtocentralAS6221::writeRegister16(uint8_t reg, uint16_t value) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(reg);
  _i2cPort->write((uint8_t)(value >> 8));    // MSB first
  _i2cPort->write((uint8_t)(value & 0xFF));
  _i2cPort->endTransmission();
}
