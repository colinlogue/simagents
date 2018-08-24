#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

uint8_t bstrtoi(char *bstr) {
  // must be 8-bit binary string
  assert(strlen(bstr)==8);

  // start with 0
  uint8_t val = 0;

  // iterate over string from most to least significant bit
  int k = 7;
  uint8_t bit_val;
  for (int i = 0; i < 8; i++) {
    assert(bstr[i] == '0' || bstr[i] == '1');
    bit_val = atoi(bstr[i]) << (k-i);
    val += bit_val;
  }    
};
