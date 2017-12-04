/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : temp_sensor_drv.h
 *    Description : Temperature sensor STCN75 driver
 *
 *    History :
 *    1. Date        : July 28, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 39 $
 **************************************************************************/
#define TEMP_SENSOR_DRV_GLOBAL
#include "temp_sensor_drv.h"

typedef enum _temp_sensor_regs_t
{
  TEMP_REG = 0, CONF_REG, THYS_REG, TOS_REG
} temp_sensor_regs_t;

/*************************************************************************
 * Function Name: TempSensor_Init
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Init Temperature sensor
 *
 *************************************************************************/
Boolean TempSensor_Init (void)
{
GPIO_InitTypeDef GPIO_InitStructure;
Int8U Data[3];

  // Enable GPIOB port
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB , DISABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  // Init temperature sensor interrupt signal
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  if(FALSE == I2C1_Open())
  {
    return(FALSE);
  }
  // Init Temperature sensor to default
  Data[0] = CONF_REG;
  Data[1] = 0;
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 2))
  {
    I2C1_Close();
    return(FALSE);
  }

  // THYS 75C
  Data[0] = THYS_REG;
  Data[1] = 0x4B;
  Data[2] = 0x00;
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 3))
  {
    I2C1_Close();
    return(FALSE);
  }

  // TOS 80C
  Data[0] = TOS_REG;
  Data[1] = 0x50;
  Data[2] = 0x00;
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 3))
  {
    I2C1_Close();
    return(FALSE);
  }

  I2C1_Close();
  return(TRUE);
}

/*************************************************************************
 * Function Name: TempSensorShutdown
 * Parameters: Boolean Shutdown
 *
 * Return: Boolean
 *
 * Description: Enable/Disable sensor shutdown
 *
 *************************************************************************/
Boolean TempSensorShutdown (Boolean Shutdown)
{
Int8U Data[2];
  if(FALSE == I2C1_Open())
  {
    return(FALSE);
  }
  Data[0] = CONF_REG;
  // Read config reg
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 1))
  {
    I2C1_Close();
    return(FALSE);
  }
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR | 0x1, &Data[1], 1))
  {
    I2C1_Close();
    return(FALSE);
  }
  if (Shutdown)
  {
    Data[1] |= 1U << 0;
  }
  else
  {
    Data[1] &= ~(1U << 0);
  }
  // Write config reg
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data,2))
  {
    I2C1_Close();
    return(FALSE);
  }
  I2C1_Close();
  return(TRUE);
}

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
                         Int32U FaultTol)
{
Int8U Data[3];
Int16S Temp;

  if(FALSE == I2C1_Open())
  {
    return(FALSE);
  }
  // Configure the fault tolerance
  Data[0] = CONF_REG;
  // Read config reg
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 1))
  {
    I2C1_Close();
    return(FALSE);
  }
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR | 0x1, &Data[1], 1))
  {
    I2C1_Close();
    return(FALSE);
  }
  Data[1] &= ~0x18;
  Data[1] |= (FaultTol & 3) << 3;

  // Write config reg
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data,2))
  {
    I2C1_Close();
    return(FALSE);
  }
  // Set Tos
  Temp = (Int16S)(TOS * 256.0);
  Data[0] = TOS_REG;
  Data[1] = Temp>>8;
  Data[2] = Temp;
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 3))
  {
    I2C1_Close();
    return(FALSE);
  }
  // Set Thys
  Temp = (Int16S)(THYS * 256.0);
  Data[0] = THYS_REG;
  Data[1] = Temp>>8;
  Data[2] = Temp;
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 3))
  {
    I2C1_Close();
    return(FALSE);
  }
  I2C1_Close();
  return(TRUE);
}

/*************************************************************************
 * Function Name: TempSensorGetTemp
 * Parameters: pFlo32 pTemp, pBoolean pAlarm
 *
 * Return: Boolean
 *
 * Description: Temperature sensor get temperature and alarm state
 *
 *************************************************************************/
Boolean TempSensorGetTemp (pFlo32 pTemp, pBoolean pAlarm)
{
Int8U Data[2];
Int16S Temp;

  if(FALSE == I2C1_Open())
  {
    return(FALSE);
  }

  if(Bit_SET == GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10))
  {
    *pAlarm = FALSE;
  }
  else
  {
    *pAlarm = TRUE;
  }

  // Configure the fault tolerance
  Data[0] = TEMP_REG;
  // Read config reg
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR, Data, 1))
  {
    I2C1_Close();
    return(FALSE);
  }
  if(FALSE == I2C1_DataTransfer(TEMP_SENSOR_SENSOR_ADDR | 0x1, Data, 2))
  {
    I2C1_Close();
    return(FALSE);
  }
  I2C1_Close();
  Temp = (Data[0] << 8) | Data[1];

  *pTemp = (Flo32)Temp;
  *pTemp /= 256.0;
  return(TRUE);
}
