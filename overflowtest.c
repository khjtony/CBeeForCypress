#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
  uint8_t LOL;
  LOL=0xbb;
  LOL=LOL+LOL;
  printf("%#x\n",LOL);
}