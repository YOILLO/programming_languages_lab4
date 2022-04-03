#ifndef BMP_H
#define BMP_H

#include "errors.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

#define HEADER_BF_TYPE 0x4D42
#define HEADER_OFF_BITS 54
#define HEADER_BI_SIZE 40
#define HEADER_BI_PLANES 1
#define HEADER_BI_BIT_COUNT 24
#define HEADER_BI_X_PPM 2834
#define HEADER_BI_Y_PPM 2834
#define HEADER_CLR_USED 0
#define HEADER_CLR_IMP 0
#define HEADER_BF_RESERVED 0
#define HEADER_BI_COMPRESSION 0

struct __attribute__((packed)) bmp_header {
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

enum error_type read_bmp(FILE* in, struct image* img);

enum error_type write_bmp(FILE* out, struct image const* img);

#endif
