#ifndef ERRORS_H
#define ERRORS_H

#include <stdbool.h>
#include <stdlib.h>

enum error_type {
	OK,
	ERROR_OPEN_FILE,
	ERROR_CLOSE_FILE,
	ERROR_READ_BMP,
	ERROR_WRITE_BMP,
	ERROR_BAD_ARGS
};

bool check_error(enum error_type error);
void print_error(enum error_type error);

#endif

