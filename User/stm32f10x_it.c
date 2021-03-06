/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "arm_math.h"

/*Button variable*/
uint16_t buttonPressed = 0;

/*Output*/
uint16_t playback_soundBuffer_index = 0;
void outputSound() ;


/***/
uint8_t prev_state=0;
void saveBuffer();
/**/


unsigned int cnt1 = 0;
unsigned int cnt2 = 0;

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/
    
    
    
    void DMA2_Channel1_IRQHandler(void)
{
  uint8_t tmp =1;
}

/*Interrupts from DMA-channel when half filled and filled*/
void DMA1_Channel1_IRQHandler(void)
{

  
  /*Do the when the buffer is half filled*/
  if(DMA_GetFlagStatus(DMA1_FLAG_HT1) != RESET) { 
    DMA_ClearFlag(DMA1_FLAG_HT1);
    

    /*Copy the sampled buffer to be an overlapping buffer that contains previos adc samples as well*/
    memcpy(&adc_sample_buffer_overlap[0],&adc_sample_buffer[SAMPLE_BUFFER_LENGTH/2],sizeof(uint16_t)*SAMPLE_BUFFER_LENGTH/2);
    memcpy(&adc_sample_buffer_overlap[SAMPLE_BUFFER_LENGTH/2],&adc_sample_buffer[0],sizeof(uint16_t)*SAMPLE_BUFFER_LENGTH/2);
    
    /*Do something here with adc_sample_buffer_overlap*/

    
  }
  /*Do the when the buffer is fully filled*/
  if(DMA_GetFlagStatus(DMA_IT_TC) != RESET) { 
    DMA_ClearFlag(DMA_IT_TC);
    
    /*Copy the sampled buffer to be an overlapping buffer that contains previos adc samples as well*/
    memcpy(&adc_sample_buffer_overlap[0],&adc_sample_buffer[0],sizeof(uint16_t)*SAMPLE_BUFFER_LENGTH/2);
    memcpy(&adc_sample_buffer_overlap[SAMPLE_BUFFER_LENGTH/2],&adc_sample_buffer[SAMPLE_BUFFER_LENGTH/2],sizeof(uint16_t)*SAMPLE_BUFFER_LENGTH/2);

    /*Do something here with adc_sample_buffer_overlap*/
   // saveBuffer();
    
  }
  


    cnt1 = TIM7->CNT; 


  


        //Convert to float
  for(int i=0;i<FRAME_LENGTH;i++) {
    adc_sample_buffer_overlap_f32[i]=(((float32_t)adc_sample_buffer_overlap[i]) - 2048);
  }
  
  preEmphasis(&adc_sample_buffer_overlap_f32[0], FRAME_LENGTH, &adc_sample_buffer_overlap_f32_2[0]);
    preprocessing(adc_sample_buffer_overlap_f32,fft_frame,window,FRAME_LENGTH); // Window and transform
    simple_mel_extractor_v2(&fft_mat,&MFCC_output_mat); // Extract MFCC
    logp_xn_zn(MFCC_output_mat,speech_HMM,&p_xn_zn_mat,NUMBER_OF_STATES,NUMBER_OF_MFCC); // Calculate B
    viterbi_log_NR(&speech_A_mat,&p_xn_zn_mat,&speech_path_mat,&speech_logV_mat,PATH_LENGTH,NUMBER_OF_STATES); //Get path
    path_filter(&speech_path_mat,&speech_filtered_path_mat,PATH_LENGTH); // Filter Path
    trans_path(&speech_filtered_path_mat,speech_trans_path,PATH_LENGTH,TRANS_PATH_LENGTH); // Get transfer path
    
    
    if(prev_state!=speech_trans_path[9]) {
        prev_state=speech_trans_path[9];
      
    
    
  //    for(int i=0;i<10;i++) {
  //      printf("%u ",speech_trans_path[i]);
  //    }
      uint8_t outputSequence[NUMBER_OF_WORDS];
      searchPattern(&outputSequence[0],&speech_trans_path[0],10);
      uint8_t out[NUMBER_OF_WORDS];
      sequenceConverter(&out[0],&outputSequence[0],NUMBER_OF_WORDS);
      languageBuffer(&lang_buff[0], &out[0],2, NUMBER_OF_WORDS);
      searchCommando(&lang_buff[0],2);
      
        cnt2 = TIM7->CNT; 
 // printf("cnt1:%u cnt2:%u diff:%u \n",cnt1,cnt2,cnt2-cnt1);
     //  printf("\n");
        
//        
//      for(int i=0;i<NUMBER_OF_WORDS;i++) {
//        printf("%u ",out[i]);
//      }
//      printf("\n");
//      for(int i=0;i<2;i++) {
//        printf("%u ",lang_buff[i]);
//      }
//       printf("\n");
//      printf("----------------------------------------------\n");
      
      disableLed(7);
      disableLed(8);
      disableLed(9);
      if(lang_buff[1]==0) {
        enableLed(7);
      }
      if(lang_buff[1]==1) {
        enableLed(8);
      }
      if(lang_buff[1]==2) {
        enableLed(9);
      }

    }
   //   printf("%u ",speech_trans_path[9]);


  
}

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles I2C1 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_ER_IRQHandler(void)
{

}

/**
  * @brief  This function handles I2C1 Events interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_EV_IRQHandler(void)
{

}


/**
  * @brief  This function handles ADC 1,2 interrupt request.
  * @param  None
  * @retval None
  */
    
/*Interrupt called each time ADC fires*/
void ADC1_2_IRQHandler(void)
{
  
//  /*Clear status flag*/
 // ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
  
//  /*Sample the data*/
//  if(buttonPressed==1) {
//    if(SoundCounter<SAMPLE_BUFFER_LENGTH) {
//    //  TxBuffer2[SoundCounter] = ADC_GetConversionValue(ADC1);
//      SoundCounter++;
//    }
//    else {
//      SoundCounter=0;
//      buttonPressed=0;
//    //  getWordSize(&TxBuffer2[0],SOUND_FILE_LENGTH);
//    }
//  }

}



///*Save the whole sound buffer to terminal*/
void saveBuffer() {
  for(int i=0;i<SAMPLE_BUFFER_LENGTH;i++) {
    printf("%d ",adc_sample_buffer[i]);
  }

}

///*Calculate FFT on the buffer*/
void doFft(uint16_t *source, uint16_t length) {
  
  
//
//  /*Fill the buffer with floats(conversion)*/
//  for(uint16_t i=0; i<length; i++){
//    fft_input_and_output[i] = (float32_t)*(source+i);
//  }
// // printf("ok\r\n");
//  
//
//    
//  /*Do the FFT*/
//  arm_rfft_fast_f32(&S_RFFT_1, &fft_input_and_output[0],&fft_input_and_output[0],0);
//  arm_cmplx_mag_f32(&fft_input_and_output[0], &fft_input_and_output[0], length/2);
//  
//
//  
  //asd
  /*Init the cdt*/
 // arm_rfft_fast_init_f32(&S_RFFT_2, length/2);
 // arm_rfft_fast_f32(&S_RFFT_2, &fft_input_and_output[0],&fft_input_and_output[0],1);
  
 // arm_dct4_init_f32(&S_DCT, &S_RFFT_2, &S_CFFT_2,SAMPLE_SIZE,SAMPLE_SIZE/2,0);
 // arm_dct4_f32(&S_DCT,&fft_input_and_output[0],&fft_input_and_output[0]);
  
//  arm_max_f32(khz10+1, SAMPLE_SIZE/4, &maxvalue, &maxindex);
  
  /*Calculate the actual frequency*/
 // uint32_t max_freq = 62*maxindex+120; //Linnear regression formula against true freq

  /*Print stuff for debug*/
  //printf("Largest freq: %ld\r\n",max_freq);
  //printf("Max:[%ld]:%f Output=[",max_freq,maxvalue);
 /*   for(i=0; i<SAMPLE_SIZE/2; i++){
      printf("%f ",output_and_input[i]);
  }
*/
 // printf("FFT_FINISH \r\n");
}

/*Output input sound to DAC*/
void outputSound() {
  /*Play sound*/
  playback_soundBuffer_index++;
  
  if(playback_soundBuffer_index>=SAMPLE_BUFFER_LENGTH) {
    playback_soundBuffer_index=0;
  }
//  *(u32*)(DAC_DHR12L2_Address)=(u32)adc_sample_buffer[playback_soundBuffer_index];
//  *(u32*)(DAC_DHR12L1_Address)=(u32)adc_sample_buffer[playback_soundBuffer_index];
}

//Interrupts from TIM6-channel
void TIM6_IRQHandler(void)
{
  TIM_ClearFlag(TIM6,TIM_FLAG_Update);
  outputSound();
  

  //TIM_Cmd(TIM6, DISABLE);
 // getWordSize(&TxBuffer2[0],SOUND_FILE_LENGTH);
  
}

//Interrupts from TIM7-channel
void TIM7_IRQHandler(void)
{
  TIM_ClearFlag(TIM7,TIM_FLAG_Update);
  TIM_Cmd(TIM7, DISABLE);
  GPIO_ResetBits(GPIOE,GPIO_Pin_2);
  GPIO_ResetBits(GPIOE,GPIO_Pin_3);
}

/**
  * @brief  This function handles CAN RX0 interrupt request.
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
{

}

/**
  * @brief  This function handles TIM1 UP interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{

}

/**
  * @brief  This function handles EXTI 15-10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{

}

/**
  * @brief  This function handles EXTI 3 interrupt request.
  * @param  None
  * @retval None
  */

/*User button interrupt*/
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    /* SEL function */
 //   TIM_Cmd(TIM6, ENABLE);
   // DMA_Cmd(DMA1_Channel1, ENABLE);
 //   TIM_Cmd(TIM3, ENABLE);
    buttonPressed = 1;
//    TIM_Cmd(TIM3, ENABLE);
//    DMA_Cmd(DMA1_Channel1, ENABLE);
    /* Clear the EXTI Line 7 */
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
