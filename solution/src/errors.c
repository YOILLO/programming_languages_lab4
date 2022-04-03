#include "errors.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char* error_messages[] = {
	[ERROR_OPEN_FILE] = "Не открыть фаил",
	[ERROR_CLOSE_FILE] = "Не закрывается фаил",
	[ERROR_READ_BMP] = "В файле не BMP",
	[ERROR_WRITE_BMP] = "Не могу сохранить фаил как BMP",
	[ERROR_BAD_ARGS] = "Аргументы не приняты"
};

bool check_error(enum error_type error) {
	if (error != OK){
		print_error(error);
		return 1;
	}
	return 0;
}

void print_error(enum error_type error) {
	fprintf(stderr, "%s %s", error_messages[error], "\n");
}
