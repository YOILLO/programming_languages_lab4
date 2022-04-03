#ifndef FILE_H
#define FILE_H

#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

enum error_type open_f(FILE **file, char const *name, char const *mode);

enum error_type close_f(FILE *file);

#endif
