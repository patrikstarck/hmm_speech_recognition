#include "includes.h"
#ifndef __DECODER_H
#define __DECODER_H

char* decoder2(uint16_t* freq_vector, uint16_t *outLength);
char* decoder(uint16_t freq, uint16_t *outLength);
extern char wordVect[20];

uint16_t stringCompare(char *string1,char *string2, uint16_t length);

void wordState(char *charArray, uint16_t length);
extern int state;

#endif