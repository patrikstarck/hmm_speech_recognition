//
//  joels.c
//  Test2
//
//  Created by Joel Larsson on 2017-12-06.
//  Copyright © 2017 Joel Larsson. All rights reserved.
//

#include "joels.h"

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

//Init data lexicon
uint8_t number_of_sequences[NUMBER_OF_WORDS] = {2,2};
uint8_t word_sequence_length[NUMBER_OF_WORDS][MAX_SEQ_PER_WORD]={
    {4,4},
    {4,8}
};


uint8_t word_sequences[NUMBER_OF_WORDS][MAX_SEQ_PER_WORD][MAX_SEQUENCES_PER_SEQ] = {
    {{0,1,0,0},{0,1,1,0}},
    {{2,20,0,0},{2,2,2,0,2,2,2,2}}
};

//Init data language model
struct Word commands[NUMBER_OF_COMMANDS];
uint8_t number_of_command_seq[NUMBER_OF_COMMANDS] = {2,2};
uint8_t command_seq_length[NUMBER_OF_COMMANDS][MAX_SEQ_PER_COMMAND] = {
    {2,2},
    {2,2}
};

uint8_t command_sequences[NUMBER_OF_COMMANDS][MAX_SEQ_PER_COMMAND][MAX_SEQUENCES_PER_SEQ] = {
    {{0,1},{1,0}},
    {{0,2},{2,0}}
};

/******END Lexicon data**********/


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


/*******************/
/*Language model functions*/
/*******************/

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
                            *(output+j)=1;
                            enableLed(6);
                        }else if(j==1){
                            //turn off lights
                            *(output+j)=0;
                            disableLed(6);
                        }
                        //erase word sequence buffer
                        for(int t=0;t<seq_length;t++){
                            *(sequence+t) = 0;
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
}
