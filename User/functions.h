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
#define MATH_PI 3.141592653589793
#define NUMBER_OF_STATES 11
#define NUMBER_OF_MFCC 13
#define PATH_LENGTH 5
#define TRANS_PATH_LENGTH 10
#define FRAME_LENGTH 256
#define VEC_LENGTH 10000

//Define struct
typedef struct speech {
	arm_matrix_instance_f32* mu;
	arm_matrix_instance_f32* sig;
	arm_matrix_instance_f32* inv;
	float32_t* det;

}speech;

#endif