/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : MAIN.H
* Author             : MCD Application Team
* Version            : V1.0.0
* Date               : 12/17/2008
* Description        : Main header file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Define */
#define SAMPLE_SIZE   256
#define SAMPLE_BUFFER_LENGTH SAMPLE_SIZE
#define SAMPLING_RATE 9000
#define DLY_100US  2000

#define DAC_DHR12L1_Address      0x4000740C
#define DAC_DHR12L2_Address      0x40007418

extern uint16_t adc_sample_buffer[SAMPLE_BUFFER_LENGTH];
extern uint16_t adc_sample_buffer_overlap[SAMPLE_BUFFER_LENGTH];
extern float32_t adc_sample_buffer_overlap_f32[SAMPLE_BUFFER_LENGTH];
extern float32_t adc_sample_buffer_overlap_f32_2[SAMPLE_BUFFER_LENGTH];


void PGPIO_Configuration(void);
void PDAC_Init_func(void);
void PRCC_Configuration(void);
void PRNVIC_Conf(void);
void PADC_Init_func(void );
void PDMA_Configuration();
void DelayResolution100us(u32 Delay);
void InitDisplay(void);

void enableLed(uint16_t ledNumber);
void disableLed(uint16_t ledNumber);


#endif /* __MAIN_H */
