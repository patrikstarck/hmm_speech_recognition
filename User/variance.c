// Calculate the variance

uint16_t returnTol(uint16_t *in,uint16_t inLength) {
  uint16_t tolerance = 0;
  uint16_t x   = 0;
  uint16_t x_2 = 0;
  for(int i=1;i<inLength;i++) {
  	x_2 = x_2 + (*(in+i))*(*(in+i));
  	x   = x   + *(in+i);
  }
  tolerance = sqrt((x_2 - (x*x/inLength))/inLength)/3;
  return tolerance;
}