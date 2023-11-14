#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Vector Vector;

Vector* vector_create(size_t initial_capacity);
void vector_destroy(Vector* vector);

bool vector_set(Vector* vector, size_t index, int64_t value);
bool vector_get(const Vector* vector, size_t index, int64_t* value);
size_t vector_size(const Vector* vector);
size_t vector_capacity(const Vector* vector);

bool vector_push_back(Vector* vector, int64_t value);
bool vector_resize(Vector* vector, size_t new_size);

void vector_print(const Vector* vector, FILE* stream);

#endif
