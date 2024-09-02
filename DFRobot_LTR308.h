/**
 * @file DFRobot_LTR308.h
 * @brief Define the basic structure of class DFRobot_LTR308
 * @details Define the LTR308 functions
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [thdyyl](yuanlong.yu@dfrobot.com)
 * @version V1.0.0
 * @date 2024-07-25
 * @url https://github.com/DFRobot/DFRobot_LTR308
 */
#ifndef __DFROBOT_LTR308_H
#define __DFROBOT_LTR308_H

#include "Arduino.h"
#include "Wire.h"


// #define ENABLE_DBG      ///< Enable this macro to see the detailed running process of the program

#ifdef ENABLE_DBG
#define DBG(...){Serial.print("[");Serial.print(__FUNCTION__);Serial.print("(): ");Serial.print(__LINE__);Serial.print(" ] ");Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif


#define LTR308_ADDR   0x53 ///< Default address of the LTR308 sensor
#define LTR308_PART_V_ID  0xB1  ///< The part number and revision identification of the sensor.

// LTR308 register addresses
#define LTR308_REG_CONTR         0x00
#define LTR308_REG_MEAS_RATE     0x04
#define LTR308_REG_ALS_GAIN      0x05
#define LTR308_REG_PART_ID       0x06
#define LTR308_REG_STATUS        0x07
#define LTR308_REG_DATA_0        0x0D
#define LTR308_REG_DATA_1        0x0E
#define LTR308_REG_DATA_2        0x0F
#define LTR308_REG_INTERRUPT     0x19
#define LTR308_REG_INTR_PERS     0x1A
#define LTR308_REG_THRES_UP_0    0x21
#define LTR308_REG_THRES_UP_1	 0x22
#define LTR308_REG_THRES_UP_2	 0x23
#define LTR308_REG_THRES_LOW_0   0x24
#define LTR308_REG_THRES_LOW_1   0x25
#define LTR308_REG_THRES_LOW_2   0x26

class DFRobot_LTR308
{
public:
  /**
   * @enum eGain_t
   * @brief Enumerated gain
   */
  typedef enum {
    eGain_1X=0x00,
    eGain_3X,
    eGain_6X,
    eGain_9X,
    eGain_18X
  }eGain_t;

  /**
   * @enum eIntrPersist_t
   * @brief Enumeration interrupts persistence
   */
  typedef enum {
    eInterruptTrigger_1=0x00,
    eInterruptTrigger_2,
    eInterruptTrigger_3,
    eInterruptTrigger_4,
    eInterruptTrigger_5,
    eInterruptTrigger_6,
    eInterruptTrigger_7,
    eInterruptTrigger_8,
    eInterruptTrigger_9,
    eInterruptTrigger_10,
    eInterruptTrigger_11,
    eInterruptTrigger_12,
    eInterruptTrigger_13,
    eInterruptTrigger_14,
    eInterruptTrigger_15,
    eInterruptTrigger_16
  }eIntrPersist_t;


  /**
   * @enum eResolution_t
   * @brief Enumeration conversion time
   */
  typedef enum {
    eConversion_400ms_20b=0x00,
    eConversion_200ms_19b,
    eConversion_100ms_18b,
    eConversion_50ms_17b,
    eConversion_25ms_16b
  }eResolution_t;
  
  /**
   * @enum eMeasurementRate_t
   * @brief Enumeration measurement rate
   */
  typedef enum {
    eRate_25ms=0x00,
    eRate_50ms,
    eRate_100ms,
    eRate_500ms,
    eRate_1000ms=5,
    eRate_2000ms,
    eRate_2000ms_2
  }eMeasurementRate_t;
  
  /**
   * @struct sMeasRate_t
   * @brief ALS measurement rate and resolution in Active Mode
   */
  typedef struct{
    eResolution_t resolution;
    eMeasurementRate_t measurementRate;
  }sMeasRate_t;


  /**
   * @struct sMainStatus_t
   * @brief  The sensor status: Power-On status, Interrupt status, Data status
   */
  typedef struct{
    bool ponStatus;
    bool intrStatus;
    bool dataStatus;
  }sMainStatus_t;


  /**
   * @struct sThres_t
   * @brief  ALS interrupt threshold
   */
  typedef struct{
    uint32_t upperLimit;
    uint32_t lowerLimit;
  }sThres_t;

private:
  uint8_t _deviceAddr;
  TwoWire* _pWire;
  eGain_t _gain;
  eResolution_t _resolution;
  eMeasurementRate_t _measurementRate;

public:
  DFRobot_LTR308(TwoWire* pWire = &Wire);

  /**
   * @fn begin
   * @brief Initialize the function.
   * @return bool ,Indicates the initialization state.
   */
  bool begin(void);

  /**
   * @fn setPowerUp
   * @brief Set the Power Up LTR308.
   */
  void setPowerUp(void);

  /**
   * @fn setPowerDown
   * @brief Set the Power Down LTR308
   */
  void setPowerDown(void);

  /**
   * @fn getPower
   * @brief Get the Power value
   * @return uint8_t: content of LTR308_CONTR control register
   */
  uint8_t getPower(void);

  /**
   * @fn setGain
   * @brief Set the Gain of LTR308
   * @param gain eGain_t
   * @n eGain_1X        device is set to 1X gain
   * @n eGain_3X        device is set to 3X gain (Sensor default)
   * @n eGain_6X        device is set to 6X gain
   * @n eGain_9X        device is set to 9X gain
   * @n eGain_18X       device is set to 18X gain
   */
  void setGain(eGain_t gain);

  /**
   * @fn getGain
   * @brief Get the Gain of LTR308
   * @return uint8_t: the control register values
   * @retval 0      device is set to 1X gain
   * @retval 1      device is set to 3X gain (Sensor default)
   * @retval 2      device is set to 6X gain
   * @retval 3      device is set to 9X gain
   * @retval 4      device is set to 18X gain
   */
  uint8_t getGain(void);

  /**
   * @fn setMeasurementRate
   * @brief Set the Measurement Rate and resolution
   * @param measRate: (sMeasRate_t)  Measurement Rate and resolution
   * @n measRate.resolution (eResolution_t)
   * @n eConversion_400ms_20b     20 Bit result, Conversion time = 400ms.
   * @n eConversion_200ms_19b     19 Bit result, Conversion time = 200ms.
   * @n eConversion_100ms_18b     18 Bit result, Conversion time = 100ms.(Sensor default)
   * @n eConversion_50ms_17b      17 Bit result, Conversion time = 50ms.
   * @n eConversion_25ms_16b      16 Bit result, Conversion time = 25ms.
   * @n -------------------------------------------------------------------------------------------
   * @n measRate.measurementRate (eMeasurementRate_t)
   * @n eRate_25ms       Measurement Rate will be 25ms.
   * @n eRate_50ms       Measurement Rate will be 50ms.
   * @n eRate_100ms      Measurement Rate will be 100ms.(Sensor default)
   * @n eRate_500ms      Measurement Rate will be 500ms.
   * @n eRate_1000ms     Measurement Rate will be 1000ms.
   * @n eRate_2000ms     Measurement Rate will be 2000ms.
   * @n eRate_2000ms_2   Measurement Rate will be 2000ms.
   */
  void setMeasurementRate(sMeasRate_t measRate);

  /**
   * @fn setMeasurementRate
   * @brief Set the Measurement Rate and resolution
   * @param resolution: (eResolution_t)  The measurement time for each ALs cycle
   * @n eConversion_400ms_20b     20 Bit result, Conversion time = 400ms.
   * @n eConversion_200ms_19b     19 Bit result, Conversion time = 200ms.
   * @n eConversion_100ms_18b     18 Bit result, Conversion time = 100ms.(Sensor default)
   * @n eConversion_50ms_17b      17 Bit result, Conversion time = 50ms.
   * @n eConversion_25ms_16b      16 Bit result, Conversion time = 25ms.
   * @param measurementRate: (eMeasurementRate_t)  The interval between DATA_REGISTERS update
   * @n eRate_25ms       Measurement Rate will be 25ms.
   * @n eRate_50ms       Measurement Rate will be 50ms.
   * @n eRate_100ms      Measurement Rate will be 100ms.(Sensor default)
   * @n eRate_500ms      Measurement Rate will be 500ms.
   * @n eRate_1000ms     Measurement Rate will be 1000ms.
   * @n eRate_2000ms     Measurement Rate will be 2000ms.
   * @n eRate_2000ms_2   Measurement Rate will be 2000ms.
   */
  void setMeasurementRate(eResolution_t resolution, eMeasurementRate_t measurementRate);

  /**
   * @fn getMeasurementRate
   * @brief Get the Measurement Rate and resolution
   * @return sMeasRate_t: Measurement Rate and resolution
   * @retval sMeasRate_t.resolution (eResolution_t)
   * @retval 0      20 Bit result, Conversion time = 400ms.
   * @retval 1      19 Bit result, Conversion time = 200ms.
   * @retval 2      18 Bit result, Conversion time = 100ms.(Sensor default)
   * @retval 3      17 Bit result, Conversion time = 50ms.
   * @retval 4      16 Bit result, Conversion time = 25ms.
   * @retval -------------------------------------------------------------------------------------------
   * @retval sMeasRate_t.measurementRate (eMeasurementRate_t)
   * @retval 0      Measurement Rate will be 25ms.
   * @retval 1      Measurement Rate will be 50ms.
   * @retval 2      Measurement Rate will be 100ms.(Sensor default)
   * @retval 3      Measurement Rate will be 500ms.
   * @retval 5      Measurement Rate will be 1000ms.
   * @retval 6      Measurement Rate will be 2000ms.
   * @retval 7      Measurement Rate will be 2000ms.
   */
  sMeasRate_t getMeasurementRate(void);

  /**
   * @fn getPartID
   * @brief Gets the part number ID and revision ID of the chip
   * @return uint8_t: Default value is 0xB1, part number ID = 0xB, revision ID = 0x1.
   */
  uint8_t getPartID(void);

  /**
   * @fn getStatus
   * @brief Get the Status of LTR308
   * @return sMainStatus_t: The status information of LTR308.
   * @retval If sMainStatus_t.ponStatus = false(0), power on event (default)
   * @retval If sMainStatus_t.ponStatus = true(1), not specified in datasheet
   * @retval -------------------------------------------------------------------------------------------
   * @retval If sMainStatus_t.intrStatus = false(0), Interrupt is NOT triggered (default)
   * @retval If sMainStatus_t.intrStatus = true(1), Interrupt is triggered and will be cleared after read
   * @retval -------------------------------------------------------------------------------------------
   * @retval If sMainStatus_t.dataStatus = false(0), ALS data is old (Data has been read)
   * @retval If sMainStatus_t.dataStatus = true(1), ALS data is new data (Data has not been read and will be cleared after read)
   */
  sMainStatus_t getStatus(void);

  /**
   * @fn getData
   * @brief Get the ALS channel data
   * @return uint32_t: ALS data, Default value is 0
   */
  uint32_t getData(void);

  /**
   * @fn setInterruptControl
   * @brief Set the Interrupt Control of LTR308
   * @param mode: interrupt mode
   * @n If mode = false(0), ALS interrupt disabled (default)
   * @n If mdoe = true(1), ALS interrupt enabled
   */
  void setInterruptControl(bool mode);

  /**
   * @fn getInterruptControl
   * @brief Get the Interrupt Control of LTR308
   * @return bool: interrupt mode
   * @retval true: ALS interrupt enabled
   * @retval false: ALS interrupt disabled
   */
  bool getInterruptControl(void);

  /**
   * @fn setIntrPersist
   * @brief Set the Intr Persist of LTR308
   * @param persist: controls the N number of times the measurement data is outside the range defined by upper and lower threshold
   * @n eInterruptTrigger_1     Every ALS value out of threshold range asserts an interrupt (default)
   * @n eInterruptTrigger_2     2 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_3     3 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_4     4 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_5     5 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_6     6 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_7     7 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_8     8 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_9     9 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_10    10 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_11    11 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_12    12 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_13    13 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_14    14 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_15    15 consecutive ALS values out of threshold range assert an interrupt
   * @n eInterruptTrigger_16    16 consecutive ALS values out of threshold range assert an interrupt
   */
  void setIntrPersist(eIntrPersist_t persist);

  /**
   * @fn getIntrPersist
   * @brief Get the Intr Persist of LTR308
   * @return uint8_t: controls the N number of times the measurement data is outside the range defined by upper and lower threshold
   * @retval 0      Every ALS value out of threshold range asserts an interrupt (default)
   * @retval 1      2 consecutive ALS values out of threshold range assert an interrupt
   * @retval 2      3 consecutive ALS values out of threshold range assert an interrupt
   * @retval 3      4 consecutive ALS values out of threshold range assert an interrupt
   * @retval 4      5 consecutive ALS values out of threshold range assert an interrupt
   * @retval 5      6 consecutive ALS values out of threshold range assert an interrupt
   * @retval 6      7 consecutive ALS values out of threshold range assert an interrupt
   * @retval 7      8 consecutive ALS values out of threshold range assert an interrupt
   * @retval 8      9 consecutive ALS values out of threshold range assert an interrupt
   * @retval 9      10 consecutive ALS values out of threshold range assert an interrupt
   * @retval 10     11 consecutive ALS values out of threshold range assert an interrupt
   * @retval 11     12 consecutive ALS values out of threshold range assert an interrupt
   * @retval 12     13 consecutive ALS values out of threshold range assert an interrupt
   * @retval 13     14 consecutive ALS values out of threshold range assert an interrupt
   * @retval 14     15 consecutive ALS values out of threshold range assert an interrupt
   * @retval 15     16 consecutive ALS values out of threshold range assert an interrupt
   */
  uint8_t getIntrPersist(void);

  /**
   * @fn setThreshold
   * @brief Sets the upper limit and lower limit of the threshold
   * @param thres: upperLimit and lowerLimit
   * @n thres.upperLimit (up to 20-bits) (default 0x0FFFFF)
   * @n thres.lowerLimit (up to 20-bits) (default 0x000000)
   */
  void setThreshold(sThres_t thres);

  /**
   * @fn setThreshold
   * @brief Sets the upper limit and lower limit of the threshold
   * @param upperLimit: (up to 20-bits) (default 0x0FFFFF)
   * @param lowerLimit: (up to 20-bits) (default 0x000000)
   */
  void setThreshold(uint32_t upperLimit, uint32_t lowerLimit);

  /**
   * @fn getThreshold
   * @brief Gets the upper limit and lower limit of the threshold
   * @return sThres_t: upperLimit and lowerLimit
   * @retval sThres_t.upperLimit (up to 20-bits) (default 0x0FFFFF)
   * @retval sThres_t.lowerLimit (up to 20-bits) (default 0x000000)
   */
  sThres_t getThreshold();

  /**
   * @fn getLux
   * @brief Convert raw data to lux  (Lux = (0.6 * ALSDATA) / (GAIN * INT))
   * @param gain: The gain of this sensor
   * @param resolution: The resolution of this sensor
   * @param alsData: The ALS Data of this sensor
   * @return double: The converted lux value
   */
  double getLux(eGain_t gain, eResolution_t resolution, uint32_t alsData);

  /**
   * @fn getLux
   * @brief Convert raw data to lux   (Lux = (0.6 * ALSDATA) / (GAIN * INT))
   * @param alsData: The ALS Data of this sensor
   * @return double: The converted lux value
   */
  double getLux(uint32_t alsData);
  ~DFRobot_LTR308();

private:

  /**
   * @fn readReg
   * @brief Read register function
   * @param reg: Register address 8bits
   * @param pBuf: Storage and buffer for data to be read
   * @param size: Length of data to be read
   * @return bool: Indicates returning read register status
   * @retval true: Reading succeeded
   * @retval false: Reading failed
   */
  bool readReg(uint8_t reg, void* pBuf, size_t size);

  /**
   * @fn writeReg
   * @brief Write register function
   * @param reg: Register address 8bits
   * @param pBuf: Storage and buffer for data to be written
   * @param size: Length of data to be written
   * @return bool: Indicates returning write register status
   * @retval true: Writing succeeded
   * @retval false: Writing failed
   */
  bool writeReg(uint8_t reg, void* pBuf, size_t size);
};

#endif