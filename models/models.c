#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../simulation.h"
#include "models.h"

sim_t get_sim_from_str(char *label) {
  if (strcmp(label, "test")==0) return simtest;
  fprintf(stderr, "\'%s\' argument does not match any model", label);
  exit(EXIT_FAILURE);
};
