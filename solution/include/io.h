#ifndef IMAGE_TRANSFORMER_IO_H
#define IMAGE_TRANSFORMER_IO_H
#include <stdio.h>
#pragma once

enum open_status {
    OPEN_OK = 0,
    OPEN_FAILED
};

enum open_status open_file(FILE** file, const char* filename, const char* mode);

enum close_status {
    CLOSE_OK = 0,
    CLOSE_FAILED
};

enum close_status close_file(FILE* file);

#endif //IMAGE_TRANSFORMER_IO_H
