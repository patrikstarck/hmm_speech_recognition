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
uint8_t number_of_sequences[NUMBER_OF_WORDS] = {16,11,11};
uint8_t word_sequence_length[NUMBER_OF_WORDS][MAX_SEQ_PER_WORD]={
  {4,5,6,6,6,5,6,5,4,5,5,6,6,4,5,4,6,6,6},
  {5,5,4,3,5,4,5,4,3,5,4},
  {5,7,5,6,6,5,4,4,5,6,3}
};

uint8_t word_sequences[NUMBER_OF_WORDS][MAX_SEQ_PER_WORD][MAX_SEQUENCES_PER_SEQ] = {
    /*Lampa*/
    {{0,4,1,3},{1,2,4,1,4},{1,2,4,1,3,4},{0,2,4,1,3,4},{0,2,4,1,3,4},{1,2,4,1,4},{0,1,2,3,4,1},{0,1,2,4,1},{1,2,4,1},{0,1,7,8,1},{1,2,7,4,1},{1,2,7,2,4,1},{1,2,7,2,5,1},{0,1,2,0},{1,2,4,5,1},{0,1,7,1},{0,1,2,6,8,1},{0,1,2,10,4,1},{0,1,2,4,2,1}}
    /*Tänd*/
    {{5,6,0,7,8},{5,6,0,7,0},{5,6,0,7},{6,7,0},{5,6,0,6,7},{5,6,1,7},{5,6,1,7,8},{5,6,7,8},{5,6,7},{5,6,3,7,8},{5,6,0,8}},
    /*Släck*/
    {{9,0,6,4,10},{9,5,7,0,6,4,10},{9,7,6,4,10},{9,0,6,2,4,10},{9,10,0,6,4,10},{9,0,6,5,10},{0,6,4,10},{8,6,4,10},{8,6,5,4,10},{9,0,6,0,4,10},{9,0,6}}
 };

/*//Init data language model
struct Word commands[NUMBER_OF_COMMANDS];
uint8_t number_of_command_seq[NUMBER_OF_COMMANDS] = {2,2};
uint8_t command_seq_length[NUMBER_OF_COMMANDS][MAX_SEQ_PER_COMMAND] = {
    {2,2},
    {2,2}
};

uint8_t command_sequences[NUMBER_OF_COMMANDS][MAX_SEQ_PER_COMMAND][MAX_SEQUENCES_PER_SEQ] = {
    {{0,1},{1,0}},
    {{0,2},{2,0}}
};*/

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

//simple FIR-filter for pre-emphasise voice signals
void preEmphasis(float32_t *in_vec,int length_in_vec,float32_t *out_vec){
    float32_t b = -0.97;
    *out_vec = *in_vec;
    for(int i=1;i<length_in_vec;i++){
        *(out_vec+i)=*(in_vec+i) + *(in_vec+i-1)*b;
    }
}


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
              for (int n = 0; n<length;n++) {
                  *(sequence+n)=4;
              }
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

/*******************/
/*Language model functions*/
/*******************/
/*
void initLanguageModel() {
    //Loop through number of words
    for (int j=0;j<NUMBER_OF_COMMANDS;j++) {
        //For each word, loop through number of sequence
        for(int i=0;i<number_of_command_seq[j];i++) {
            //Add the seqences to the struct array
            words[j].pho_seq[i] = &(command_sequences[j][i][0]);
            words[j].length[i]=command_seq_length[j][i];
        }
        commands[j].nSeq=number_of_command_seq[j];
    }
}

void languageBuffer(uint8_t* lang_buff, uint8_t* input,uint8_t output_length, uint8_t input_length){
    for(i=0;i<input_length;i++){
        if(*(input+i)!=100){
            for(k=0;k<output_length;k++){
                if(*(output+k)==100){
                    *(lang_buff+k)=*(input+i);
                }
            }
        }
    }
        
}

void searchCommando(uint8_t* output, uint8_t* sequence,uint8_t seq_length) {
    
    //Loop through all commands
    for (int j=0;j<NUMBER_OF_COMMANDS;j++) {
        *(output+j) = 100;
        //Loop through all sequences for each command
        for(int i=0;i<commands[j].nSeq;i++) {
            
            //Only find one sequence per command
            if(*(output+j)!= 100) {
                break;
            }
            
            uint8_t compareIndex = 0;
            for (int k=0;k<seq_length;k++) {
                if(*(sequence+k)== *(commands[j].pho_seq[i]+compareIndex)) {
                    compareIndex++;
                    
                    //command found?
                    if(compareIndex==commands[j].length[i]) {
                        //things happen
                        //if more commands are added, add another if-statement
                        if(j==0){
                            //turn on lights
                            //*(output+j)=1;
                            enableLed(6);
                        }else if(j==1){
                            //turn off lights
                            //*(output+j)=0;
                            disableLed(6);
                        }
                        //erase word sequence buffer
                        for(int t=(k-compareIndex);t<compareIndex;t++){
                            *(sequence+t) = 100;
                        }
                        break;
                    }
                }
                else {
                    compareIndex = 0;
                    if(*(sequence+k)== *(commands[j].pho_seq[i]+compareIndex)) {
                        compareIndex++;
                    }
                }
            }
        }
    }
}*/

/*******************/
/*End language model functions*/
/*******************/

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
		*ind = 0;
		*max = C->pData[col];
		for(int i = 1;i<C->numRows;i++) {
			maxvalue = C->pData[i*(C->numCols)+col];
			if(maxvalue>*max && maxvalue != -1000000000) {
				*max = maxvalue;
				*ind = i;
			}
		}
}

void MatVecMax(arm_matrix_instance_f32 *C,float32_t *max,uint16_t *ind) {
		// This function finds the maximum value in a arm matrix row vector
		float32_t maxvalue;
		*ind = 0;
		*max = C->pData[0];
		for(int i = 1;i<C->numCols ;i++) {
			maxvalue = C->pData[i];
			if(maxvalue>*max && maxvalue != -1000000000) {
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
                          if(A->pData[k*n_states+i] == 0){// || logV->pData[k] == 0) {
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
				if (A_plus_logV.pData[k+i*n_states] == -1000000000) {
					C_mat.pData[k*n_states+i] = -1000000000;
				}
				else {
					C_mat.pData[k*n_states+i] = A_plus_logV.pData[k+i*n_states]+xn_zn->pData[k];
				}
				//C(k,i) = A_plus_logV(i,k) + p_xn_zn(1,k); Matlab ..
			}
		}

		for(uint8_t i = 0;i<n_states;i++) {
			MatrixMax(&C_mat,i,&max_C,&C_max_ind);
			logV->pData[i] = max_C;
			PATH[i] = C_max_ind;
			//trace_printf("index \n%i\n",C_max_ind);
			//trace_printf("Max_val \n%f\n",max_C);
		}

		MatVecMax(logV,&max_C,&C_max_ind);
		path->pData[path_length-1] = C_max_ind; // Put cmax in in last element
		path->pData[path_length-1]  = PATH[(int)(path->pData[path_length-1])]; // Put PATH(path(end)) in path(end)

		for(int i = 0;i<NUMBER_OF_STATES;i++) {
			if (logV->pData[i] < -100000000) {
				logV->pData[i] = 0;
			}
		}

		max_C = 0;
		for(int i = 0;i<n_states;i++) {
			max_C = max_C + logV->pData[i];
		}

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
	else if (*(trans_path+trans_path_length-1 ) == (uint8_t)(filtered_path->pData[filtered_path_length-1])) {
		// Do nothing
	}	
	else {
		
		for(int i = 0;i<(trans_path_length-1);i++) {
			*(trans_path+i) = *(trans_path+i+1);// Move all elements on step to the right
		}
		*(trans_path+trans_path_length-1 ) = (uint8_t)(filtered_path->pData[filtered_path_length-1]);

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
					*(frame+frame_index) = *(in_vec+i)*32768;//(*(in_vec+i)-2048)*32.7*2.5;
					frame_index++;
				}
			}
			if(odd == 0) {
				frame_nr = (frame_nr/2);
				for(int i = ((frame_nr-1)*frame_length+128);i<((frame_length*frame_nr)+128);i++) {
					*(frame+frame_index) = *(in_vec+i)*32768;//(*(in_vec+i)-2048)*32.7*2.5;
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

float32_t returnMax(float32_t *in,uint8_t inLength) {
	float32_t maxvalue=*in;
  for(int i=1;i<inLength;i++) {
    if(*(in+i)>maxvalue) {
      maxvalue=*(in+i);
    }
  }
  return maxvalue;
}

void preprocessing(float32_t *frame,float32_t *fft_frame,float32_t *window,int frame_size) {

	windower(window,frame,frame_size); // Apply blackman window

	arm_rfft_fast_init_f32(&S_RFFT_1, frame_size);
	arm_rfft_fast_f32(&S_RFFT_1, &frame[0],&fft_frame[0],0);
	arm_cmplx_mag_squared_f32(&fft_frame[0], &fft_frame[0], frame_size/2);
        
    float32_t fm= 10000/returnMax(&fft_frame[0],frame_size/2);
        

	for(int i = 0;i<(frame_size/2+1);i++) {
		*(fft_frame+i) = *(fft_frame+i)*fm;
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
