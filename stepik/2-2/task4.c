#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int64_t read_int64() {
    int64_t val;
    scanf( "%" SCNd64, &val);
    return val;
}

size_t read_size() {
    size_t val;
    scanf("%zu", &val);
    return val;
}

void array_int_fill(int64_t *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = read_int64();
    }
}

int64_t** marray_read(size_t* rows, size_t** sizes) {
    *rows = read_size();
    *sizes = (size_t*)malloc(sizeof(size_t) * *rows);
    int64_t** marray = (int64_t**)malloc(sizeof(int64_t*) * *rows);

    for (size_t i = 0; i < *rows; i++) {
        (*sizes)[i] = read_size();
        marray[i] = (int64_t*)malloc(sizeof(int64_t) * (*sizes)[i]);
        array_int_fill(marray[i], (*sizes)[i]);
    }

    return marray;
}

void array_int_print(int64_t* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%" PRId64 " ", arr[i]);
    }
}

void print_newline() {
    printf("\n");
}

void marray_print(int64_t** marray, size_t* sizes, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        array_int_print(marray[i], sizes[i]);
        print_newline();
    }
}

int main() {
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows, &sizes);

    marray_print(marray, sizes, rows);

    // Освобождение памяти
    for (size_t i = 0; i < rows; i++) {
        free(marray[i]);
    }
    free(sizes);
    free(marray);

    return 0;
}
