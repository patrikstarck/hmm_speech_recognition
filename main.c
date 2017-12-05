/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : Vx.x.x
* Date               :
* Description        : Main program body
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


/*
FFT:40
H-mult:27
mel_tot:40
*/

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Private variables ---------------------------------------------------------*/
Int32U CriticalSecCntr;

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

/*Sampled sound buffers*/
uint16_t adc_sample_buffer[SAMPLE_BUFFER_LENGTH];
uint16_t adc_sample_buffer_overlap[SAMPLE_BUFFER_LENGTH];

/*Test data*/
float32_t frame_power[129]={0.919234219606967,2.33299349351531,131.430411463052,287.644107706566,109.821191588645,1177.15839979831,1631.98871192288,542.286784112919,14.9261526478802,357.488070963738,256.366238185232,15.9533468999523,0.0773882967743689,10.4718856293044,4.90268819166957,17.7434464685045,65.6201858829443,104.297832963192,53.5702458420142,41.4977454398681,47.7401531964056,5.12237769993290,26.7057871455505,12.3960217937510,0.908442463346279,50.6824275382759,130.761660244894,99.3760128206861,11.4236276688786,4.11421266597096,22.3454545119935,43.0858536623546,21.0210262277773,10.9413122538063,19.9410171554077,26.7542587256648,15.9392860198084,8.92455573123926,17.2927367273060,48.7567607657858,34.8416200993278,35.3003230975222,11.8976994492144,0.135004099965742,2.25596250387799,8.96549208736801,4.56297808939745,1.92526520938987,21.4772636252041,46.5798617861815,33.2106276995165,13.5862878392417,6.45570798300452,0.641334244368443,0.0256781713059060,1.76564535654941,0.816176221723345,2.03842540074694,10.9972486310441,14.9479067054754,6.02222354269253,0.766466527983373,4.64035780613468,9.16824932413326,1.35329013527987,14.6112056545833,29.8465396572167,45.0480287207607,67.2252108934342,61.2988669270343,21.5880814818347,15.6914985219066,26.3808345444654,7.08253694663345,3.84897145213686,9.78003126183809,22.2370538945538,24.7375975542727,11.9302898001757,10.5030102647912,9.71489725719142,1.84010958896599,1.91498110469401,5.49579422396884,0.320701349295795,13.7218291795652,13.4372142707041,19.3403210357898,29.8603290156457,7.14934941955385,0.961970212983457,11.3580561244152,43.3401595804555,73.1206439601915,60.3728368246052,10.7006723268295,1.67105053729363,4.33998813426103,1.78299967581777,3.78516963034976,7.45633016925743,8.98236433875215,12.6975475055490,14.8693262500720,14.1362207657299,2.07608368209111,6.22473572320338,14.8560006605914,12.5275105030586,5.51292855778817,6.33497860809764,7.30230464007482,0.929290923060751,11.5866698254924,25.8981166918714,10.7964939946845,0.635147347375397,1.45797095103051,2.18037932959397,4.56989203593712,3.51009724123093,0.292323324335008,0.149172320233589,0.509732538524275,0.719552144199072,0.0617591863918364,0.0764363216977142,0.0103265799445625,0.101216600274090};
arm_matrix_instance_f32 frame_power_mat = {129, 1, frame_power};
float32_t MFCC[13];
arm_matrix_instance_f32 MFCC_mat = {13,1,MFCC};


void main(void) 
{
 

  
  /*Init the display*/
// InitDisplay();
  
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  ENTR_CRT_SECTION();
  SystemInit();
  EXT_CRT_SECTION();

  //Start and config clocks
  PRCC_Configuration();
  
  //Config GPIO-pins
  PGPIO_Configuration();
  
  enableLed(6);
  //disableLed(6);
  
  //Config NVIC(Nested Vectored Interrupt controller)
  PRNVIC_Conf();
  
  //Config the ADC
  PADC_Init_func();
  
  //Config the DMA
  PDMA_Configuration();
  
  //Config the DAC
  PDAC_Init_func();
  
  //Init the lexicon
  initLexicon();
  
  //Test the lexicon search function
 uint8_t string[22] = {2,2,20,0,0,1,1,0,2,2,2,0,2,2,2,2,2,5,1,4,2,4};
 uint8_t outputSequence[NUMBER_OF_WORDS];
 searchPattern(&outputSequence[0],&string[0],22);
 uint8_t in[6]={4,100,100,100,100,2};
 uint8_t out[6];
 sequenceConverter(&out[0],&in[0],6);
 
 //Exract mfcc from fft frame
 simple_mel_extractor_v2(&frame_power_mat,&MFCC_mat);
 
 // Assign vectors to matrices
 speech_HMM[0].mu = &speech_mu_1_mat;
 speech_HMM[0].sig = &speech_sigma_1_mat;
 speech_HMM[0].det = &speech_det_1;
 speech_HMM[0].inv =	&speech_sigma_inverse_1_mat;

 speech_HMM[1].mu = &speech_mu_2_mat;
 speech_HMM[1].sig = &speech_sigma_2_mat;
 speech_HMM[1].det = &speech_det_2;
 speech_HMM[1].inv =	&speech_sigma_inverse_2_mat;

 speech_HMM[2].mu = &speech_mu_3_mat;
 speech_HMM[2].sig = &speech_sigma_3_mat;
 speech_HMM[2].det = &speech_det_3;
 speech_HMM[2].inv =	&speech_sigma_inverse_3_mat;

 speech_HMM[3].mu = &speech_mu_4_mat;
 speech_HMM[3].sig = &speech_sigma_4_mat;
 speech_HMM[3].det = &speech_det_4;
 speech_HMM[3].inv =	&speech_sigma_inverse_4_mat;

 speech_HMM[4].mu = &speech_mu_5_mat;
 speech_HMM[4].sig = &speech_sigma_5_mat;
 speech_HMM[4].det = &speech_det_5;
 speech_HMM[4].inv =	&speech_sigma_inverse_5_mat;

 speech_HMM[5].mu = &speech_mu_6_mat;
 speech_HMM[5].sig = &speech_sigma_6_mat;
 speech_HMM[5].det = &speech_det_6;
 speech_HMM[5].inv =	&speech_sigma_inverse_6_mat;

 speech_HMM[6].mu = &speech_mu_7_mat;
 speech_HMM[6].sig = &speech_sigma_7_mat;
 speech_HMM[6].det = &speech_det_7;
 speech_HMM[6].inv =	&speech_sigma_inverse_7_mat;

 speech_HMM[7].mu = &speech_mu_8_mat;
 speech_HMM[7].sig = &speech_sigma_8_mat;
 speech_HMM[7].det = &speech_det_8;
 speech_HMM[7].inv =	&speech_sigma_inverse_8_mat;

 speech_HMM[8].mu = &speech_mu_9_mat;
 speech_HMM[8].sig = &speech_sigma_9_mat;
 speech_HMM[8].det = &speech_det_9;
 speech_HMM[8].inv =	&speech_sigma_inverse_9_mat;

 speech_HMM[9].mu = &speech_mu_10_mat;
 speech_HMM[9].sig = &speech_sigma_10_mat;
 speech_HMM[9].det = &speech_det_10;
 speech_HMM[9].inv =	&speech_sigma_inverse_10_mat;

 speech_HMM[10].mu = &speech_mu_11_mat;
 speech_HMM[10].sig = &speech_sigma_11_mat;
 speech_HMM[10].det = &speech_det_11;
 speech_HMM[10].inv =	&speech_sigma_inverse_11_mat; 

 run_all();
  
while (1)
  {
    //interrupts does the job
  }

}

void InitDisplay(void) {
  GLCD_PowerUpInit(NULL);
  GLCD_Backlight(BACKLIGHT_ON);
  DelayResolution100us(5000);

  GLCD_SetFont(&Terminal_9_12_6,0x000F00,0x00FF0);
  GLCD_TextSetPos(2,2);
}

void enableLed(uint16_t ledNumber) {
  switch(ledNumber) {
    case(6):
      GPIO_SetBits(GPIOC,GPIO_Pin_6);
      break;
    case(7):
      GPIO_SetBits(GPIOC,GPIO_Pin_7);
      break;
    case(8):
      GPIO_SetBits(GPIOC,GPIO_Pin_8);
      break;
    case(9):
      GPIO_SetBits(GPIOC,GPIO_Pin_9);
      break;
  default:
    break;
  }
}

void disableLed(uint16_t ledNumber) {
  switch(ledNumber) {
    case(6):
      GPIO_ResetBits(GPIOC,GPIO_Pin_6);
      break;
    case(7):
      GPIO_ResetBits(GPIOC,GPIO_Pin_7);
      break;
    case(8):
      GPIO_ResetBits(GPIOC,GPIO_Pin_8);
      break;
    case(9):
      GPIO_ResetBits(GPIOC,GPIO_Pin_9);
      break;
  default:
    break;
  }
}

void PGPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Configure PC.06 (ADC Channel6) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    /* Configure PA.00 (ADC Channel0) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure DAC channe1 & channel2 outputs pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
     /* Configure PE1 (USER button) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /* Configure PC6-9 LEDs as output */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
      /* SEL Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  

}

void PDAC_Init_func(void) {
  
  DAC_InitTypeDef            DAC_InitStructure;
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  DMA_InitTypeDef            DMA_InitStructure;

  /* TIM6 Configuration */
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = SAMPLING_RATE/2; //5000 = 9.6kHz(?)
  TIM_TimeBaseStructure.TIM_Prescaler =1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  /* TIM6 TRGO selection */
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  
  /* TIM6 enable counter */
  TIM_Cmd(TIM6, ENABLE);
  
  TIM_ITConfig(TIM6, TIM_FLAG_Update, ENABLE);
  
  /* DAC channel1 Configuration */
 // DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO; //No trigger currently for DAC. Is instead triggered when writing to register
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);
  
  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);

  /* Enable DAC Channel2 */
  DAC_Cmd(DAC_Channel_2, ENABLE);
}

void PRCC_Configuration(void)
{

/* Enable peripheral clocks --------------------------------------------------*/
  /* Enable GPIO and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC
| RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG
| RCC_APB2Periph_AFIO, ENABLE);

  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable ADC1  clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
  
   /* TIM3&6&7 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM7 | RCC_APB1Periph_TIM6, ENABLE);
  
   /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

}

void PRNVIC_Conf(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure and enable ADC interrupt */
  //This is for ADC-interrupts
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
    /* Configure and enable TIM3 interrupt */
  //This is for TIM3-interrupts
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 // NVIC_Init(&NVIC_InitStructure);
  
     /* Configure and enable TIM6 interrupt */
  //This is for TIM6-interrupts
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  
  //Enable DMA2 channel 3 IRQ Channel */
  //This is for DMA-interrupts
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
      /* Enable the EXTI3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel =EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  EXTI_ClearITPendingBit(EXTI_Line1);
  NVIC_Init(&NVIC_InitStructure);
  


}

void PADC_Init_func(void )
{
  
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  
  /* TIM3 Configuration */
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = SAMPLING_RATE/2; //5000 = 9.6kHz(?)
  TIM_TimeBaseStructure.TIM_Prescaler =1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* TIM3 TRGO selection */
  TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
  
  /* TIM7 Configuration */
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = SAMPLING_RATE/2; //5000 = 9.6kHz(?)
  TIM_TimeBaseStructure.TIM_Prescaler =SAMPLING_RATE;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

  /* TIM7 enable counter */
  TIM_Cmd(TIM7, ENABLE);
  
 // TIM_ITConfig(TIM3, TIM_FLAG_Update, ENABLE);
  

  ADC_InitTypeDef	     ADC_InitStructure;

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  //TIM3 is external trigger for ADC
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;//ADC_ExternalTrigConv_None;//
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel6 configuration *///The sampling cycles can be modified for better(or worse) result
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5); 

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable EOC interupt */
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);


  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);

  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);

  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}


void PDMA_Configuration() {
  
  DMA_InitTypeDef            DMA_InitStructure;

  /* DMA2 channel3 configuration */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; //Address to ADC-buffer
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adc_sample_buffer[0]; //Address to memory buffer
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ; //Peripheral to memoery
  DMA_InitStructure.DMA_BufferSize = SAMPLE_BUFFER_LENGTH; //Size of buffer
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //Address of input is always the same
  DMA_InitStructure.DMA_MemoryInc =DMA_MemoryInc_Enable ; //Increment memory address automatically
  DMA_InitStructure.DMA_PeripheralDataSize =  DMA_PeripheralDataSize_HalfWord ; //16bit, do not change
  DMA_InitStructure.DMA_MemoryDataSize =  DMA_MemoryDataSize_HalfWord ; //16bit, do not change
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //Refill after filled
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  
  /*Enable, init and start*/
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_HT, ENABLE);
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
  DMA_Cmd(DMA1_Channel1, ENABLE);        
}

/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: u32 Dly
 *
 * Return: none
 *
 * Description: Delay ~ (arg * 100us)
 *
 *************************************************************************/
void DelayResolution100us(u32 Delay)
{
  for(; Delay; Delay--)
  {
    for(volatile u32 j = DLY_100US; j; j--)
    {
    }
  }
}

