/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : step_motor_drv.c
 *    Description : Step Motor Driver
 *
 *    History :
 *    1. Date        : July 19, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 39 $
 **************************************************************************/
#define STEP_MOTOR_GLOBAL
#include "step_motor_drv.h"

static Boolean _Direction;
static Int32U _Steps;

/*************************************************************************
 * Function Name: StepMotorIntrHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Step motor interrupt handler
 *
 *************************************************************************/
void StepMotorIntrHandler(void)
{
  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  if (_Steps && (0 == --_Steps))
  {
    TIM_Cmd(TIM1,DISABLE);
  }
}

/*************************************************************************
 * Function Name: StepMotorInit
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init Step motor
 *
 *************************************************************************/
void StepMotorInit (void)
{
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

  // Enable clock
  RCC_APB2PeriphResetCmd(  RCC_APB2Periph_AFIO  | RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD
                         | RCC_APB2Periph_GPIOE | RCC_APB2Periph_TIM1,
                           DISABLE);
  RCC_APB2PeriphClockCmd(  RCC_APB2Periph_AFIO  | RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD
                         | RCC_APB2Periph_GPIOE | RCC_APB2Periph_TIM1,
                           ENABLE);

  TIM_Cmd(TIM1,DISABLE);

  GPIO_InitStructure.GPIO_Pin =  ENA_A_MASK ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENA_A_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  ENA_B_MASK;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENA_B_PORT, &GPIO_InitStructure);

  StepMotorStop();

  /* Init PWM TIM1 */
  /* PWM (TIM1/CH1P) PE9 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  /* PWM (TIM1/CH1N) PE8 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* PWM (TIM1/CH2P) PE11 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  /* PWM (TIM1/CH2N) PE10 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Map TIM1 OC1/OC2 */
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);

  TIM_InternalClockConfig(TIM1);

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = DEF_SPEED;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFF; // 8 bit resolution
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

  /* Channel 1 Configuration in TOGGLE mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0x80;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC1Init(TIM1,&TIM_OCInitStructure);

  /* Channel 2 Configuration in TOGGLE mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC2Init(TIM1,&TIM_OCInitStructure);

  /* Double buffered */
  TIM_ARRPreloadConfig(TIM1,ENABLE);

  /* Enable the TIM1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

  TIM_CtrlPWMOutputs(TIM1,ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM1,ENABLE);
}

/*************************************************************************
 * Function Name: StepMotorRun
 * Parameters: Int32U Steps
 *
 * Return: none
 *
 * Description: Step motor run
 *
 *************************************************************************/
void StepMotorRun (Int32U Steps)
{
TIM_OCInitTypeDef TIM_OCInitStructure;
  if (0 == Steps)
  {
    return;
  }

  ENTR_CRT_SECTION();
  if ((Int32U)-1L == Steps)
  {
    // Disable steps counting
    _Steps = 0;
  }
  else
  {
    _Steps += Steps;
  }
  EXT_CRT_SECTION();

  if (_Direction)
  {
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0x80;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
  }
  else
  {
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0x80;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
  }

  GPIO_WriteBit(ENA_A_PORT,ENA_A_MASK,Bit_SET);
  GPIO_WriteBit(ENA_B_PORT,ENA_B_MASK,Bit_SET);
  /* TIM1 counter enable */
  TIM_Cmd(TIM1,ENABLE);
}

/*************************************************************************
 * Function Name: StepMotorStop
 * Parameters: none
 *
 * Return: none
 *
 * Description: Step motor stop
 *
 *************************************************************************/
void StepMotorStop (void)
{
  // TIM1 counter disable
  TIM_Cmd(TIM1,DISABLE);
  // Add some delay for setup a position
  for(volatile int i = 4000; i; i--);
  GPIO_WriteBit(ENA_A_PORT,ENA_A_MASK,Bit_RESET);
  GPIO_WriteBit(ENA_B_PORT,ENA_B_MASK,Bit_RESET);
  _Steps = 0;
}

/*************************************************************************
 * Function Name: StepMotorSet
 * Parameters: Int32U  Speed, Boolean Dir, Int32U Steps
 *
 * Return: none
 *
 * Description: Step motor operation set
 *
 *************************************************************************/
void StepMotorSet (Int32U  Speed, Boolean Dir)
{
  _Direction = Dir;
  Speed *= 61;
  Speed = 0xFFFFUL - Speed;
  if (Speed < 0x1000)
  {
    Speed = 0x1000;
  }
  else if (Speed > 0xFFFF)
  {
    Speed = 0xFFFF;
  }
  TIM1->PSC = Speed;
}

/*************************************************************************
 * Function Name: StepMotorSet
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Return motor state (stop/move)
 *
 *************************************************************************/
Boolean StepMotorDone (void)
{
  return(0 == _Steps);
}

/*************************************************************************
 * Function Name: StepMotorDeg2Steps
 * Parameters: Flo32 Deg
 *
 * Return: Int32U
 *
 * Description: Convert degrees to steps
 *
 *************************************************************************/
Int32U StepMotorDeg2Steps (Flo32 Deg)
{
Int32U Steps;
  Deg /= 360.0/(Flo32)MOTOR_STEPS;
  Steps = (Int32U)Deg;
  return(Steps);
}

/*************************************************************************
 * Function Name: StepMotorSteps2Deg
 * Parameters: Int32U Steps
 *
 * Return: Flo32
 *
 * Description: Convert steps to degrees
 *
 *************************************************************************/
Flo32 StepMotorSteps2Deg (Int32U Steps)
{
Flo32 Deg;
  Deg = Steps;
  Deg *= (360.0/(Flo32)MOTOR_STEPS);
  return(Deg);
}
