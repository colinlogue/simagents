#include <stdlib.h> // rand, malloc
#include <stdio.h> // size_t
#include <assert.h> // assert
#include <string.h> // memcpy

int randRange(int start, int end) {
  /** Returns a random number in the range (start, end] **/
  int len = end - start;
  assert(len > 0); // end must be greater than start
  return rand() % len;
};

void shuffleArray(void *array_ptr, int array_len, size_t item_size) {
  int current_idx = array_len - 1;
  void *current_ptr, *swap_ptr;
  int swap_idx;
  void *copy_buffer = malloc(item_size);
  
  while (current_idx > 0) {
    
    // copy value of current index to copy_buffer
    current_ptr = array_ptr + (item_size * current_idx);
    memcpy(copy_buffer, current_ptr, item_size);

    // copy value of random earlier value in array to current index
    swap_idx = randRange(0, current_idx);
    swap_ptr = array_ptr + (item_size * swap_idx);
    memcpy(current_ptr, swap_ptr, item_size);

    // copy saved value of current index to swap index
    memcpy(swap_ptr, copy_buffer, item_size);

    current_idx--;

  }
  
};

