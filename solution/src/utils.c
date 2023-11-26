#include "structures.h"
#include <stdlib.h>
void free_image(struct image* source) {
    free(source->data);
    source->width = 0;
    source->height = 0;
}
