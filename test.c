#include "utils/quickdict.h"

int main() {
  printf("Building quickdict...\n");
  quickdict_t *qd = qd_build();
  printf("qd located at: %p\n", qd);
  char *SECRET_MSG = "This is a secret!";
  qd_add_entry(qd, "SECRET_MSG", SECRET_MSG, sizeof(SECRET_MSG));
  uint8_t idx = qd_lookup(qd, "SECRET_MSG");
  printf("Hash of SECRET_MSG: %u\n", qd_hash("SECRET_MSG"));
  printf("Lookup index: %u\n", idx);
  char *val = (char*)(qd->entries[idx]->value);
  printf("Location of message: %p\n", SECRET_MSG);
  printf("Location of value: %p\n", qd->entries[idx]->value);
  printf("The secret message is: %s\n", val);
}