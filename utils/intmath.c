/**
  * Functions for integer math.
**/

extern int power(int root, int exp) {
  int val = 1;
  for (int i = 0; i < exp; i++) {
    val *= root;
  }
  return val;
};

extern int max(int a, int b) {
  return (a > b) ? a : b;
};

extern int min(int a, int b) {
  return (a < b) ? a : b;
};