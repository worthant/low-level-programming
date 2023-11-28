#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int64_t read_int64() {
    int64_t val;
    scanf("%" SCNd64, &val);
    return val;
}

size_t read_size() {
    size_t val;
    scanf("%zu", &val);
    return val;
}

void print_newline() {
    printf("\n");
}

int64_t* array_int_min( int64_t* arr, size_t size ) {
    if (!size) return NULL;
    int64_t* min = &arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < *min) min = &arr[i];
    }
    return min;
}

void array_int_print(int64_t *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%" PRId64 " ", arr[i]);
    }
}

void array_int_fill(int64_t *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = read_int64();
    }
}

int64_t **marray_read(size_t *rows, size_t **sizes) {
    *rows = read_size();
    *sizes = (size_t *) malloc(sizeof(size_t) * *rows);
    int64_t **marray = (int64_t **) malloc(sizeof(int64_t *) * *rows);

    for (size_t i = 0; i < *rows; i++) {
        (*sizes)[i] = read_size();
        marray[i] = (int64_t *) malloc(sizeof(int64_t) * (*sizes)[i]);
        array_int_fill(marray[i], (*sizes)[i]);
    }

    return marray;
}

void marray_print(int64_t **marray, size_t *sizes, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        array_int_print(marray[i], sizes[i]);
        print_newline();
    }
}

void marray_free(int64_t **marray, size_t rows) {
    for (; rows > 0; rows--) {
        free(marray[rows - 1]);
    }
    free(marray);
}