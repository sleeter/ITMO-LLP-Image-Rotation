/* создаёт копию изображения, которая повёрнута на 90 градусов */
#include "structures.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
struct image rotate( struct image const source ) {
    struct image rotate_image = { .height = source.width, .width = source.height, .data = (struct pixel*) malloc(sizeof(struct pixel) * source.height * source.width )};
    for (uint64_t j = rotate_image.width; j != 0; j--) {
        for (uint64_t i = 1; i <= rotate_image.height; i++) {
            rotate_image.data[(i-1) * rotate_image.width + (j-1)] = source.data[(source.height-j) * source.width + (i-1)];
//            *(rotate_image.data + (i-1) * rotate_image.width + (j-1)) = *(source.data + (source.height-j) * source.width + (i-1));
        }
    }
    return rotate_image;
}
enum angle_status {
    VALID = 0,
    NOT_VALID
};
enum angle_status valid_angle(const int16_t* angles, const size_t angles_size, int16_t angle) {
    if(angle < 0) angle += 360;
    for(size_t i = 0; i < angles_size; i++)
        if(angles[i] == angle) return VALID;
    return NOT_VALID;
}

size_t rotate_count(int16_t angle) {
    angle = (int16_t)-angle;
    if(angle < 0) angle += 360;
    return angle / 90;
}
