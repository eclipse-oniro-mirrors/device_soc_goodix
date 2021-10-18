/**
 *****************************************************************************************
 *
 * @file hbd_ctrl.h
 *
 * @brief GH30x sensor control library header.
 *
 *****************************************************************************************
 * @attention
  #####Copyright (c) 2019 GOODIX
  All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of GOODIX nor the names of its contributors may be used
    to endorse or promote products derived from this software without
    specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************
 */
#ifndef __HBD_CTRL_H__
#define __HBD_CTRL_H__

typedef unsigned char GU8;
typedef signed char GS8;
typedef unsigned short GU16;
typedef signed short GS16;
typedef long int GS32;
typedef unsigned long int GU32;
typedef float GF32;

/* Hbd commhandler return value type. */
typedef enum 
{
    COMM_CMD_ALGO_IN_MCU_HB_START = 0,
    COMM_CMD_ALGO_IN_MCU_HB_STOP,
    COMM_CMD_ALGO_IN_APP_HB_START,
    COMM_CMD_ALGO_IN_APP_HB_STOP,
    COMM_CMD_ALGO_IN_MCU_HRV_START,
    COMM_CMD_ALGO_IN_MCU_HRV_STOP,
    COMM_CMD_ALGO_IN_APP_HRV_START,
    COMM_CMD_ALGO_IN_APP_HRV_STOP,
    COMM_CMD_ADT_SINGLE_MODE_START,
    COMM_CMD_ADT_SINGLE_MODE_STOP,
    COMM_CMD_ADT_CONTINUOUS_MODE_START,
    COMM_CMD_ADT_CONTINUOUS_MODE_STOP,
    COMM_CMD_INVALID,
} EM_COMM_CMD_TYPE;

/* Hbd functiional state enum. */
typedef enum 
{
    HBD_FUNCTIONAL_STATE_DISABLE = 0, 
    HBD_FUNCTIONAL_STATE_ENABLE = 1,
} EM_HBD_FUNCTIONAL_STATE;

/* Hb sample rate enum. */
enum EM_HB_SAMPLING_RATE
{
    HB_SAMPLING_RATE_25HZ = 25,
    HB_SAMPLING_RATE_40HZ = 40,
    HB_SAMPLING_RATE_INVALID,
} ;

/* Hrv sample rate enum. */
enum EM_HRV_SAMPLING_RATE
{
    HRV_SAMPLING_RATE_100HZ = 100,
    HRV_SAMPLING_RATE_200HZ = 200,
    HRV_SAMPLING_RATE_INVALID,
} ;

/* Int status enum. */
enum EM_INT_STATUS
{
    INT_STATUS_CHIP_RESET = 0,
    INT_STATUS_NEW_DATA,
    INT_STATUS_FIFO_WATERMARK,
    INT_STATUS_FIFO_FULL,
    INT_STATUS_WEAR_DETECTED,
    INT_STATUS_UNWEAR_DETECTED,
    INT_STATUS_INVALID,
} ;

/* Hb start mode enum. */
enum EM_HB_START_MODE
{
    HB_START_MODE_HB = 0,
    HB_START_MODE_HRV,
    HB_START_MODE_INVAILD,
} ;

/* Adt start mode enum. */
enum EM_ADT_START_MODE
{
    ADT_START_MODE_WEAR_DETECT = 0,
    ADT_START_MODE_UNWEAR_DETECT,
    ADT_START_MODE_INVALID,
} ;

/* Adt mode flag enum. */
enum EM_HBD_ADT_MODE
{
	HBD_ADT_MODE_SINGLE = 0,
	HBD_ADT_MODE_CONTINUOUS,
	HBD_ADT_MODE_INVALID ,
};

/* I2c Low Two bit select enum. */
enum EM_HBD_I2C_ID_SEL
{
    HBD_I2C_ID_SEL_1L0L = 0,
    HBD_I2C_ID_SEL_1L0H,
    HBD_I2C_ID_SEL_1H0L,
    HBD_I2C_ID_SEL_1H0H,
    HBD_I2C_ID_INVALID,
};

/* Led pd select enum. */
typedef enum 
{
    HBD_LED_PD_SEL_INTERNAL = 0,
    HBD_LED_PD_SEL_EXTERNAL,
} EM_HBD_LED_PD_SEL;

/* Led logic channel map to hw led enum. */
typedef enum
{
    HBD_LED_LOGIC_CHANNEL_MAP_PHY012 = 0,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY021,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY102,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY120,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY201,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY210,
} EM_HBD_LED_LOGIC_CHANNEL_MAP;

/* Led Logic Channel1 & led2 mode. */
typedef enum 
{
    HBD_LOGIC_CHANNEL1_2_MODE_NORMAL = 0, 
    HBD_LOGIC_CHANNEL1_2_MODE_SYNC,
    HBD_LOGIC_CHANNEL1_2_MODE_SHARE_CONFIG,
    HBD_LOGIC_CHANNEL1_2_MODE_SYNC_SHARE_CONFIG,
} EM_HBD_LOGIC_CHANNEL1_2_MODE;

/* sample time enum. */
typedef enum 
{
    HBD_SAMPLE_TIME_32CYCLES = 0,
    HBD_SAMPLE_TIME_64CYCLES,
    HBD_SAMPLE_TIME_128CYCLES,
    HBD_SAMPLE_TIME_256CYCLES,
    HBD_SAMPLE_TIME_512CYCLES,
    HBD_SAMPLE_TIME_1024CYCLES,
    HBD_SAMPLE_TIME_2048CYCLES,
} EM_HBD_SAMPLE_TIME;

/* tia gain enum. */
typedef enum
{
    HBD_TIA_GAIN_0 = 0,
    HBD_TIA_GAIN_1,
    HBD_TIA_GAIN_2,
    HBD_TIA_GAIN_3,
    HBD_TIA_GAIN_4,
    HBD_TIA_GAIN_5,
    HBD_TIA_GAIN_6,
    HBD_TIA_GAIN_7,
} EM_HBD_TIA_GAIN;

/* Hb config struct type. */
typedef struct
{
    EM_HBD_FUNCTIONAL_STATE emHbModeFifoEnable;     // HB fifo enable flag
    GU16 usHbModeSampleRate;                        // HB sample rate
    EM_HBD_FUNCTIONAL_STATE emHrvModeFifoEnable;    // HRV fifo enable flag
    GU16 usHrvModeSampleRate;                       // HRV sample rate
} ST_HB_CONFIG_TYPE;

/* Adt config struct type. Notes: only logic channel0 & channel1 valid in adt mode. */
typedef struct
{
    EM_HBD_FUNCTIONAL_STATE emGINTEnable;                  // GINT enable flag
    EM_HBD_LED_LOGIC_CHANNEL_MAP emLedLogicChannelMap;     // Logic map
    EM_HBD_LED_PD_SEL emLogicChannel0PDSelect;             // Logic Channel0 PD select
    EM_HBD_LED_PD_SEL emLogicChannel1PDSelect;             // Logic Channel1 PD select
    GU8 uchLogicChannel0Current;                           // Logic Channel0 current cofig(1 step = 400uA)
    GU8 uchLogicChannel1Current;                           // Logic Channel1 current cofig(1 step = 400uA)
    EM_HBD_TIA_GAIN emLogicChannel0TiaGain;                // Logic Channel0 tia gain(valid value:0-7)
    EM_HBD_TIA_GAIN emLogicChannel1TiaGain;                // Logic Channel1 tia gain(valid value:0-7)
    EM_HBD_SAMPLE_TIME emSampleTime;                       // Sample time
} ST_ADT_CONFIG_TYPE;

/* Hbd init config struct type. */
typedef struct
{
    ST_HB_CONFIG_TYPE stHbInitConfig;
    ST_ADT_CONFIG_TYPE stAdtInitConfig;
} ST_HBD_INIT_CONFIG_TYPE;

/* Gsensor data struct type. */
typedef struct
{
    GU16 usXAxisVal; // X-Axis Value
    GU16 usYAxisVal; // Y-Axis Value
    GU16 usZAxisVal; // Z-Axis Value
} ST_GS_DATA_TYPE;

 
/* Hbd function return code definitions list. */
#define HBD_RET_OK                          (0)                /**< There is no error */
#define HBD_RET_GENERIC_ERROR               (-1)               /**< A generic error happens */
#define HBD_RET_PARAMETER_ERROR             (-2)               /**< Parameter error */
#define HBD_RET_COMM_NOT_REGISTERED_ERROR   (-3)               /**< I2c/Spi communication interface not registered error */
#define HBD_RET_COMM_ERROR                  (-4)               /**< I2c/Spi Communication error */
#define HBD_RET_RESOURCE_ERROR              (-5)               /**< Resource full or not available error */
#define HBD_RET_NO_INITED_ERROR             (-6)               /**< No inited error */
#define HBD_RET_LED_CONFIG_ALL_OFF_ERROR    (-7)               /**< Led config all off error */

/******* hbd init default config ****************
 * stHbInitConfig = { HBD_FUNCTIONAL_STATE_ENABLE,          /// hb mode fifo enable 
 *                    HB_SAMPLING_RATE_25HZ,                /// hb mode sample rate
 *                    HBD_FUNCTIONAL_STATE_ENABLE,          /// hrv mode fifo enable 
 *                    HRV_SAMPLING_RATE_100HZ,              /// hrv mode sample rate
 *                  }
 * stAdtInitConfig = { HBD_FUNCTIONAL_STATE_DISABLE,        /// GINT disable
 *                     HBD_LED_LOGIC_CHANNEL_MAP_PHY012,    /// Logic map
 *                     HBD_LED_PD_SEL_INTERNAL,             /// Logic Channel0 PD select
 *                     HBD_LED_PD_SEL_INTERNAL,             /// Logic Channel1 PD select
 *                     0x19,                                /// Logic Channel0 current 10mA (1 step = 400uA)
 *                     0x19,                                /// Logic Channel1 current 10mA (1 step = 400uA)
 *                     HBD_TIA_GAIN_3,                      /// Logic Channel0 tia gain
 *                     HBD_TIA_GAIN_3,                      /// Logic Channel1 tia gain
 *                     HBD_SAMPLE_TIME_128CYCLES,           /// sample time
 *                   }
 */
#define HBD_INIT_CONFIG_DEFAULT_DEF(var) ST_HBD_INIT_CONFIG_TYPE var={\
                                                                      {HBD_FUNCTIONAL_STATE_ENABLE, HB_SAMPLING_RATE_25HZ, HBD_FUNCTIONAL_STATE_ENABLE, HRV_SAMPLING_RATE_100HZ},\
                                                                      {HBD_FUNCTIONAL_STATE_DISABLE,\
                                                                      HBD_LED_LOGIC_CHANNEL_MAP_PHY012, \
                                                                      HBD_LED_PD_SEL_INTERNAL, \
                                                                      HBD_LED_PD_SEL_INTERNAL,\
                                                                      0x19, 0x19, HBD_TIA_GAIN_3, HBD_TIA_GAIN_3, HBD_SAMPLE_TIME_128CYCLES}\
                                                                    }


/****************************************************************
* Description: set i2c operation function
* Input:  uchI2cIdLowTwoBitsSelect: i2c low two bits addr selected, see EM_HBD_I2C_ID_SEL
          pI2cWriteFunc: i2c write function pointer
          pI2cReadFunc: i2c read function pointer
* Return: None
******************************************************************/
void HBD_SetI2cRW (GU8 uchI2cIdLowTwoBitsSelect,
                   GU8 (*pI2cWriteFunc)(GU8 uchDeviceId, const GU8 uchWriteBytesArr[], GU16 usWriteLen),  
                   GU8 (*pI2cReadFunc)(GU8 uchDeviceId, const GU8 uchCmddBytesArr[], GU16 usCmddLen, GU8 uchReadBytesArr[], GU16 usMaxReadLen));

/****************************************************************
* Description: set spi operation function
* Input:  pSpiWriteFunc: spi write function pointer
          pSpiReadFunc: spi read function pointer
          pSpiCSCtrlFunc: spi cs operation function pointer
* Return: None
******************************************************************/
void HBD_SetSpiRW (GU8 (*pSpiWriteFunc)(GU8 uchWriteBytesArr[], GU16 usWriteLen), 
                   GU8 (*pSpiReadFunc)(GU8 uchReadBytesArr[], GU16 usMaxReadLen),
                   void (*pSpiCSCtrlFunc)(GU8 uchCsLevelHigh));
                   
/****************************************************************
* Description: set delay function callback
* Input:  pDelayUsFunc:delay function callback
* Return: None
******************************************************************/
void HBD_SetDelayUsCallback (void (*pDelayUsFunc)(GU16 usUsec));

/****************************************************************
* Description: Set storage ctrl function
* Input:    pStorageWriteFunc: storage data write func ptr,
            pStorageReadFunc: storage data read func ptr,
            unConfigStorageAddr: sotrage addr,
* Return: None
******************************************************************/
void HBD_SetConfigStorageFunc (void (*pStorageWriteFunc)(GU32 unStoreAddr, GU8 uchBufferArr[], GU16 usLength), 
							   void (*pStorageReadFunc)(GU32 unStoreAddr, GU8 uchBufferArr[], GU16 usLength), 
							   GU32 unConfigStorageAddr);

/****************************************************************
* Description: load new GH30x config
* Input:    uchNewConfigArr: config array ,
            uchForceUpdateConfig: 1: need force update,0 :don't need, 
* Return: HBD_RET_OK:use new config arr, HBD_RET_GENERIC_ERROR:use the storage config arr,
******************************************************************/
GS8 HBD_LoadNewConfig (GU8 uchNewConfigArr[], GU8 uchForceUpdateConfig);

/****************************************************************
* Description: Communication operation interface confirm.
* Output:  None
* Return: HBD_RET_OK=GH30x comunicate ok, 
          HBD_RET_COMM_ERROR=GH30x comunicate error,
          HBD_RET_COMM_NOT_REGISTERED_ERROR=GH30x i2c/spi interface not registered,
******************************************************************/
GS8 HBD_CommunicationInterfaceConfirm (void);

/****************************************************************
* Description: init hbd configure parameters
* Input:    stHbInitConfigParam: Init Config struct ,see ST_HBD_INIT_CONFIG_TYPE,
* Return: HBD_RET_OK=success, 
          HBD_RET_PARAMETER_ERROR=paramters error,
          HBD_RET_COMM_ERROR=GH30x comunicate error, 
          HBD_RET_COMM_NOT_REGISTERED_ERROR=GH30x i2c/spi interface not registered
******************************************************************/
GS8 HBD_Init (ST_HBD_INIT_CONFIG_TYPE *stHbdInitConfigParam);

/****************************************************************
* Description: start hbd
* Input:  uchStartMode: HB_START_MODE_HB: Hb mode, HB_START_MODE_HRV: Hrv Mode, 
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
          HBD_RET_LED_CONFIG_ALL_OFF_ERROR=all Led disable error,
          HBD_RET_PARAMETER_ERROR=start mode parameter error, 
******************************************************************/
GS8 HBD_HbStart (GU8 uchStartMode);

/****************************************************************
* Description: stop hbd
* Input:  None
* Return: HBD_RET_OK=success, HBD_RET_NO_INITED_ERROR=fail:don't init success 
******************************************************************/
GS8 HBD_Stop (void);

/****************************************************************
* Description: start hbd
* Input:  uchStartMode: ADT_START_MODE_WEAR_DETECT: Wear detect mode, 
                        ADT_START_MODE_UNWEAR_DETECT: Unwear detect Mode, 
          uchAdtMode: HBD_ADT_MODE_SINGLE:single mode, 
                      HBD_ADT_MODE_CONTINUOUS: continuous mode
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=fail:don't init success 
          HBD_RET_PARAMETER_ERROR=fail:parameter error
******************************************************************/
GS8 HBD_AdtStart (GU8 uchStartMode, GU8 uchAdtMode);

/****************************************************************
* Description: get Int status 
* Input:  None
* Return: Status, see EM_INT_STATUS
******************************************************************/
GU8 HBD_GetIntStatus (void);

/****************************************************************
* Description: Pack rawdata package, if want get static state value, 
               param [stGsAxisValue]could set NULL 
* Input:  stGsAxisValue: acc value, see ST_GS_DATA_TYPE
* Return: rawdata package count
******************************************************************/
GU16 HBD_PollWithGSensor (ST_GS_DATA_TYPE *stGsAxisValue);

/****************************************************************
* Description: pack rawdata package with gsensor buffer, if want get static state value, 
               param [stGsAxisValue]could set NULL, or param [usGsDataNum] set less than freq
* Input:  stGsAxisValue: gsensor buffer data
          usGsDataNum: gsensor buffer len, must greater than hbd freq
* Return: rawdata package count
******************************************************************/
GU16 HBD_PollWithGSensorBuffer (ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum);

/****************************************************************
* Description: restart hbd if read done stop, must use with HBD_PollWithGSensorBuffer_Ex
* Input:  none, 
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
          HBD_RET_LED_CONFIG_ALL_OFF_ERROR=all Led disable error,
******************************************************************/
GS8 HBD_HbRestart_Ex (void);

/****************************************************************
* Description: pack rawdata with gsensor buffer, when read done hbd stop, 
               must use with HBD_HbRestart_Ex
* Input:  stGsAxisValue: gsensor buffer data
          usGsDataNum: gsensor buffer len, must greater than hbd freq
          puchReadingFlag: ptr of reading data flag 
          puchTimeoutFlag: ptr of timer timeout flag
* Return: rawdata package count
******************************************************************/
GU16 HBD_PollWithGSensorBuffer_Ex (ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, GU8 *puchReadingFlag, GU8 *puchTimeoutFlag);

/****************************************************************
* Description: pack rawdata with gsensor buffer, when read done hbd stop, 
               must use with HBD_HbRestart_Ex
* Input:  stGsAxisValue: gsensor buffer data
          usGsDataNum: gsensor buffer len, must greater than hbd freq
          puchReadingFlag: ptr of reading data flag 
          puchTimeoutFlag: ptr of timer timeout flag
* Return: rawdata package count
******************************************************************/
GU16 HBD_PollWithGSensorBuffer_Ex2 (ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, GU8 *puchReadingFlag, GU8 *puchTimeoutFlag);

/****************************************************************
* Description: calculate hbd_value and wearing detect use one Rawdata.
* Output:   puchHbValue:ptr of heartbeat value output
            puchWearingState:ptr of wearing state output
            puchWearingQuality: ptr of wearing quality output
            puchVoiceBroadcast: ptr of voice broadcast output
            pusRRvalue: ptr of RR value output 
* Return: refresh flag, if heartbeat value have refresh that return 1.
******************************************************************/
GU8 HBD_HbCalculateByOneRawdata (GU8 *puchHbValue, GU8 *puchWearingState, GU8 *puchWearingQuality, GU8 *puchVoiceBroadcast, GU16 *pusRRvalue);

/****************************************************************
* Description: calculate hbd_value and wearing detect use Rawdata buffer.
* Output:   puchHbValue:ptr of heartbeat value output
            puchWearingState:ptr of wearing state output
            puchWearingQuality: ptr of wearing quality output
            puchVoiceBroadcast: ptr of voice broadcast output
            pusRRvalue: ptr of RR value output 
* Return: refresh flag, if heartbeat value have refresh that return 1.
******************************************************************/
GU8 HBD_HbCalculateByRawdataBuffer (GU8 *puchHbValue, GU8 *puchWearingState, GU8 *puchWearingQuality, GU8 *puchVoiceBroadcast, GU16 *pusRRvalue);

/****************************************************************
* Description: enable wearing and setting direction array
* Input:    fDirectionArr: gsensor direction 
* Return: None
******************************************************************/
void HBD_EnableWearing (GF32 fDirectionArr[3]);

/****************************************************************
* Description: hrv rawdata pack
* Input:  None
* Return: length
******************************************************************/
GU16 HBD_HrvRawdataPack (void);

/****************************************************************
* Description: hrv fifo rawdata pack
* Input:  None
* Return: length
******************************************************************/
GU16 HBD_HrvFifoRawdataPack (void);

/****************************************************************
* Description: calculate hrv_value use one Rawdata.
* Output:   pusHrvRRValue:ptr of hrv RR value output
* Return: refresh flag, if hrv RR value have refresh that return 1.
******************************************************************/
GU8 HBD_HrvCalculateByOneRawdata(GU16 *pusHrvRRValue);

/****************************************************************
* Description: calculate hrv_value use Rawdata buffer.
* Output:   pusHrvRRValueArr:ptr of hrv RR value output array
* Return: refresh cnt, all count of RR value have refresh.
******************************************************************/
GU16 HBD_HrvCalculateByRawdataBuffer(GU16 *pusHrvRRValueArr);

/****************************************************************
* Description: Get version
* Input:    None,
* Return: library Hbd ctrl version
******************************************************************/
GS8 * HBD_GetHbdVersion(void);

/****************************************************************
* Description: Get hba algorithm version
* Input:    None,
* Return: library hba algorithm version
******************************************************************/
GS8 * HBD_GetHbaVersion(void);

/****************************************************************
* Description: Get hrv algorithm version
* Input:    None,
* Return: library hrv algorithm version
******************************************************************/
GS8 * HBD_GetHrvVersion(void);

/****************************************************************
* Description: Reset chip
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_COMM_NOT_REGISTERED_ERROR=GH30x i2c/spi interface not registered
******************************************************************/
GS8 HBD_ChipReset (void);

/****************************************************************
* Description: change Hb config
* Input:  uchMode: 0:Hrv reconfig, else Hb reconfig
* Return: HBD_RET_OK=success, 
          HBD_RET_PARAMETER_ERROR=fail:parameter error,
******************************************************************/
GS8 HBD_ChangeHbConfig (GU8 uchMode, EM_HBD_FUNCTIONAL_STATE emFifoEnable, GU16 usSampleRate);

/****************************************************************
* Description: set irq pluse width 
* Input:  uchIrqPluseWidth: irq width(us) setting (not allow set 0 ),  
* Return: HBD_RET_OK=success, 
          HBD_RET_PARAMETER_ERROR=fail:parameter error
******************************************************************/
GS8 HBD_SetIrqPluseWidth (GU8 uchIrqPluseWidth);

/****************************************************************
* Description: parse communicate receive data
* Input:    uchCommInterFaceId: this id from HBD_SetSendDataFunc return,
            uchDataBuffArr: data buff ptr of receive data,
			uchLen: data len of receive data,
* Return: see EM_COMM_CMD_TYPE typedef
******************************************************************/
EM_COMM_CMD_TYPE HBD_CommParseHandler (GU8 uchCommInterFaceId, GU8 uchDataBuffArr[], GU8 uchLen);

/****************************************************************
* Description: Set send data function
* Input:    pSendDataFunc: send data func ptr,
* Return: val > 0:communication interface id,
          HBD_RET_RESOURCE_ERROR: have no resource,
******************************************************************/
GS8 HBD_SetSendDataFunc (void (*pSendDataFunc)(GU8 uchDataBuffArr[], GU8 uchLen));

/****************************************************************
* Description: send Package 
* Input:    None,
* Return: None
******************************************************************/
void HBD_SendPackage (void);

#endif /* __HBD_CTRL_H__ */

/********END OF FILE********* (C) COPYRIGHT 2018 .********/
