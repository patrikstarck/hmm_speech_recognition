/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : glcd_ll.c
 *    Description : GLCD low level functions
 *
 *    History :
 *    1. Date        : December 2, 2006
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 39 $
 **************************************************************************/
#include "glcd_ll.h"

static Int32U Width;

/*************************************************************************
 * Function Name: GLCD_SetReset
 * Parameters: Boolean State
 * Return: none
 *
 * Description: Set reset pin state
 *
 *************************************************************************/
void GLCD_SetReset (Boolean State)
{
  GPIO_WriteBit(LCD_RST_PORT,LCD_RST_MASK,(State)?Bit_SET:Bit_RESET);
}

/*************************************************************************
 * Function Name: GLCD_SetBacklight
 * Parameters: Int8U Light
 * Return: none
 *
 * Description: Set backlight pin state
 *
 *************************************************************************/
void GLCD_Backlight (Int8U Light)
{
  TIM5->CCR4 = Light;
}

/*************************************************************************
 * Function Name: GLCD_LLInit
 * Parameters: none
 * Return: none
 *
 * Description: Init Reset and Backlight control outputs
 *
 *************************************************************************/
void GLCD_LLInit (void)
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
GPIO_InitTypeDef GPIO_InitStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;

  // Enable GPIO clock and release reset
  RCC_APB2PeriphClockCmd(  RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_GPIOD,
                         ENABLE);
  RCC_APB2PeriphResetCmd(  RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA
                         | RCC_APB2Periph_GPIOD,
                         DISABLE);

  // LCD Reset output PB14
  GPIO_InitStructure.GPIO_Pin =  LCD_RST_MASK;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LCD_RST_PORT, &GPIO_InitStructure);

  GLCD_SetReset(0);

	// LCD backlight PWM 8bit init
  // PWM DAC (TIM5/CH4) 8 bit PA3
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Map TIM5 OC4 to PA3
  GPIO_PinRemapConfig(GPIO_Remap_TIM5CH4_LSI,DISABLE);

  // Init PWM TIM5
  // Enable Timer5 clock and release reset
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5,DISABLE);

  TIM_InternalClockConfig(TIM5);

  // Time base configuration
  TIM_TimeBaseStructure.TIM_Prescaler = 140;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFF; // 8 bit resolution
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

  // Channel 4 Configuration in PWM mode
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0x00;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC4Init(TIM5,&TIM_OCInitStructure);
  // Double buffered
  TIM_ARRPreloadConfig(TIM5,ENABLE);
  // TIM3 counter enable
  TIM_Cmd(TIM5,ENABLE);

  GLCD_Backlight(0);
}

/*************************************************************************
 * Function Name: LcdSpiChipSelect
 * Parameters: Boolean Select
 * Return: none
 *
 * Description: SPI Chip select control
 * Select = true  - Chip is enable
 * Select = false - Chip is disable
 *
 *************************************************************************/
void GLCD_SPI_ChipSelect (Boolean Select)
{
  GPIO_WriteBit(LCD_CS_PORT,LCD_CS_MASK,(Select)?Bit_RESET:Bit_SET);
}

/*************************************************************************
 * Function Name: LcdSpiSetWordWidth
 * Parameters: Int32U Data
 * Return: Boolean
 *
 * Description: Set SPI word width
 *
 *************************************************************************/
Boolean GLCD_SPI_SetWordWidth (Int32U Data)
{
  if(   (8 != Data)
     && (9 != Data))
  {
    return(FALSE);
  }

  Width = Data;
  return(TRUE);
}

/*************************************************************************
 * Function Name: LcdSpiSetClockFreq
 * Parameters: Int32U Frequency
 * Return: Int32U
 *
 * Description: Set SPI clock
 *
 *************************************************************************/
/*
Int32U GLCD_SPI_SetClockFreq (Int32U Frequency)
{
Int32U Fspi = SYS_GetFpclk(Ssp1_PCLK_OFFSET);
Int32U Div = 2;
  while((Div * Frequency) < Fspi)
  {
    if((Div += 2) == 254)
    {
      break;
    }
  }
  Ssp1CPSR = Div;
  return(Fspi/Div);
}
*/
/*************************************************************************
 * Function Name: GLCD_SPI_Init
 * Parameters: Int32U Clk, Int32U Width
 * Return: none
 *
 * Description: Init SPI
 *
 *************************************************************************/
void GLCD_SPI_Init(Int32U Clk, Int32U Width)
{
GPIO_InitTypeDef GPIO_InitStructure;
  // Enable GPIO clock and release reset
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,
                         ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,
                         DISABLE);

  // Configure SPI2_CLK, SPI2_MOSI, SPI2_nCS1, Card Present and Write Protect pins
  // Chip select - PC3
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = LCD_CS_MASK;
  GPIO_Init(LCD_CS_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = LCD_SPI_SCLK_MASK | LCD_SPI_MOSI_MASK;
  GPIO_Init(LCD_SPI_PORT, &GPIO_InitStructure);


  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = LCD_SPI_MISO_MASK;
  GPIO_Init(LCD_SPI_PORT, &GPIO_InitStructure);

  // Chip select
  GLCD_SPI_ChipSelect(0);
  GLCD_SPI_CLK_H();

  // Chip select
  GLCD_SPI_ChipSelect(FALSE);

  // Set data width
  GLCD_SPI_SetWordWidth(Width);

}

/*************************************************************************
 * Function Name: GLCD_SPI_TranserByte
 * Parameters: Int32U Data
 * Return: Int32U
 *
 * Description: Transfer byte from SPI
 *
 *************************************************************************/
Int32U GLCD_SPI_TranserByte (Int32U Data)
{
Int32U InData = 0;
Int32U Mask;
  for (Mask = 1UL << (Width-1); Mask; Mask>>= 1)
  {
    // Clock Low
    GLCD_SPI_CLK_L();
    // Set Data
    if (Mask & Data)
    {
      GLCD_SPI_MOSI_H();
    }
    else
    {
      GLCD_SPI_MOSI_L();
    }
    InData <<= 1;
    // Clock High
    __no_operation();
    __no_operation();
    __no_operation();
    GLCD_SPI_CLK_H();
    // Get Data
    if (GLCD_SPI_MIS0())
    {
      ++InData;
    }
    __no_operation();
    __no_operation();
    __no_operation();
  }
  return(InData);
}

/*************************************************************************
 * Function Name: GLCD_SPI_SendBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Write block of data to SPI
 *
 *************************************************************************/
void GLCD_SPI_SendBlock (pInt8U pData, Int32U Size)
{
Int32U OutCount = Size;
  while (OutCount--)
  {
    GLCD_SPI_TranserByte(*pData++ | 0x100);
  }
}

/*************************************************************************
 * Function Name: GLCD_SPI_ReceiveBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Read block of data from SPI
 *
 *************************************************************************/
void GLCD_SPI_ReceiveBlock (pInt8U pData, Int32U Size)
{
  while (Size)
  {
    *pData++ = GLCD_SPI_TranserByte(0xFFFF0);
    --Size;
  }
}
