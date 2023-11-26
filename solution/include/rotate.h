#ifndef IMAGE_TRANSFORMER_ROTATE_H
#define IMAGE_TRANSFORMER_ROTATE_H
#include "structures.h"
#include <stdint.h>
#pragma once

struct image rotate( struct image const source );

enum angle_status {
    VALID = 0,
    NOT_VALID
};

enum angle_status valid_angle(const int16_t* angles, size_t angles_size, int16_t angle);

size_t rotate_count(int16_t angle);

#endif //IMAGE_TRANSFORMER_ROTATE_H
