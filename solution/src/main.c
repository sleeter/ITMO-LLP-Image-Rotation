#include "bmp.h"
#include "io.h"
#include "rotate.h"
#include "structures.h"
#include "utils.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ANGLE_SIZE 4

int print_error(char* str) {
    fprintf(stderr, "%s", str);
    return 1;
}

int main( int argc, char** argv ) {
    if (argc != 4) {
        fprintf(stderr, "Data is not correct, use: %s <source-image> <transformed-image> <angle>.\n", argv[0]);
        return 1;
    }
    int16_t angle = (int16_t) atoi(argv[3]);
    const size_t angle_size = ANGLE_SIZE;
    const int16_t angles[] = {0,90, 180, 270};
    if(valid_angle(angles, angle_size, angle) != VALID) {
        fprintf(stderr, "Angle is not valid, use: {0, 90, 180, 270, -90, -180, -270}.\n");
        return 1;
    }
    FILE * file_1;
    if(open_file(&file_1, argv[1], "rb")!= OPEN_OK) {
        fprintf(stderr, "File %s is not opened.\n", argv[1]);
        return 1;
    }
    struct image image = (struct image) { .height = 0, .width = 0, .data = NULL};
    enum read_status status = from_bmp(file_1, &image);
    if(status != READ_OK) {
        fprintf(stderr, "%u\n", status);
        fprintf(stderr, "BMP is not read.\n");
        return 1;
    }
    if(close_file(file_1)!=CLOSE_OK) {
        fprintf(stderr, "File %s is not closed.\n", argv[1]);
        return 1;
    }
    size_t rotate_cnt = rotate_count(angle);
    fprintf(stderr, "%d - angle, %zu - rotate count", (int32_t)angle, rotate_cnt);
    for(size_t i = 0; i < rotate_cnt; i++) {
        struct image rotate_image_new = rotate(image);
        free_image(&image);
        image = rotate_image_new;
    }
    FILE * file_2;
    if(open_file(&file_2, argv[2], "wb")!= OPEN_OK) {
        fprintf(stderr, "File %s is NOT opened.\n", argv[2]);
        return 1;
    }
    if(to_bmp(file_2, &image) != WRITE_OK) {
        fprintf(stderr, "BMP is not write.\n");
        return 1;
    }
    if(close_file(file_2)!=CLOSE_OK) {
        fprintf(stderr, "File %s is not closed.\n", argv[1]);
        return 1;
    }
    free_image(&image);
    return 0;
}
