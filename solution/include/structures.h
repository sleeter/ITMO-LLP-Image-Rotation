#ifndef IMAGE_TRANSFORMER_STRUCTURES_H
#define IMAGE_TRANSFORMER_STRUCTURES_H
#include <stdint.h>
#pragma once

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

#endif //IMAGE_TRANSFORMER_STRUCTURES_H
