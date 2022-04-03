#include "bmp.h"
#include "errors.h"
#include "file.h"
#include "image.h"
#include "transformer.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv ) {
	FILE *in;
	FILE *out;
	struct image in_img = {0};
	struct image out_img;

	if (argc != 3){
		print_error(ERROR_BAD_ARGS);
		return 1;
	}
	if(check_error(open_f(&in, argv[1], "rb")))
		return 2;
	if(check_error(open_f(&out, argv[2], "wb"))){
		close_f(in);
		return 3;
	}
	if (check_error(read_bmp(in, &in_img))){
		close_f(in);
		close_f(out);
		return 4;
	}

	out_img = rotate(in_img);
	
	image_destroy(&in_img);

	if (check_error(write_bmp(out, &out_img))){
		image_destroy(&out_img);
		close_f(in);
		close_f(out);
		return 5;		
	}
	
	image_destroy(&out_img);

		
	if (check_error(close_f(in))){
		close_f(out);
		return 6;
	}
	
	if (check_error(close_f(out)))
		return 7;

	return 0;
}
