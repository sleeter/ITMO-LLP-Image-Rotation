#include "structures.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTES_PER_PIXEL 3
#define BMP_SIGNATURE_1 0x4d42
#define BMP_SIGNATURE_2 0x4349
#define BMP_SIGNATURE_3 0x5450
#define BIT_COUNT 24
#define BMP_SIZE_1 40
#define BMP_SIZE_2 108
#define BMP_SIZE_3 124
#define OFFSET_BITS 14
#define PLANES 1
#define RESERVED 0


#pragma pack(push, 1)
struct bmp_header
{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)


/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIZE,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_OTHER_FIELDS,
    READ_INVALID_HEADER
};

enum read_status from_bmp( FILE* in, struct image* img ) {
    struct bmp_header bmp_h;
    size_t res = fread(&bmp_h, sizeof(struct bmp_header), 1, in);
    if( res < 1) return READ_INVALID_SIZE;
    if(bmp_h.bfType != BMP_SIGNATURE_1 && bmp_h.bfType != BMP_SIGNATURE_2 && bmp_h.bfType != BMP_SIGNATURE_3) return READ_INVALID_SIGNATURE;
    if(bmp_h.biBitCount != BIT_COUNT) return READ_INVALID_BITS;
    if(bmp_h.bfReserved != RESERVED || bmp_h.biPlanes != PLANES ||
       (bmp_h.biSize != BMP_SIZE_1 && bmp_h.biSize != BMP_SIZE_2 && bmp_h.biSize != BMP_SIZE_3) ||
       bmp_h.bOffBits != bmp_h.biSize + OFFSET_BITS) return READ_INVALID_OTHER_FIELDS;
    img->height = bmp_h.biHeight;
    img->width = bmp_h.biWidth;
    img->data = (struct pixel*) malloc(sizeof(struct pixel) * img->width * img->height);

    for (uint64_t y = 0; y < img->height; y++) {
        for (uint64_t x = 0; x < img->width; x++) {
            struct pixel* pixel = &img->data[y * img->width + x];
            fread(pixel, 1, sizeof(struct pixel), in);
        }

        fseek(in, (long)(4 - ((img->width * BYTES_PER_PIXEL) % 4)), SEEK_CUR);
    }

    return READ_OK;
}

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum write_status to_bmp( FILE* out, struct image const* img ) {
    struct bmp_header bmp_h = {
            .bfType = BMP_SIGNATURE_1,
            .bfReserved = 0,
            .bOffBits = OFFSET_BITS + BMP_SIZE_1,
            .biSize = BMP_SIZE_1,
            .biWidth = img->width,
            .biHeight = img->height,
            .biPlanes = PLANES,
            .biBitCount = BIT_COUNT,
            .biCompression = 0,
            .biSizeImage = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrImportant = 0,
            .biClrUsed = 0,
            .bfileSize = (sizeof(struct bmp_header) + img->width * img->height)
    };

    fwrite(&bmp_h, sizeof(struct bmp_header), 1, out);


    size_t padding_cnt = (4 - (img->width * BYTES_PER_PIXEL) % 4) % 4;
    for (uint64_t y = 0; y < img->height; ++y) {
        for (uint64_t x = 0; x < img->width; ++x) {
            struct pixel const* pixel = &img->data[y * img->width + x];
            fwrite(pixel, sizeof(struct pixel), 1, out);
        }

        struct pixel padding = { .r = 0, .g = 0, .b = 0};
        fwrite(&padding, 1, padding_cnt, out);
    }



    return WRITE_OK;
}
