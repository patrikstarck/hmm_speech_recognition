#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "includes.h"

// Define hmm struct

//Define struct
typedef struct speech speech;
struct speech{
	arm_matrix_instance_f32* mu;
	arm_matrix_instance_f32* sig;
	arm_matrix_instance_f32* inv;
	float32_t* det;

};

/*Defines*/
#define NUMBER_OF_WORDS 2
#define MAX_SEQ_PER_WORD 20
#define MAX_SEQUENCES_PER_SEQ 20
#define MATH_PI 3.141592653589793
#define NUMBER_OF_STATES 8
#define A_SIZE NUMBER_OF_STATES*NUMBER_OF_STATES
#define NUMBER_OF_MFCC 13
#define PATH_LENGTH 5
#define TRANS_PATH_LENGTH 10
#define FRAME_LENGTH 256
#define VEC_LENGTH 9000

/*MFCC*/
void simple_mel_extractor_v2(arm_matrix_instance_f32 *frame_power, arm_matrix_instance_f32 *MFCC_mat);

/*Lexicon*/
void initLexicon() ;
void sequenceConverter(uint8_t* outSequence, uint8_t* inSequence, uint8_t length);
void searchPattern(uint8_t* output, uint8_t* sequence,uint8_t length);
void framer(float32_t *in_vec,int length_in_vec,float32_t *frame,int frame_length,int frame_nr);
void windower(float32_t *window,float32_t *frame,int frame_length);
void preprocessing(float32_t *frame,float32_t *fft_frame,float32_t *window,int frame_size);
void logp_xn_zn(arm_matrix_instance_f32 observ,speech *mu_sig,arm_matrix_instance_f32 *xn_zn,uint8_t n_states,uint8_t n_features);
void MatrixMax(arm_matrix_instance_f32 *C,uint8_t col,float32_t *max,uint16_t *ind);
void MatVecMax(arm_matrix_instance_f32 *C,float32_t *max,uint16_t *ind);
void viterbi_log_NR(arm_matrix_instance_f32 *A,arm_matrix_instance_f32 *xn_zn,arm_matrix_instance_f32 *path,arm_matrix_instance_f32 *logV,uint8_t path_length,uint8_t n_states);
void path_filter(arm_matrix_instance_f32 *path,arm_matrix_instance_f32 *filtered_path,uint8_t path_length);
void trans_path(arm_matrix_instance_f32 *filtered_path,uint8_t *trans_path,uint8_t filtered_path_length,uint8_t trans_path_length);
void run_all();

#endif
