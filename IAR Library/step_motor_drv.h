/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : step_motor_drv.h
 *    Description : Step Motor Driver include file
 *
 *    History :
 *    1. Date        : July 19, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 39 $
 **************************************************************************/
#include "includes.h"

#ifndef __STEP_MOTOR_DRV_H
#define __STEP_MOTOR_DRV_H

#ifdef  STEP_MOTOR_GLOBAL
#define STEP_MOTOR_EXTERN
#else
#define STEP_MOTOR_EXTERN  extern
#endif

#define ENA_A_MASK  GPIO_Pin_7
#define ENA_A_PORT  GPIOB

#define ENA_B_MASK  GPIO_Pin_10
#define ENA_B_PORT  GPIOD

#define DEF_SPEED   140

#define MOTOR_STEPS 10

/*************************************************************************
 * Function Name: StepMotorIntrHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Step motor interrupt handler
 *
 *************************************************************************/
void StepMotorIntrHandler(void);

/*************************************************************************
 * Function Name: StepMotorInit
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init Step motor
 *
 *************************************************************************/
void StepMotorInit (void);

/*************************************************************************
 * Function Name: StepMotorRun
 * Parameters: Int32U Steps
 *
 * Return: none
 *
 * Description: Step motor run
 *
 *************************************************************************/
void StepMotorRun (Int32U Steps);

/*************************************************************************
 * Function Name: StepMotorStop
 * Parameters: none
 *
 * Return: none
 *
 * Description: Step motor stop
 *
 *************************************************************************/
void StepMotorStop (void);

/*************************************************************************
 * Function Name: StepMotorSet
 * Parameters: Int32U  Speed, Boolean Dir, Int32U Steps
 *
 * Return: none
 *
 * Description: Step motor operation set
 *
 *************************************************************************/
void StepMotorSet (Int32U  Speed, Boolean Dir);

/*************************************************************************
 * Function Name: StepMotorSet
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Return motor state (stop/move)
 *
 *************************************************************************/
Boolean StepMotorDone (void);

/*************************************************************************
 * Function Name: StepMotorDeg2Steps
 * Parameters: Flo32 Deg
 *
 * Return: Int32U
 *
 * Description: Convert degrees to steps
 *
 *************************************************************************/
Int32U StepMotorDeg2Steps (Flo32 Deg);

/*************************************************************************
 * Function Name: StepMotorSteps2Deg
 * Parameters: Int32U Steps
 *
 * Return: Flo32
 *
 * Description: Convert steps to degrees
 *
 *************************************************************************/
Flo32 StepMotorSteps2Deg (Int32U Steps);

#endif // __STEP_MOTOR_DRV_H
