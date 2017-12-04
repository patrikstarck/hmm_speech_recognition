/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : temp_sensor_drv.h
 *    Description : Temperature sensor STCN75 driver include file
 *
 *    History :
 *    1. Date        : July 28, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 4269 $
 **************************************************************************/
#include "includes.h"

#ifndef __TEMP_SENSOR_DRV_H
#define __TEMP_SENSOR_DRV_H

#ifdef  TEMP_SENSOR_DRV_GLOBAL
#define TEMP_SENSOR_DRV_EXTERN
#else
#define TEMP_SENSOR_DRV_EXTERN  extern
#endif

#define TEMP_SENSOR_SENSOR_ADDR     0x96
#define TEMP_SENOSR_COMP_MODE       FALSE
#define TEMP_SENOSR_INTR_MODE       TRUE

/*************************************************************************
 * Function Name: TempSensor_Init
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Init Temperature sensor
 *
 *************************************************************************/
Boolean TempSensor_Init (void);

/*************************************************************************
 * Function Name: TempSensorShutdown
 * Parameters: Boolean Shutdown
 *
 * Return: Boolean
 *
 * Description: Enable/Disable sensor shutdown
 *
 *************************************************************************/
Boolean TempSensorShutdown (Boolean Shutdown);

/*************************************************************************
 * Function Name: TempSensor_Conf
 * Parameters: Flo32 TOS, Flo32 THYS, Boolean Mode, Int32U FaultTol
 *
 * Return: Boolean
 *
 * Description: Temperature sensor config
 *
 *************************************************************************/
Boolean TempSensor_Conf (Flo32 TOS, Flo32 THYS, Boolean Mode,
                         Int32U FaultTol);

/*************************************************************************
 * Function Name: TempSensorGetTemp
 * Parameters: pFlo32 pTemp, pBoolean pAlarm
 *
 * Return: Boolean
 *
 * Description: Temperature sensor get temperature and alarm state
 *
 *************************************************************************/
Boolean TempSensorGetTemp (pFlo32 pTemp, pBoolean pAlarm);

#endif // __TEMP_SENSOR_DRV_H
