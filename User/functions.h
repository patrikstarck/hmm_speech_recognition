#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "includes.h"

/*MFCC*/
void simple_mel_extractor_v2(arm_matrix_instance_f32 *frame_power, arm_matrix_instance_f32 *MFCC_mat);

/*Lexicon*/
void initLexicon() ;
void sequenceConverter(uint8_t* outSequence, uint8_t* inSequence, uint8_t length);
void searchPattern(uint8_t* output, uint8_t* sequence,uint8_t length);

/*Defines*/
#define NUMBER_OF_WORDS 2
#define MAX_SEQ_PER_WORD 20
#define MAX_SEQUENCES_PER_SEQ 20

#endif