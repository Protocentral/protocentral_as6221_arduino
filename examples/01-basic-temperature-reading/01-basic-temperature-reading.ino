//////////////////////////////////////////////////////////////////////////////////////////
//
//  ProtoCentral AS6221 Arduino example — basic body temperature reading
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
//
//  Reads the body temperature from the ProtoCentral AS6221 wearable temperature sensor
//  (QWIIC) and prints it in Celsius and Fahrenheit to the Serial Monitor once per second.
//
//  Hardware:
//      Plug the AS6221 wearable sensor into a QWIIC / STEMMA QT port, or wire
//      SDA/SCL/3V3/GND directly to the Arduino.
//
//////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "protocentral_as6221.h"

ProtocentralAS6221 tempSensor(AS6221_DEFAULT_ADDRESS);  // 0x48

void setup()
{
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Serial.println("ProtoCentral AS6221 - Basic Reading");

  if (!tempSensor.begin())
  {
    Serial.println("AS6221 not found on the I2C bus. Check wiring/address.");
    while (1) { delay(1000); }
  }
  Serial.println("AS6221 detected.");
}

void loop()
{
  float tempC = tempSensor.readTemperatureC();    // Degrees Celsius
  float tempF = tempSensor.readTemperatureF();    // Degrees Fahrenheit

  Serial.print("Temperature: ");
  Serial.print(tempC, 4);
  Serial.print(" C  /  ");
  Serial.print(tempF, 4);
  Serial.println(" F");

  delay(1000);
}
