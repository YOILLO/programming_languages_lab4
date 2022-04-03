#include "image.h"
#include "transformer.h"
#include <stdlib.h>

struct image rotate(const struct image source) {
	struct image target = image_create(source.height, source.width);
	if (target.data == NULL)
		return target;
	for(size_t i = 0; i < source.height; i++)
		for(size_t j = 0; j < source.width; j++) {
			image_set_pixel(&target, image_get_pixel(&source, j, source.height - i - 1), i, j);
		}
	return target;
}

