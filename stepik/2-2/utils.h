#ifndef UTILS_H
#define UTILS_H

#include <inttypes.h>
#include <stdio.h>

int64_t read_int64();

size_t read_size();

void print_newline();

int64_t *array_int_min(int64_t *array, size_t size);

void array_int_print(int64_t *arr, size_t size);

void array_int_fill(int64_t *arr, size_t size);

int64_t **marray_read(size_t *rows, size_t *sizes[]);

void marray_print(int64_t **marray, size_t *sizes, size_t rows);

void marray_free(int64_t **marray, size_t rows);

#endif
