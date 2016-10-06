#include <stdio.h>


void encode_byte(unsigned char bval) {
  unsigned char bit = 0;
  unsigned int i;

  for (i=0; i<8; i++) {
    bit = (bval & (1 << 7)) >> 7;
    bval = bval << 1;

    if (bit == 0) {
      fputc(0xff, stdout);
      fputc(0x00, stdout);
    }
    else {
      fputc(0xff, stdout);
      fputc(0xff, stdout);
      fputc(0x00, stdout);
      fputc(0x00, stdout);
    }
  }

}


int main() {
  int nextc;

  while (1) {
    nextc = fgetc(stdin);
    if (nextc == EOF) {
      break;
    }
    encode_byte(nextc);
  }

  return 0;
}
