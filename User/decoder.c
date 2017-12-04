#include "includes.h"

char wordVect[20];

/*A decoder that decodes a single "word"*/
char* decoder2(uint16_t* freq_vector, uint16_t *outLength) {
  
    
  if((freq_vector[0]<=570 && freq_vector[0]>=430) && (freq_vector[1]<=830 && freq_vector[1]>=680) &&(freq_vector[2]<=1570 && freq_vector[2]>=1430)) {
    wordVect[0] = 'l';
    wordVect[1] = 'i';
    wordVect[2] = 'g';
    wordVect[3] = 'h';
    wordVect[4] = 't';
    wordVect[5] = 's';
    *outLength = 6;
  }
  
  if((freq_vector[0]<=570 && freq_vector[0]>=430) && (freq_vector[1]<=2070 && freq_vector[1]>=1930) &&(freq_vector[2]<=2570 && freq_vector[2]>=2430)) {
    wordVect[0] = 'o';
    wordVect[1] = 'n';
    *outLength = 2;
  }
  
  if((freq_vector[0]<=1570 && freq_vector[0]>=1430) && (freq_vector[1]<=2070 && freq_vector[1]>=1930) &&(freq_vector[2]<=2570 && freq_vector[2]>=2430)) {
    wordVect[0] = 'o';
    wordVect[1] = 'f';
    wordVect[2] = 'f';
    *outLength = 3;
  }
  
  if((freq_vector[0]<=830 && freq_vector[0]>=680) && (freq_vector[1]<=1570 && freq_vector[1]>=1430) &&(freq_vector[2]<=2570 && freq_vector[2]>=2430)) {
    wordVect[0] = 'k';
    wordVect[1] = 'i';
    wordVect[2] = 't';
    wordVect[3] = 'c';
    wordVect[4] = 'h';
    wordVect[5] = 'e';
    wordVect[6] = 'n';
    *outLength = 7;
  }
  
  if((freq_vector[0]<=560 && freq_vector[0]>=430) && (freq_vector[1]<=1570 && freq_vector[1]>=1430) &&(freq_vector[2]<=2570 && freq_vector[2]>=2430)) {
    wordVect[0] = 'l';
    wordVect[1] = 'i';
    wordVect[2] = 'v';
    wordVect[3] = 'i';
    wordVect[4] = 'n';
    wordVect[5] = 'g';
    wordVect[6] = 'r';
    wordVect[7] = 'o';
    wordVect[8] = 'o';
    wordVect[9] = 'm';
    *outLength = 10;
  }
  
  return &wordVect[0];
}



/*String for comparisons between two strings*/
uint16_t stringCompare(char *string1,char *string2, uint16_t length) {
  uint16_t equal = 0;
  for(int i=0;i<length;i++) {
    if( *(string1+i) != *(string2+i)) {
      equal = 1;
    }
  }
  return equal;
}

/*State machine that keeps tracks of the word state*/
int state;
void wordState(char *charArray, uint16_t length){

    if(stringCompare(charArray,"lights",length)==0){
        state = 1;
    }else if(stringCompare(charArray,"on",length)==0 &&state==1){
        state =2;
    }else if(stringCompare(charArray,"off",length)==0&&state==1){
        state = 3;
    }else if(stringCompare(charArray,"kitchen",length)==0&&state == 2){
        state = 0;
        //turn on light
        enableLed(6);
    }else if(stringCompare(charArray,"kitchen",length)==0&&state == 3){
        state = 0;
        //turn off light
        disableLed(6);
    }else if(stringCompare(charArray,"livingroom",length)==0&&state ==2){
        state = 0;
        //turn on light
        enableLed(7);
    }else if(stringCompare(charArray,"livingroom",length)==0&&state ==3){
        state = 0;
        //turn off light
        disableLed(7);
    }else if(stringCompare(charArray,"bathroom",length)==0&&state ==2){
        state = 0;
        enableLed(8);
        //turn on light
    }else if(stringCompare(charArray,"bathroom",length)==0&&state ==3){
        state = 0;
        //turn off light    
        disableLed(8);
    }else{
        state = 0;
        //start over;
    }
}