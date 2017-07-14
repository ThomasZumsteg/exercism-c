#ifndef ALL_YOUR_BASE_H
#define ALL_YOUR_BASE_H

#define DIGITS_ARRAY_SIZE 64
#include <stdint.h>
#include <stddef.h>

size_t rebase(int8_t *digits, int8_t from_base, int8_t to_base, size_t len);

#endif
