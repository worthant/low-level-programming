#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/**
 * Represents a dynamic array (vector) of int64_t elements.
 *
 * Members:
 *   - data: Pointer to the dynamically allocated array of int64_t.
 *   - size: The number of elements currently in the vector.
 *   - capacity: The total number of elements the vector can currently hold.
 */
struct Vector {
    int64_t* data;
    size_t size;
    size_t capacity;
};


/**
 * Creates a new vector with a specified initial capacity.
 *
 * Allocates memory for the vector structure and its internal data array. Sets the initial size
 * of the vector to 0 and initializes its capacity to the specified value.
 *
 * @param initial_capacity The initial capacity of the vector.
 * @return A pointer to the newly created vector, or NULL if memory allocation fails.
 */
Vector* vector_create(size_t initial_capacity) {
    Vector* vector = malloc(sizeof(Vector));
    if (!vector) return NULL;

    vector->data = malloc(sizeof(int64_t) * initial_capacity);
    if (!vector->data) {
        free(vector);
        return NULL;
    }

    vector->size = 0;
    vector->capacity = initial_capacity;
    return vector;
}


/**
 * Destroys the vector, freeing its memory.
 *
 * Frees the memory allocated for the vector's internal data array and then the vector itself.
 *
 * @param vector A pointer to the vector to be destroyed.
 */
void vector_destroy(Vector* vector) {
    free(vector->data);
    free(vector);
}


/**
 * Sets the value at a specified index in the vector.
 *
 * If the index is within the bounds of the vector's current size, updates the value at the
 * specified index.
 *
 * @param vector A pointer to the vector.
 * @param index The index at which to set the value.
 * @param value The value to set at the specified index.
 * @return True if the index is valid and the value is set, false otherwise.
 */
bool vector_set(Vector* vector, size_t index, int64_t value) {
    if (index >= vector->size) return false;
    vector->data[index] = value;
    return true;
}


/**
 * Retrieves the value from a specified index in the vector.
 *
 * If the index is within the bounds of the vector's current size, retrieves the value at the
 * specified index.
 *
 * @param vector A pointer to the vector.
 * @param index The index from which to get the value.
 * @param value A pointer to store the retrieved value.
 * @return True if the index is valid and the value is retrieved, false otherwise.
 */
bool vector_get(const Vector* vector, size_t index, int64_t* value) {
    if (index >= vector->size) return false;
    *value = vector->data[index];
    return true;
}


/**
 * Returns the current size of the vector.
 *
 * @param vector A pointer to the vector.
 * @return The number of elements currently in the vector.
 */
size_t vector_size(const Vector* vector) {
    return vector->size;
}


/**
 * Returns the current capacity of the vector.
 *
 * @param vector A pointer to the vector.
 * @return The total number of elements the vector can currently hold.
 */
size_t vector_capacity(const Vector* vector) {
    return vector->capacity;
}


/**
 * Expands the vector's capacity if needed.
 *
 * If the vector's size has reached its capacity, doubles the capacity. Allocates new memory
 * for the expanded data array and copies existing elements to the new array.
 *
 * @param vector A pointer to the vector.
 * @return True if expansion is successful or not needed, false if memory allocation fails.
 */
static bool vector_expand_if_needed(Vector* vector) {
    if (vector->size < vector->capacity) return true;

    size_t new_capacity = vector->capacity * 2;
    int64_t* new_data = realloc(vector->data, sizeof(int64_t) * new_capacity);
    if (!new_data) return false;

    vector->data = new_data;
    vector->capacity = new_capacity;
    return true;
}


/**
 * Adds a new value to the end of the vector.
 *
 * Expands the vector's capacity if necessary. Increments the vector's size after adding the value.
 *
 * @param vector A pointer to the vector.
 * @param value The value to be added.
 * @return True if the value is successfully added, false otherwise.
 */
bool vector_push_back(Vector* vector, int64_t value) {
    if (!vector_expand_if_needed(vector)) return false;

    vector->data[vector->size++] = value;
    return true;
}


/**
 * Resizes the vector to a new size.
 *
 * If the new size is greater than the current capacity, reallocates memory to expand the capacity.
 * Updates the size of the vector to the new size.
 *
 * @param vector A pointer to the vector.
 * @param new_size The new size for the vector.
 * @return True if resizing is successful, false if memory allocation fails.
 */
bool vector_resize(Vector* vector, size_t new_size) {
    if (new_size > vector->capacity) {
        size_t new_capacity = new_size;
        int64_t* new_data = realloc(vector->data, sizeof(int64_t) * new_capacity);
        if (!new_data) return false;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    vector->size = new_size;
    return true;
}


/**
 * Prints the elements of the vector to a specified file stream.
 *
 * Iterates over the elements of the vector and prints each value.
 *
 * @param vector A pointer to the vector.
 * @param stream The file stream to print the vector elements to (e.g., stdout).
 */
void vector_print(const Vector* vector, FILE* stream) {
    for (size_t i = 0; i < vector->size; i++) {
        fprintf(stream, "%" PRId64 " ", vector->data[i]);
    }
    fprintf(stream, "\n");
}
