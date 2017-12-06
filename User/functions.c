/*Includes*/

#include "includes.h"

/*********************************/
/******Variable declaration*******/
/*********************************/

arm_rfft_fast_instance_f32 S_RFFT_1;


/**************/
/*Lexicon Data*/
/**************/

/*Structures*/
struct Word {
  uint8_t* pho_seq[MAX_SEQ_PER_WORD]; //Sequence of phonemes
  uint8_t length[MAX_SEQ_PER_WORD];   //Length of each sequence in this word
  uint8_t nSeq;         //Number of sequences(must not be 20)
};

struct Word words[NUMBER_OF_WORDS]; //Struct that contains all words

//Init data
uint8_t number_of_sequences[NUMBER_OF_WORDS] = {4,2};
uint8_t word_sequence_length[NUMBER_OF_WORDS][MAX_SEQ_PER_WORD]={
  {5,4,6,4},
  {4,8}
};

uint8_t word_sequences[NUMBER_OF_WORDS][MAX_SEQ_PER_WORD][MAX_SEQUENCES_PER_SEQ] = {
  {{0,1,2,4,1},{1,2,4,1},{0,1,2,4,4,2 },{1,2,4,2}},
    {{2,20,0,0},{2,2,2,0,2,2,2,2}}
 };

/******END Lexicon data**********/



/********************/
/*    MFCC  data   */
/*******************/

//Ceplifter
float32_t ceplifter[13]={1,2.56546322100614,4.09905812525573,5.56956514302075,6.94704899201157,8.20346807339814,9.31324531789684,10.2537888611430,11.0059519488997,11.5544227097595,11.8880358606903,12,11.8880358606903};
arm_matrix_instance_f32 ceplifter_mat = {13, 1, ceplifter};

//Discrete cosine transform
float32_t DCT[260] = {0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.316227766016838,0.315252941349890,0.307490367669328,0.292156360634725,0.269628494389924,0.240461479767574,0.205373505467449,0.165228553867129,0.121015126908468,0.0738219058991409,0.0248109445657177,-0.0248109445657176,-0.0738219058991408,-0.121015126908468,-0.165228553867129,-0.205373505467449,-0.240461479767574,-0.269628494389924,-0.292156360634725,-0.307490367669328,-0.315252941349890,0.312334477467278,0.281761002650515,0.223606797749979,0.143564401525505,0.0494689214077114,-0.0494689214077113,-0.143564401525505,-0.223606797749979,-0.281761002650515,-0.312334477467278,-0.312334477467278,-0.281761002650515,-0.223606797749979,-0.143564401525505,-0.0494689214077114,0.0494689214077113,0.143564401525505,0.223606797749979,0.281761002650515,0.312334477467278,0.307490367669328,0.240461479767574,0.121015126908468,-0.0248109445657176,-0.165228553867129,-0.269628494389924,-0.315252941349890,-0.292156360634725,-0.205373505467450,-0.0738219058991408,0.0738219058991407,0.205373505467449,0.292156360634725,0.315252941349890,0.269628494389924,0.165228553867129,0.0248109445657179,-0.121015126908468,-0.240461479767574,-0.307490367669328,0.300750477503773,0.185874017230092,1.93633660727019e-17,-0.185874017230092,-0.300750477503773,-0.300750477503773,-0.185874017230092,-5.80900982181058e-17,0.185874017230092,0.300750477503773,0.300750477503773,0.185874017230092,9.68168303635097e-17,-0.185874017230092,-0.300750477503773,-0.300750477503773,-0.185874017230092,-1.35543562508914e-16,0.185874017230092,0.300750477503773,0.292156360634725,0.121015126908468,-0.121015126908468,-0.292156360634725,-0.292156360634725,-0.121015126908468,0.121015126908468,0.292156360634725,0.292156360634725,0.121015126908468,-0.121015126908468,-0.292156360634725,-0.292156360634725,-0.121015126908468,0.121015126908468,0.292156360634725,0.292156360634725,0.121015126908468,-0.121015126908468,-0.292156360634725,0.281761002650515,0.0494689214077114,-0.223606797749979,-0.312334477467278,-0.143564401525505,0.143564401525504,0.312334477467278,0.223606797749979,-0.0494689214077110,-0.281761002650515,-0.281761002650515,-0.0494689214077112,0.223606797749979,0.312334477467278,0.143564401525505,-0.143564401525505,-0.312334477467278,-0.223606797749979,0.0494689214077109,0.281761002650515,0.269628494389924,-0.0248109445657176,-0.292156360634725,-0.240461479767574,0.0738219058991407,0.307490367669328,0.205373505467450,-0.121015126908468,-0.315252941349890,-0.165228553867129,0.165228553867129,0.315252941349890,0.121015126908468,-0.205373505467449,-0.307490367669328,-0.0738219058991409,0.240461479767574,0.292156360634725,0.0248109445657175,-0.269628494389924,0.255833636800846,-0.0977197537924274,-0.316227766016838,-0.0977197537924275,0.255833636800846,0.255833636800847,-0.0977197537924273,-0.316227766016838,-0.0977197537924275,0.255833636800846,0.255833636800847,-0.0977197537924272,-0.316227766016838,-0.0977197537924276,0.255833636800846,0.255833636800847,-0.0977197537924272,-0.316227766016838,-0.0977197537924277,0.255833636800846,0.240461479767574,-0.165228553867129,-0.292156360634725,0.0738219058991407,0.315252941349890,0.0248109445657182,-0.307490367669328,-0.121015126908468,0.269628494389924,0.205373505467450,-0.205373505467449,-0.269628494389924,0.121015126908468,0.307490367669328,-0.0248109445657170,-0.315252941349890,-0.0738219058991410,0.292156360634725,0.165228553867129,-0.240461479767574,0.223606797749979,-0.223606797749979,-0.223606797749979,0.223606797749979,0.223606797749979,-0.223606797749979,-0.223606797749979,0.223606797749979,0.223606797749979,-0.223606797749979,-0.223606797749979,0.223606797749979,0.223606797749979,-0.223606797749979,-0.223606797749979,0.223606797749979,0.223606797749979,-0.223606797749979,-0.223606797749979,0.223606797749979,0.205373505467449,-0.269628494389924,-0.121015126908468,0.307490367669328,0.0248109445657179,-0.315252941349890,0.0738219058991406,0.292156360634725,-0.165228553867128,-0.240461479767574,0.240461479767574,0.165228553867129,-0.292156360634725,-0.0738219058991410,0.315252941349890,-0.0248109445657169,-0.307490367669328,0.121015126908468,0.269628494389924,-0.205373505467450,0.185874017230092,-0.300750477503773,-5.80900982181058e-17,0.300750477503773,-0.185874017230092,-0.185874017230093,0.300750477503773,1.74270294654317e-16,-0.300750477503773,0.185874017230093,0.185874017230093,-0.300750477503773,-8.52183846062801e-16,0.300750477503773,-0.185874017230092,-0.185874017230092,0.300750477503773,-1.55102667445532e-16,-0.300750477503773,0.185874017230092};
arm_matrix_instance_f32 DCT_mat = {13, 20, DCT};
 
//Mel filter bank
#define H2_ROW_LENGTH 19 
float32_t H2[380]={0.500000000000000,1,0.666666666666667,0.333333333333333,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.333333333333333,0.666666666666667,1,0.666666666666667,0.333333333333333,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.333333333333333,0.666666666666667,1,0.666666666666667,0.333333333333333,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.333333333333333,0.666666666666667,1,0.666666666666667,0.333333333333333,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.333333333333333,0.666666666666667,1,0.666666666666667,0.333333333333333,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.333333333333333,0.666666666666667,1,0.750000000000000,0.500000000000000,0.250000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0.250000000000000,0.500000000000000,0.750000000000000,1,0.750000000000000,0.500000000000000,0.250000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0.250000000000000,0.500000000000000,0.750000000000000,1,0.750000000000000,0.500000000000000,0.250000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0.250000000000000,0.500000000000000,0.750000000000000,1,0.750000000000000,0.500000000000000,0.250000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0.250000000000000,0.500000000000000,0.750000000000000,1,0.800000000000000,0.600000000000000,0.400000000000000,0.200000000000000,0,0,0,0,0,0,0,0,0,0,0,0.200000000000000,0.400000000000000,0.600000000000000,0.800000000000000,1,0.800000000000000,0.600000000000000,0.400000000000000,0.200000000000000,0,0,0,0,0,0,0,0,0,0,0.200000000000000,0.400000000000000,0.600000000000000,0.800000000000000,1,0.800000000000000,0.600000000000000,0.400000000000000,0.200000000000000,0,0,0,0,0,0,0,0,0,0,0.200000000000000,0.400000000000000,0.600000000000000,0.800000000000000,1,0.833333333333333,0.666666666666667,0.500000000000000,0.333333333333333,0.166666666666667,0,0,0,0,0,0,0,0,0,0.166666666666667,0.333333333333333,0.500000000000000,0.666666666666667,0.833333333333333,1,0.857142857142857,0.714285714285714,0.571428571428571,0.428571428571429,0.285714285714286,0.142857142857143,0,0,0,0,0,0,0,0.142857142857143,0.285714285714286,0.428571428571429,0.571428571428571,0.714285714285714,0.857142857142857,1,0.833333333333333,0.666666666666667,0.500000000000000,0.333333333333333,0.166666666666667,0,0,0,0,0,0,0,0.166666666666667,0.333333333333333,0.500000000000000,0.666666666666667,0.833333333333333,1,0.875000000000000,0.750000000000000,0.625000000000000,0.500000000000000,0.375000000000000,0.250000000000000,0.125000000000000,0,0,0,0,0,0,0.125000000000000,0.250000000000000,0.375000000000000,0.500000000000000,0.625000000000000,0.750000000000000,0.875000000000000,1,0.857142857142857,0.714285714285714,0.571428571428571,0.428571428571429,0.285714285714286,0.142857142857143,0,0,0,0,0,0.142857142857143,0.285714285714286,0.428571428571429,0.571428571428571,0.714285714285714,0.857142857142857,1,0.888888888888889,0.777777777777778,0.666666666666667,0.555555555555556,0.444444444444444,0.333333333333333,0.222222222222222,0.111111111111111,0,0,0,0,0.111111111111111,0.222222222222222,0.333333333333333,0.444444444444444,0.555555555555556,0.666666666666667,0.777777777777778,0.888888888888889,1,0.888888888888889,0.777777777777778,0.666666666666667,0.555555555555556,0.444444444444444,0.333333333333333,0.222222222222222,0.111111111111111,0,0,0.111111111111111,0.222222222222222,0.333333333333333,0.444444444444444,0.555555555555556,0.666666666666667,0.777777777777778,0.888888888888889,1,0.888888888888889,0.777777777777778,0.666666666666667,0.555555555555556,0.444444444444444,0.333333333333333,0.222222222222222,0.111111111111111,0,0};
arm_matrix_instance_f32 H2_mat = {20, 19, H2};
uint8_t H2_start[20]={9,11,14,17,20,23,26,30,34,38,42,47,52,57,63,70,76,84,91,100};

// Define work matrices
float32_t multi2[20];
arm_matrix_instance_f32 mat_multi_2 = {20,1,multi2}; 
float32_t Alog[(A_SIZE)]; // init A_plus_logV
float32_t c[(A_SIZE)]; // Init C
arm_matrix_instance_f32 A_plus_logV = {NUMBER_OF_STATES,NUMBER_OF_STATES,Alog};
arm_matrix_instance_f32 C_mat = {NUMBER_OF_STATES,NUMBER_OF_STATES,c};
float32_t X_minus_mu[NUMBER_OF_MFCC];
arm_matrix_instance_f32 X_minus_mu_mat = {NUMBER_OF_MFCC,1,X_minus_mu};
arm_matrix_instance_f32 X_minus_mu_mat_tran = {1,NUMBER_OF_MFCC,X_minus_mu};
float32_t multi[NUMBER_OF_MFCC];
arm_matrix_instance_f32 mat_multi = {1,NUMBER_OF_MFCC,multi};
/*****END MFCC data*******/





/***************************/
/********FUNCTIONS**********/
/***************************/



/***************/
/*MFCC function*/
/***************/

void simple_mel_extractor_v2(arm_matrix_instance_f32 *frame_power, arm_matrix_instance_f32 *MFCC_mat) {

  //Multiply with H(fancy way)
  for(int i=0;i<20;i++) {
    float32_t tmp_sum = 0;
    for(int j=0;j<H2_ROW_LENGTH-1;j++) {
      tmp_sum = tmp_sum + ((*(frame_power->pData+H2_start[i]+j))*H2[i*H2_ROW_LENGTH+j]);
    }
    *(mat_multi_2.pData+i)=tmp_sum;
  }

//  arm_mat_mult_f32(&H_mat,frame_power,&mat_multi);  //Heavier way to multiply with H 
    
  //Log
  for(int i=0;i<20;i++) {
    *(mat_multi_2.pData+i)=log(*(mat_multi_2.pData+i));
  }

  //DCT
  arm_mat_mult_f32(&DCT_mat,&mat_multi_2,MFCC_mat);

  //Ceplifter
  for(int i=0;i<13;i++) {
    *(MFCC_mat->pData+i)=(*(MFCC_mat->pData+i))*(*(ceplifter_mat.pData+i));
  }
  
  //Final is MFCC_mat
}

/*****END MFCC Functions*****/


/*******************/
/*Lexicon functions*/
/*******************/

void initLexicon() {
  //Loop through number of words
  for (int j=0;j<NUMBER_OF_WORDS;j++) {
    //For each word, loop through number of sequence
    for(int i=0;i<number_of_sequences[j];i++) {
      //Add the seqences to the struct array
      words[j].pho_seq[i] = &(word_sequences[j][i][0]);
      words[j].length[i]=word_sequence_length[j][i];
    }
    words[j].nSeq=number_of_sequences[j];
  }
}

void sequenceConverter(uint8_t* outSequence, uint8_t* inSequence, uint8_t length) {
  
  //Init output
  for(int i=0;i<length;i++) {
    *(outSequence+i)=100;
  }
  
  for(int i=0;i<length;i++) {
    uint8_t minIndex=0;
    uint8_t minValue=1000;
    for(int j=0;j<length;j++) {
      if(*(inSequence+j)<minValue) {
        minIndex=j;
        minValue = *(inSequence+j);
      }
    }
   if(minValue!=100) {
    *(outSequence+i)=minIndex;
    *(inSequence+minIndex)=100;
    }
   else {
     break;
   }
  }
  
}

void searchPattern(uint8_t* output, uint8_t* sequence,uint8_t length) {
  
  //Loop through all words
  for (int j=0;j<NUMBER_OF_WORDS;j++) {
    *(output+j) = 100;
    //Loop through all sequences for each word
    for(int i=0;i<words[j].nSeq;i++) {
      
      //Only find one sequence per word
      if(*(output+j)!= 100) {
        break;
      }
      
      uint8_t compareIndex = 0;
      for (int k=0;k<length;k++) {
        if(*(sequence+k)== *(words[j].pho_seq[i]+compareIndex)) {
          compareIndex++;
          
          //word found?
          if(compareIndex==words[j].length[i]) {
            *(output+j)=(k+1)-compareIndex;
            break;
          }
        }
        else {
          compareIndex = 0;
          if(*(sequence+k)== *(words[j].pho_seq[i]+compareIndex)) {
            compareIndex++;
          }
        }
      }
      
      
      
    }
  }

}

void logp_xn_zn(arm_matrix_instance_f32 observ,speech *mu_sig,arm_matrix_instance_f32 *xn_zn,uint8_t n_states,uint8_t n_features) {
		
		float32_t sum_val = 0;
	        float32_t C =  (-0.5)*n_features*log(2*MATH_PI);
		for(int i = 0;i<n_states;i++) {

			arm_mat_sub_f32(&observ,(mu_sig+i)->mu,&X_minus_mu_mat); // X-mu = out (X,mu,out)
			arm_mat_trans_f32(&X_minus_mu_mat,&X_minus_mu_mat_tran);
			arm_mat_mult_f32(&X_minus_mu_mat_tran,(mu_sig+i)->inv,&mat_multi); // A*B = out (A,B,Out)


			for(int k = 0;k<n_features;k++) {
				mat_multi.pData[k] = mat_multi.pData[k]*X_minus_mu_mat.pData[k];
			}

			sum_val = 0;
			for(int n = 0;n<mat_multi.numCols;n++) {
				sum_val = sum_val + mat_multi.pData[n];
			}
			(xn_zn->pData[i]) = C - *((mu_sig+i)->det)*0.5 - 0.5*sum_val;
		}


}

	/*Returns the maximum value*/
void MatrixMax(arm_matrix_instance_f32 *C,uint8_t col,float32_t *max,uint16_t *ind) {
		// This function takes the maximum value in a given colum col in the square matrix C
		// If C is 3x3 matrix then col must be a value on the set [0;2]
		float32_t maxvalue;
		*max = C->pData[col];
		for(int i = 1;i<C->numRows;i++) {
			maxvalue = C->pData[i*(C->numCols)+col];
			if(maxvalue>*max && *max > -1000000000) {
				*max = maxvalue;
				*ind = i;
			}
		}
}

void viterbi_log_NR(arm_matrix_instance_f32 *A,arm_matrix_instance_f32 *xn_zn,arm_matrix_instance_f32 *path,arm_matrix_instance_f32 *logV,uint8_t path_length,uint8_t n_states) {

		float32_t max_C = 0;
		uint16_t C_max_ind = 0;
		uint16_t PATH[NUMBER_OF_STATES];


		// Update path
		// last element in path: *(path+path_length-1);
		for(int i = 0;i<(path_length-1);i++) {
			path->pData[i] = path->pData[i+1];// Move all elements on step to the right
		}

		for(int i = 0;i<(n_states);i++) {
			for(int k = 0;k<n_states;k++) { // FIX IF: A->pData[k+i*n_states] = 0
				if(A->pData[k*n_states+i] == 0 || logV->pData[k] == 0) {
					A_plus_logV.pData[k*n_states+i] = -1000000000;
				}
				else {
					A_plus_logV.pData[k*n_states+i] = (A->pData[k*n_states+i])+logV->pData[k];
				}

				//A_plus_logV(k,i) = log(A(k,i)) + previous(1,k); Matlab ..
			}
		}


		for(int i = 0;i<(n_states);i++) {
			for(int k = 0;k<n_states;k++) {
				if (A_plus_logV.pData[k+i*n_states] == 0) {
					C_mat.pData[k*n_states+i] = -1000000000;
				}
				else {
					C_mat.pData[k*n_states+i] = A_plus_logV.pData[k+i*n_states]+xn_zn->pData[k];
				}
				//C(k,i) = A_plus_logV(i,k) + p_xn_zn(1,k); Matlab ..
			}
		}

		/*int ts = 0;

				for(int k = 0;k<(n_states*n_states);k++){
					ts = ts+1;
					trace_printf("   %f", C_mat.pData[k]);
					if (ts == n_states) {
						ts = 0;
						trace_printf(" \n");
					}
				}*/

		for(uint8_t i = 0;i<n_states;i++) {
			MatrixMax(&C_mat,i,&max_C,&C_max_ind);
			logV->pData[i] = max_C;
			PATH[i] = C_max_ind;
			//trace_printf("index \n%i\n",C_max_ind);
			//trace_printf("Max_val \n%f\n",max_C);
		}


		MatrixMax(logV,0,&max_C,&C_max_ind);
		path->pData[path_length-1] = C_max_ind;
		path->pData[path_length-1]  = PATH[(int)(path->pData[path_length-1])];

		for(int i = 0;i<NUMBER_OF_STATES;i++) {
			if (logV->pData[i] < -100000000) {
				logV->pData[i] = 0;
			}
		}
		/*for(int i = 0;i<NUMBER_OF_STATES;i++) {
			trace_printf("Logv \n%f\n",logV->pData[i]);
		}*/
		max_C = 0;
		for(int i = 0;i<n_states;i++) {
			max_C = max_C + logV->pData[i];
		}
		//trace_printf("Max_val \n%f\n",max_C);

		arm_mat_scale_f32(logV,1/max_C,logV);

}

void path_filter(arm_matrix_instance_f32 *path,arm_matrix_instance_f32 *filtered_path,uint8_t path_length) {
	filtered_path->pData[0] = path->pData[0];
	for(int i = 1;i<path_length;i++) {
		if(path->pData[i] ==  path->pData[i-1]) {
			filtered_path->pData[i] = path->pData[i];
		}
		else {
			filtered_path->pData[i] = filtered_path->pData[i-1];
		}
	}
}

void trans_path(arm_matrix_instance_f32 *filtered_path,uint8_t *trans_path,uint8_t filtered_path_length,uint8_t trans_path_length) {

	if(filtered_path->pData[filtered_path_length-1] == filtered_path->pData[filtered_path_length-2]) {
		// Do nothing
	}
	else {
		for(int i = 0;i<(trans_path_length-1);i++) {
			*(trans_path+i) = *(trans_path+i+1);// Move all elements on step to the right
		}
		*(trans_path +trans_path_length-1 ) = (uint8_t)(filtered_path->pData[filtered_path_length-1]);

	}
}

void framer(float32_t *in_vec,int length_in_vec,float32_t *frame,int frame_length,int frame_nr) {
		int frame_index = 0;
		int odd = 100;

		odd =frame_nr-(frame_nr/2 +frame_nr/2);

		if(frame_nr<2*(length_in_vec/frame_length)) {
			if(odd == 1) {
				frame_nr = (frame_nr/2)+1;
				for(int i = (frame_nr-1)*frame_length;i<(frame_length*frame_nr);i++) {
					*(frame+frame_index) = *(in_vec+i)*32768;
					frame_index++;
				}
			}
			if(odd == 0) {
				frame_nr = (frame_nr/2);
				for(int i = ((frame_nr-1)*frame_length+128);i<((frame_length*frame_nr)+128);i++) {
					*(frame+frame_index) = *(in_vec+i)*32768;
					frame_index++;
				}
			}

		}
		else {
			// This is bad!
		}
}

void windower(float32_t *window,float32_t *frame,int frame_length) {
		for(int i = 0;i<frame_length;i++){
			*(frame+i) = (*(frame+i))*(*(window+i));
		}
}


void preprocessing(float32_t *frame,float32_t *fft_frame,float32_t *window,int frame_size) {

	windower(window,frame,frame_size); // Apply blackman window

	arm_rfft_fast_init_f32(&S_RFFT_1, frame_size);
	arm_rfft_fast_f32(&S_RFFT_1, &frame[0],&fft_frame[0],0);
	arm_cmplx_mag_squared_f32(&fft_frame[0], &fft_frame[0], frame_size/2);
	for(int i = 0;i<(frame_size/2+1);i++) {
		*(fft_frame+i) = *(fft_frame+i)/256;
	}

}

void run_all() {
	
	
	
	for (int i = 1;i<2*(VEC_LENGTH/FRAME_LENGTH);i++) { // Main loop over length of signal
		framer(sound_vec,VEC_LENGTH,frame,FRAME_LENGTH,i); // Get new frame

	preprocessing(frame,fft_frame,window,FRAME_LENGTH); // Window and transform
	simple_mel_extractor_v2(&fft_mat,&MFCC_output_mat); // Extract MFCC
	logp_xn_zn(MFCC_output_mat,speech_HMM,&p_xn_zn_mat,NUMBER_OF_STATES,NUMBER_OF_MFCC); // Calculate B
	viterbi_log_NR(&speech_A_mat,&p_xn_zn_mat,&speech_path_mat,&speech_logV_mat,PATH_LENGTH,NUMBER_OF_STATES); //Get path
	path_filter(&speech_path_mat,&speech_filtered_path_mat,PATH_LENGTH); // Filter Path
	trans_path(&speech_filtered_path_mat,speech_trans_path,PATH_LENGTH,TRANS_PATH_LENGTH); // Get transfer path
	}
        
        for(int i=0;i<10;i++) {
          
          printf("%f ",speech_trans_path_mat.pData[i]);
        }
        
}


/*****END Lexicon functions*****/












//
//
///*Global variables accessible from all functions*/
////uint16_t output[SOUND_FILE_LENGTH/BUFFER_SIZE];
//uint16_t temp_v[BUFFER_SIZE];
//uint16_t mean_v[SOUND_FILE_LENGTH/BUFFER_SIZE];
//
//float32_t f_output_tmp[BUFFER_SIZE];
//float32_t f_output[BUFFER_SIZE];
//float32_t f_input[BUFFER_SIZE];
//uint16_t meanOfSoundSignal;
// 
///*FFT Instance*/
////arm_rfft_fast_instance_f32 S;
//
///*Sort ascending (Buble sort)*/
//void sort(uint16_t *number, uint16_t n) {
//
//    /* Sort the given array number, of length n */
//    int temp = 0, j, i;
//
//    for (i = 1; i < n; i++) {
//        for (j = 0; j < n - i; j++) {
//            if (number[j] > number[j + 1]) {
//                temp = number[j];
//                number[j] = number[j + 1];
//                number[j + 1] = temp;
//            }
//        }
//    }
//}
//
///*Returns a calculated tolerence*/
//uint16_t returnTol(uint16_t *in,uint16_t inLength) {
//  uint16_t tolerance = 0;
//  uint32_t x   = 0;
//  uint32_t x_2 = 0;
//  for(int i=1;i<inLength;i++) {
//  	x_2 = x_2 + (*(in+i))*(*(in+i));
//  	x   = x   + *(in+i);
//  }
//  tolerance = (uint16_t)sqrt((x_2 - (x*x/inLength))/inLength)/3;
//  return tolerance;
//}
//
///*Returns the maximum value*/
//uint16_t returnMax(uint16_t *in,uint16_t inLength) {
//  uint16_t maxvalue=*in;
//  for(int i=1;i<inLength;i++) {
//    if(*(in+i)>maxvalue) {
//      maxvalue=*(in+i);
//    }
//  }
//  return maxvalue;
//}
//
///*Returns the mean value (Not very good one)*/
//uint16_t returnMean(uint16_t *in,uint16_t inLength) {
//  uint32_t meanValue=0;
//  for(int i=0;i<inLength;i++) {
//      meanValue=meanValue+*(in+i);
//  }
//  meanValue=meanValue/inLength;
//  return (uint16_t)meanValue;
//}
//
///*Returns the mean value (Optimized version)*/
//uint16_t returnMean2(uint16_t *in,uint16_t inLength) {
//  float32_t meanValue=0;
//  for(int i=0;i<inLength;i++) {
//      meanValue=meanValue+(*(in+i)-meanValue)/(i+1);
//  }
//  return (uint16_t)meanValue;
//}
//
///*Returns the maximum index*/
//uint16_t floatReturnMaxIndex(float32_t *in,uint16_t inLength) {
//  uint16_t maxIndex=0;
//  float32_t maxvalue=*in;
//  for(int i=1;i<inLength;i++) {
//    if(*(in+i)>maxvalue) {
//      maxIndex=i;
//      maxvalue=*(in+i);
//    }
//  }
//  return maxIndex;
//}
//
//
///*Finds and returns the 3 largest peaks*/
//void returnThreeLargestIndex(float32_t *in,uint16_t inLength, uint16_t* index1, uint16_t* index2, uint16_t* index3) {
//  float32_t value1=0;
//  float32_t value2=0;
//  float32_t value3=0;
//  
//  for(int i=1;i<inLength-1;i++) {
//    
//    /*Find if it's a peak!*/
//    if(*(in+i)>*(in+i-1) && *(in+i)>*(in+i+1)) {
//           
//      
//      if((*(in+i)>value1)) {
//      
//      /*Shift down values in the vector*/
//      value3=value2;
//      *index3 = *index2;
//      value2=value1;
//      *index2 = *index1;
//      
//      *index1=i;
//      value1=*(in+i);
//      }
//    
//      else if(*(in+i)>value2) {
//
//        /*Shift down values in the vector*/
//        value3=value2;
//        *index3 = *index2;
//        
//        *index2=i;
//        value2=*(in+i);
//      }
//      
//      else if(*(in+i)>value3) {
//        
//        *index3=i;
//        value3=*(in+i);
//      }
//    
//    }
//    
//  }
//
//  
//}
//
//
///*Returns the "abs" when using a unsigned int. mean is the "zero level"*/
//uint16_t absOfUnsigned(uint16_t value,uint16_t mean) {
//  if(value<mean) {
//    return value+(mean-value);
//  }
//  else {
//    return value;
//  }
//}
//
/////*Function for detecting words in a sound file. 
////Calculates the power spectrum for each word by doing a fft in segments*/
////void getWordSize(uint16_t *soundIn,uint16_t soundInLength) {
////
////  /*Reset display(Suuuuper slow)*/
//// // InitDisplay();
////   
////  /*Print total input*/
////  printf("Input-Vector: "); 
////  for(int i=0;i<soundInLength;i++) {
////    printf("%u ",soundIn[i]);
////  }
////  printf("\n");
////  printf("\n");
////  printf("\n");
////
////
////  /*Define some variables*/
////  uint16_t dim_i = SOUND_FILE_LENGTH/BUFFER_SIZE;
////
////  printf("Mean spectrum: ");
////  /*Amplitude spectrum loop*/
////  for(int i=0;i<dim_i;i++) {
////    for(int j=0;j<BUFFER_SIZE;j++) {
////      temp_v[j] = absOfUnsigned(soundIn[i*BUFFER_SIZE+j],meanOfSoundSignal);
////    }
////    mean_v[i] = returnMean(&temp_v[0],BUFFER_SIZE);
////    printf("%u ",mean_v[i]);
////  }
////  printf("\n");
////  
////  /*Compute moving average of the amplitude spectrum*/
//// // filter(2,mean_v,&output[0],dim_i);
////  
////  /*Mean of the amplitude spectrum*/
//// // uint16_t meanOfAmplitudeSpectrum = returnMean2(&output[0],dim_i);
////  
////  /*Mean of the total signal*/
////  meanOfSoundSignal = returnMean2(soundIn,soundInLength);
////  printf("Mean: %u \n", meanOfSoundSignal);
////  
////  /*Tolerance to detect when a word is found*/
//// // uint16_t tolerance = meanOfAmplitudeSpectrum+1;
////  
////  /*Print the filtered amplitude spectrum*/
////  printf("Filtered: ");
////  for(int i=0;i<dim_i;i++) {
//// //     printf("%u ",output[i]);
////    }
////  printf("\n");
////  
////  /*Start to identify the words*/
////  uint16_t state = 0;
////  uint16_t wordStart,wordEnd;
////  uint16_t wordIndex = 0;
////  for(int i=0;i<dim_i;i++) {
////    if(output[i]>=tolerance) {
////      if(state==0) {
////        
////        /*Word starts here*/
////        printf("Word starts at index %u \n",i);
////        wordStart=i;
////        wordIndex++;
////      }
////
////      state = 1;
////    }
////    else {
////      if(state==1) {
////        
////        /*Word ends here*/
////        wordEnd=i;
////        printf("Word ends at index %u \n",i);
////        wordIndex++;
////        
////        /*A word is now complete.
////        Calculate the power spectrum for the found word*/
////        calculatePowerSpectrum(&soundIn[wordStart*BUFFER_SIZE],(wordEnd-wordStart)*BUFFER_SIZE);
////      }
////      
////      state = 0;
////      
////    }
////  } 
////}
//
//
///*Calculate the power spectrum of the input. It is split into segments of BUFFER_SIZE*/
//void calculatePowerSpectrum(uint16_t *input, uint16_t inputSize) {
//    
//  /*Check if the input can be splitted into BUFFER_SIZE-segments*/
//  if((inputSize % BUFFER_SIZE)==0) {
//    
//    /*Reset the output buffer (defined globaly atm)*/
//    for(int j=0;j<BUFFER_SIZE/2;j++) {
//        f_output[j] = 0;
//    }
//    
//    /*Do fft for all segment*/
//    for(int i=0;i<inputSize/BUFFER_SIZE;i++) {
//      
//      /*Convert to float*/
//      for(int j=0;j<BUFFER_SIZE;j++) {
//        f_input[j] = (float32_t)(*(input+j+(i*BUFFER_SIZE))-meanOfSoundSignal);
//      }
// 
//      /*Do the fft for one segment*/
//      doFFT(&f_input[0],&f_output_tmp[0], BUFFER_SIZE);
//      
//      /*Sum the output to the total output*/
//      for(int j=0;j<BUFFER_SIZE/2;j++) {
//        f_output[j]=f_output[j]+f_output_tmp[j];
//      }
//
//    }
//    
//    /*Print total output*/
//    printf("FFT-Vector: "); 
//    for(int i=0;i<BUFFER_SIZE/2;i++) {
//      printf("%f ",f_output[i]);
//    }
//    printf("\n");
//    uint16_t index1,index2,index3;
//    returnThreeLargestIndex(&f_output[1],BUFFER_SIZE/2, &index1, &index2, &index3);
//    uint16_t maxindex=floatReturnMaxIndex(&f_output[0],BUFFER_SIZE/2);
//    printf("Max index: %u , %u, %u, %u \n",maxindex,index1,index2,index3);
//    printf("This would equal %u,%u,%u Hz \n\n\n",SAMPLING_RATE*index1/BUFFER_SIZE,SAMPLING_RATE*index2/BUFFER_SIZE,SAMPLING_RATE*index3/BUFFER_SIZE);
//    uint16_t freq_vector[3] = {SAMPLING_RATE*index1/BUFFER_SIZE,SAMPLING_RATE*index2/BUFFER_SIZE,SAMPLING_RATE*index3/BUFFER_SIZE};
//    sort(&freq_vector[0],3);
//    for(int i=0;i<3;i++) {
//      printf("%u ",freq_vector[i]);
//    }
//    printf("\n");
//    
//    uint16_t outLength;
//    char* output = decoder2(&freq_vector[0], &outLength);
//    wordState(output,outLength);
//    for(int i=0;i<outLength;i++) {
//      printf("%c",*(output+i));
//      GLCD_print("%c",*(output+i));
//    }
//    GLCD_print("\n");
//    printf("\n");
//  }
//
//}
///*Init the FFT*/
//void initFFT() {
////  arm_rfft_fast_init_f32(&S, BUFFER_SIZE);
//}
//
///*Do FFT*/
//void doFFT(float32_t *input, float32_t *output, uint16_t fft_size) {
//
//  /*Do the FFT*/
//  //arm_rfft_fast_f32(&S, input,output,0);
//  //arm_cmplx_mag_f32(output, output, fft_size/2);
//
//}
//
///*Moving avereage filter*/
//void filter(uint16_t windowSize,uint16_t *input ,uint16_t* output, uint16_t inputSize) {
//  
//  /*Output moving avereage vector*/
//  uint16_t maStarNow, maStarPrev;
//  
//  /*Make the filtering. Optimized algorithm: http://www.daycounter.com/LabBook/Moving-Average.phtml*/
//  for(int i=0;i<inputSize;i++) {
//    if(i<1) {
//      maStarNow = *(input+i) * windowSize;
//      *(output+i)= maStarNow/windowSize;
//      maStarPrev = maStarNow;
//    }
//    else {
//      maStarNow = maStarPrev + *(input+i)- maStarPrev/windowSize;
//      *(output+i)= maStarNow/windowSize;
//      maStarPrev = maStarNow;
//    }
//  }
//
//}
