#include "bmp.h"
#include "errors.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

struct bmp_header header_from_image(const struct image* img) {
	struct bmp_header header = {0};
	header.bfType = HEADER_BF_TYPE;
	header.bfileSize = sizeof (struct bmp_header) + image_get_size_bytes(img) + img->width * img->height * ((4 - ((img->width * sizeof (struct pixel)) % 4)) % 4);
	header.bOffBits = HEADER_OFF_BITS;
	header.biSize = HEADER_BI_SIZE;
	header.bfReserved = HEADER_BF_RESERVED;
	header.biWidth = img->width;
	header.biHeight = img->height;
	header.biPlanes = HEADER_BI_PLANES;
	header.biBitCount = HEADER_BI_BIT_COUNT;
	header.biCompression = HEADER_BI_COMPRESSION;
	header.biSizeImage = header.bfileSize - HEADER_OFF_BITS;
	header.biXPelsPerMeter = HEADER_BI_X_PPM;
	header.biYPelsPerMeter = HEADER_BI_Y_PPM;
	header.biClrUsed = HEADER_CLR_USED;
	header.biClrImportant = HEADER_CLR_IMP;
	return header;
}

bool header_dimensions_valid(struct bmp_header const* header) {
	return header->biHeight > 0 && header->biWidth > 0;
}

bool header_signature_valid(struct bmp_header const* header) {
	return header->bfType == HEADER_BF_TYPE;
}

enum error_type read_pixels (FILE* in, struct bmp_header const* header, struct image* img) {
	struct pixel pixel = {0};
	if(!header_dimensions_valid(header))
		return ERROR_READ_BMP;
	*img = image_create(header->biWidth, header->biHeight);
	if (fseek(in, header->bOffBits, SEEK_SET))
		return ERROR_READ_BMP;
	for (uint32_t i = 0; i < img->height; i++) {
		for (uint32_t j = 0; j < img->width; j++) {
			if (fread(&pixel, sizeof (struct pixel), 1, in) != 1) {
				image_destroy(img);
				return ERROR_READ_BMP;
			}
			image_set_pixel(img, pixel, j, i);
		}
		if (fseek(in, (long) ((4 - ((img->width * sizeof (struct pixel)) % 4)) % 4), SEEK_CUR))
			return ERROR_READ_BMP;
	}
	return OK;
}

enum error_type write_pixels (FILE* out, struct image const* img) {
	struct pixel pixel;
	for (uint32_t i = 0; i < img->height; i++){
		for (uint32_t j = 0; j < img->width; j++) {
			pixel = image_get_pixel(img, j, i);
			if (fwrite(&pixel, sizeof (struct pixel), 1, out) != 1)
				return ERROR_WRITE_BMP;
		}
		size_t zero = 0;
		if(fwrite(&zero, (4 - ((img->width * sizeof (struct pixel)) % 4)) % 4, 1, out) != 1)
			return ERROR_WRITE_BMP;
	}
	return OK;
}

enum error_type read_bmp(FILE* in, struct image* img) {
	struct bmp_header header = {0};
	if(!in || !img)
		return ERROR_READ_BMP;
	if (fread(&header, sizeof(struct bmp_header), 1, in) != 1)
		return ERROR_READ_BMP;
	if (!header_signature_valid(&header))
		return ERROR_READ_BMP;
	if (!header_dimensions_valid(&header))
		return ERROR_READ_BMP;
	return read_pixels(in, &header, img);
}

enum error_type write_bmp(FILE* out, struct image const* img) {
	struct bmp_header header;
	if(!out || !img)
		return ERROR_WRITE_BMP;
	header = header_from_image(img);
	if (fwrite(&header, sizeof (struct bmp_header), 1, out) != 1)
		return ERROR_WRITE_BMP;
	return write_pixels(out, img);
}


