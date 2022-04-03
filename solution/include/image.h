#ifndef IMAGE_H
#define IMAGE_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

struct image {
	size_t width, height;
	struct pixel *data;
};

struct pixel {
	uint8_t b, g, r;
};

struct image image_create(size_t width, size_t height);

void image_destroy(struct image *img);

bool image_set_pixel(struct image *img, struct pixel const p, size_t x, size_t y);

struct pixel image_get_pixel(struct image const* img, size_t x, size_t y);

size_t image_get_size_bytes(struct image const* img);

#endif

