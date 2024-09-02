/**
   @file interrupt.ino
   @brief Description When the threshold was exceeded for n consecutive times, the interruption was triggered.
   @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @license The MIT License (MIT)
   @author [thdyyl](yuanlong.yu@dfrobot.com)
   @version V1.0.0
   @date 2024-07-25
   @url https://github.com/DFRobot/DFRobot_LTR308
*/

#include <DFRobot_LTR308.h>

DFRobot_LTR308 light;
// DFRobot_LTR308 light(&Wire);
bool is_stop = false;
void setup()
{
  Serial.begin(115200);
  while (!light.begin())
  {
    Serial.println("Initialization failed!");
    delay(1000);
  }
  Serial.println("Initialization successful!");
  light.setPowerDown();
  Serial.print("PART_ID:0X");
  /** ----------------------------- **
   *  PART_ID     0xB1 (default)     *
   ** ----------------------------- **/
  Serial.println(light.getPartID(), HEX);
  

  /** -----------------------------------**
   * 0x00   |      ALS standby(default)   *
   * 0x02   |      ALS active             *
   * -------------------------------------*/
  Serial.print("control: 0X");
  Serial.println(light.getPower(), HEX);


  /** ---------------------------------------------------------------------------- **
   *    retval  |       enum        |         Description                           *
   * -----------|-------------------|---------------------------------------------- *
   *       0    |     eGain_1X      |   device is set to 1X gain                    *
   *       1    |     eGain_3X      |   device is set to 3X gain (Sensor default)   *
   *       2    |     eGain_6X      |   device is set to 6X gain                    *
   *       3    |     eGain_9X      |   device is set to 9X gain                    *
   *       4    |     eGain_18X     |   device is set to 18X gain                   *
   * ------------------------------------------------------------------------------ */
  Serial.println("Set Gain...");
  light.setGain(light.eGain_1X);
  Serial.print("Set the gain to ");
  Serial.println(light.getGain());

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
  Serial.println("Set measurement rate, data bits, and conversion time...");
  // DFRobot_LTR308::sMeasRate_t measRateData = {light.eConversion_400ms_20b, light.eRate_1000ms};
  // light.setMeasurementRate(measRateData);
  light.setMeasurementRate(light.eConversion_400ms_20b, light.eRate_1000ms);
  DFRobot_LTR308::sMeasRate_t measRate;
  measRate = light.getMeasurementRate();
  Serial.print("Set the conversion time to ");
  Serial.println(measRate.resolution);
  Serial.print("Set the measurement rate to ");
  Serial.println(measRate.measurementRate);

  /**The upper and lower limits are set in the range of 0-0x0FFFFF, 
   * which is determined according to the conversion time and can 
   * also be said to be determined according to the set data bits */
  Serial.println("Set the upper and lower limits of the threshold...");
  // DFRobot_LTR308::sThres_t thresHold = {1000, 50};
  // light.setThreshold(thresHold);
  light.setThreshold(1000, 50);
  DFRobot_LTR308::sThres_t thres = light.getThreshold();
  Serial.print("The upper limit set is ");
  Serial.println(thres.upperLimit);
  Serial.print("The lower limit set is ");
  Serial.println(thres.lowerLimit);

  /** ---------------------------------------------------------------------------------------------------------------------- **
   *    retval      |           enum            |               Description                                                   *
   * ---------------|---------------------------|---------------------------------------------------------------------------- *
   *      0         |    eInterruptTrigger_1    |    Every ALS value out of threshold range asserts an interrupt (default)    *
   *      1         |    eInterruptTrigger_2    |    2 consecutive ALS values out of threshold range assert an interrupt      *
   *      2         |    eInterruptTrigger_3    |    3 consecutive ALS values out of threshold range assert an interrupt      *
   *      3         |    eInterruptTrigger_4    |    4 consecutive ALS values out of threshold range assert an interrupt      *
   *      4         |    eInterruptTrigger_5    |    5 consecutive ALS values out of threshold range assert an interrupt      *
   *      5         |    eInterruptTrigger_6    |    6 consecutive ALS values out of threshold range assert an interrupt      *
   *      6         |    eInterruptTrigger_7    |    7 consecutive ALS values out of threshold range assert an interrupt      *
   *      7         |    eInterruptTrigger_8    |    8 consecutive ALS values out of threshold range assert an interrupt      *
   *      8         |    eInterruptTrigger_9    |    9 consecutive ALS values out of threshold range assert an interrupt      *
   *      9         |    eInterruptTrigger_10   |    10 consecutive ALS values out of threshold range assert an interrupt     *
   *      10        |    eInterruptTrigger_11   |    11 consecutive ALS values out of threshold range assert an interrupt     *
   *      11        |    eInterruptTrigger_12   |    12 consecutive ALS values out of threshold range assert an interrupt     *
   *      12        |    eInterruptTrigger_13   |    13 consecutive ALS values out of threshold range assert an interrupt     *
   *      13        |    eInterruptTrigger_14   |    14 consecutive ALS values out of threshold range assert an interrupt     *
   *      14        |    eInterruptTrigger_15   |    15 consecutive ALS values out of threshold range assert an interrupt     *
   *      15        |    eInterruptTrigger_16   |    16 consecutive ALS values out of threshold range assert an interrupt     *
   * ------------------------------------------------------------------------------------------------------------------------ */
  Serial.println("Set interrupt persistence...");
  light.setIntrPersist(light.eInterruptTrigger_12);
  Serial.print("Interrupt persistence set to ");
  Serial.println(light.getIntrPersist());

  Serial.println("Enable Interrupt...");
  light.setInterruptControl(true);
  Serial.print("Is the interrupt enabled: ");
  Serial.println(light.getInterruptControl());
  light.setPowerUp();
}

void loop()
{
  /*The set waiting time should be consistent with the measurement rate for the best effect.*/
  delay(1000);
  DFRobot_LTR308::sMainStatus_t mainStatus = light.getStatus();

  uint32_t data = light.getData();
  if (mainStatus.dataStatus){
    Serial.print("Original Data: ");
    Serial.println(data);
    Serial.print("Lux Data: ");
    Serial.println(light.getLux(data));
  }
  if (mainStatus.intrStatus){
    Serial.println("Interrupt trigger...");
    light.setPowerDown();
    is_stop = true;
  }
  if(is_stop){
    delay(5000);
    light.setPowerUp();
    Serial.println("............................");
    Serial.println("Re collect...");
    is_stop = false;
  }
}