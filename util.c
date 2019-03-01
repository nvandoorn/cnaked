#include "util.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print(char *formatter) {
  char f = strcat(formatter, "\n");
  va_list ap;
  va_start(ap, formatter);
  printf(f, );
}
