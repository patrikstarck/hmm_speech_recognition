//
//  joels.h
//  Test2
//
//  Created by Joel Larsson on 2017-12-06.
//  Copyright © 2017 Joel Larsson. All rights reserved.
//

#ifndef joels_h
#define joels_h

#include <stdio.h>

/*Defines*/
#define NUMBER_OF_WORDS 2
#define NUMBER_OF_COMMANDS 2
#define MAX_SEQ_PER_COMMAND 20
#define MAX_SEQ_PER_WORD 20
#define MAX_SEQUENCES_PER_SEQ 20
#define MATH_PI 3.141592653589793
#define NUMBER_OF_STATES 11
#define A_SIZE 121
#define NUMBER_OF_MFCC 13
#define PATH_LENGTH 5
#define TRANS_PATH_LENGTH 10
#define FRAME_LENGTH 256
#define VEC_LENGTH 9000

/*Lexicon*/
void initLexicon(void) ;
void sequenceConverter(uint8_t* outSequence, uint8_t* inSequence, uint8_t length);
void searchPattern(uint8_t* output, uint8_t* sequence,uint8_t length);
void searchCommando(uint8_t* output, uint8_t* sequence,uint8_t seq_length);
void initLanguageModel(void);


#endif /* joels_h */
