#include "image.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>


struct image image_create (size_t width, size_t height) {
	struct image img = {0};
	img.width = width;
	img.height = height;
	img.data = malloc (width * height * sizeof (struct pixel));
	return img;
}

static bool image_check_coords(struct image const* img, size_t x, size_t y) {
	return x >= 0 && x <= img->width && y >= 0 && y <= img->height;
}

bool image_set_pixel(struct image *img, struct pixel const p, size_t x, size_t y) {
	if(!image_check_coords(img, x, y))
		return false;
	*(img->data + y * img->width + x) = p;
	return true;
}

size_t image_get_size_bytes(struct image const* img) {
	return img->width * img->height * sizeof(struct pixel);
}

struct pixel image_get_pixel(struct image const* img, size_t x, size_t y) {
	return *(img->data + y * img->width + x);
}

void image_destroy(struct image *img) {
	free(img->data);
}

