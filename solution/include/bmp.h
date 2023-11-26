#ifndef IMAGE_TRANSFORMER_BMP_H
#define IMAGE_TRANSFORMER_BMP_H
#include "structures.h"
#include <stdio.h>
#pragma once

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIZE,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_OTHER_FIELDS,
    READ_INVALID_HEADER
};

enum read_status from_bmp( FILE* in, struct image* img );

enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum write_status to_bmp( FILE* out, struct image const* img );

#endif //IMAGE_TRANSFORMER_BMP_H
