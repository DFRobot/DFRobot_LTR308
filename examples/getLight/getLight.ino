/**
 * @file getLight.ino
 * @brief Get the light source value and lux value of the LTR308
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [thdyyl](yuanlong.yu@dfrobot.com)
 * @version V1.0.0
 * @date 2024-07-25
 * @url https://github.com/DFRobot/DFRobot_LTR308
 */

#include <DFRobot_LTR308.h>

DFRobot_LTR308 light;
// DFRobot_LTR308 light(&Wire);
void setup(){
  Serial.begin(115200);
  while(!light.begin()){
    Serial.println("Initialization failed!");
    delay(1000);
  }
  Serial.println("Initialization successful!");
  
  /** ---------------------------------------------------------------------------- **
   *    retval  |       enum        |         Description                           *
   * -----------|-------------------|---------------------------------------------- *
   *       0    |     eGain_1X      |   device is set to 1X gain                    *
   *       1    |     eGain_3X      |   device is set to 3X gain (Sensor default)   *
   *       2    |     eGain_6X      |   device is set to 6X gain                    *
   *       3    |     eGain_9X      |   device is set to 9X gain                    *
   *       4    |     eGain_18X     |   device is set to 18X gain                   *
   * ------------------------------------------------------------------------------ */
//   Serial.println("Set Gain...");
//   light.setGain(light.eGain_1X);
//   Serial.print("Set the gain to ");
//   Serial.println(light.getGain());


  /** ---------------------------------------------------------------------------------------------------- **
   *    retval     |            enum            |           Description                                     *
   * ------------------------------------------------------------------------------------------------------ *
   *     resolution                                                                                         *
   * ------------------------------------------------------------------------------------------------------ *
   *      0        |    eConversion_400ms_20b   | 20 Bit result, Conversion time = 400ms.                   *
   *      1        |    eConversion_200ms_19b   | 19 Bit result, Conversion time = 200ms.                   *
   *      2        |    eConversion_100ms_18b   | 18 Bit result, Conversion time = 100ms.(Sensor default)   *
   *      3        |    eConversion_50ms_17b    | 17 Bit result, Conversion time = 50ms.                    *
   *      4        |    eConversion_25ms_16b    | 16 Bit result, Conversion time = 25ms.                    *
   * ------------------------------------------------------------------------------------------------------ *
   *    Measurement Rate                                                                                    *
   * ------------------------------------------------------------------------------------------------------ *
   *      0        |    eRate_25ms              |   Measurement Rate will be 25ms.                          *
   *      1        |    eRate_50ms              |   Measurement Rate will be 50ms.                          *
   *      2        |    eRate_100ms             |   Measurement Rate will be 100ms.(Sensor default)         *
   *      3        |    eRate_500ms             |   Measurement Rate will be 500ms.                         *
   *      5        |    eRate_1000ms            |   Measurement Rate will be 1000ms.                        *
   *      6        |    eRate_2000ms            |   Measurement Rate will be 2000ms.                        *
   *      7        |    eRate_2000ms_2          |   Measurement Rate will be 2000ms.                        *
   * ------------------------------------------------------------------------------------------------------ */
//   Serial.println("Set measurement rate, data bits, and conversion time...");
//   light.setMeasurementRate(light.eConversion_400ms_20b, light.eRate_500ms);
//   DFRobot_LTR308::sMeasRate_t measRate;
//   measRate = light.getMeasurementRate();
//   Serial.print("Set the conversion time to ");
//   Serial.println(measRate.resolution);
//   Serial.print("Set the measurement rate to ");
//   Serial.println(measRate.measurementRate);
}

void loop(){
  uint32_t data = light.getData();
  Serial.println();
  Serial.print("Original Data: ");
  Serial.println(data);
  Serial.print("Lux Data: ");
  Serial.println(light.getLux(data));

  delay(500);
}