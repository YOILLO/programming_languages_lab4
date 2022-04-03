#include "errors.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

enum error_type open_f(FILE **file, char const *name, char const *mode) {
	if (!name)
		return ERROR_OPEN_FILE;
	*file = fopen(name, mode);
	if (*file)
		return OK;
	return ERROR_OPEN_FILE;
}

enum error_type close_f(FILE *file) {
	if (!file)
	        return ERROR_CLOSE_FILE;
	if (!fclose(file))
		return OK;
	return ERROR_CLOSE_FILE;
}

