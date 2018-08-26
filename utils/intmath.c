int power(int root, int exp) {
  int val = 1;
  for (int i = 0; i < exp; i++) {
    val *= root;
  }
  return val;
};

int max(int a, int b) {
  return (a > b) ? a : b;
};

int min(int a, int b) {
  return (a < b) ? a : b;
};