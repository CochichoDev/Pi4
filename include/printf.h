#pragma once

#include <stdarg.h>
#include <stdint.h>

int printf(const char *__restrict ctrl1, ...);
int vprintf(const char *ctrl1, va_list argp);
int puts(const char *__restrict ctrl1);

