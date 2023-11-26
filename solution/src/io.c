#include <stdio.h>

enum open_status {
    OPEN_OK = 0,
    OPEN_FAILED
};

enum open_status open_file(FILE** file, const char* filename, const char* mode) {
    *file = fopen(filename, mode);
    if (!*file) return OPEN_FAILED;
    return OPEN_OK;
}

enum close_status {
    CLOSE_OK = 0,
    CLOSE_FAILED
};

enum close_status close_file(FILE* file) {
    if(!file) return CLOSE_FAILED;
    return fclose(file) == 0 ? CLOSE_OK : CLOSE_FAILED;
}
