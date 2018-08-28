#include <stdint.h>

// Dictionary type that holds up to 256 items and uses a simple hash function
// to locate keys. Keys CANNOT be deleted. Values are void pointers.


static const uint8_t DICT_SIZE = 256;

typedef struct {
	char *key;
	void *value;
}

typedef struct {

} shortdict_t;

shortdict_t *build_shortdict(char **keys, )