// Heder 

// Init all variables
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#include "includes.h"

extern float32_t sound_vec[VEC_LENGTH];
extern float32_t window[FRAME_LENGTH];
extern float32_t frame[FRAME_LENGTH];
extern float32_t fft_frame[FRAME_LENGTH];

extern float32_t p_xn_zn[NUMBER_OF_STATES];
extern float32_t X[NUMBER_OF_MFCC];
extern float32_t MFCC_vec[NUMBER_OF_MFCC];

extern arm_matrix_instance_f32 fft_mat;
extern arm_matrix_instance_f32 MFCC_output_mat;
extern arm_matrix_instance_f32 p_xn_zn_mat;
extern arm_matrix_instance_f32 obs_X;

extern float32_t speech_path[PATH_LENGTH];
extern float32_t speech_filtered_path[PATH_LENGTH];
extern uint8_t speech_trans_path[TRANS_PATH_LENGTH];
extern float32_t speech_logV[NUMBER_OF_STATES];
extern arm_matrix_instance_f32 speech_logV_mat;
extern arm_matrix_instance_f32 speech_path_mat;
extern arm_matrix_instance_f32 speech_filtered_path_mat;
extern arm_matrix_instance_f32 speech_trans_path_mat;


//memcpy(&dest[0],&source[0],sizeof(source));


extern struct speech speech_HMM[NUMBER_OF_STATES];

extern float32_t speech_mu_1[NUMBER_OF_MFCC];
extern float32_t speech_mu_2[NUMBER_OF_MFCC];
extern float32_t speech_mu_3[NUMBER_OF_MFCC];
extern float32_t speech_mu_4[NUMBER_OF_MFCC];
extern float32_t speech_mu_5[NUMBER_OF_MFCC];
extern float32_t speech_mu_6[NUMBER_OF_MFCC];
extern float32_t speech_mu_7[NUMBER_OF_MFCC];
extern float32_t speech_mu_8[NUMBER_OF_MFCC];
extern float32_t speech_mu_9[NUMBER_OF_MFCC];
extern float32_t speech_mu_10[NUMBER_OF_MFCC];
extern float32_t speech_mu_11[NUMBER_OF_MFCC];

extern arm_matrix_instance_f32 speech_mu_1_mat;
extern arm_matrix_instance_f32 speech_mu_2_mat;
extern arm_matrix_instance_f32 speech_mu_3_mat;
extern arm_matrix_instance_f32 speech_mu_4_mat;
extern arm_matrix_instance_f32 speech_mu_5_mat;
extern arm_matrix_instance_f32 speech_mu_6_mat;
extern arm_matrix_instance_f32 speech_mu_7_mat;
extern arm_matrix_instance_f32 speech_mu_8_mat;
extern arm_matrix_instance_f32 speech_mu_9_mat;
extern arm_matrix_instance_f32 speech_mu_10_mat;
extern arm_matrix_instance_f32 speech_mu_11_mat;

extern float32_t speech_sigma_1[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_2[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_3[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_4[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_5[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_6[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_7[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_8[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_9[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_10[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_11[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];

extern arm_matrix_instance_f32 speech_sigma_1_mat;
extern arm_matrix_instance_f32 speech_sigma_2_mat;
extern arm_matrix_instance_f32 speech_sigma_3_mat;
extern arm_matrix_instance_f32 speech_sigma_4_mat;
extern arm_matrix_instance_f32 speech_sigma_5_mat;
extern arm_matrix_instance_f32 speech_sigma_6_mat;
extern arm_matrix_instance_f32 speech_sigma_7_mat;
extern arm_matrix_instance_f32 speech_sigma_8_mat;
extern arm_matrix_instance_f32 speech_sigma_9_mat;
extern arm_matrix_instance_f32 speech_sigma_10_mat;
extern arm_matrix_instance_f32 speech_sigma_11_mat;

extern float32_t speech_sigma_inverse_1[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_2[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_3[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_4[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_5[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_6[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_7[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_8[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_9[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_10[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];
extern float32_t speech_sigma_inverse_11[(NUMBER_OF_MFCC*NUMBER_OF_MFCC)];

extern arm_matrix_instance_f32 speech_sigma_inverse_1_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_2_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_3_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_4_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_5_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_6_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_7_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_8_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_9_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_10_mat;
extern arm_matrix_instance_f32 speech_sigma_inverse_11_mat;

extern float32_t speech_det_1;
extern float32_t speech_det_2;
extern float32_t speech_det_3;
extern float32_t speech_det_4;
extern float32_t speech_det_5;
extern float32_t speech_det_6;
extern float32_t speech_det_7;
extern float32_t speech_det_8;
extern float32_t speech_det_9;
extern float32_t speech_det_10;
extern float32_t speech_det_11;


extern float32_t speech_A[A_SIZE];
extern arm_matrix_instance_f32 speech_A_mat;

#endif /* INIT_H_ */
