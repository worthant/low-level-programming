// Реализуйте функцию perform которая считывает массив со входа,
// и выводит его минимальный элемент.
// Если массив пустой, выведите None.
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

// заполнить уже выделенный массив array размера size числами
// числа нужно считывать из потока ввода
void array_int_fill(int64_t *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = read_int64();
    }
}

int64_t *array_int_read(size_t *size) {
    *size = read_size();
    int64_t* arr = (int64_t*)malloc(sizeof(int64_t) * *size);
    array_int_fill(arr, *size);
    return arr;
}

int64_t* array_int_min( int64_t* arr, size_t size ) {
    if (!size) return NULL;
    int64_t* min = &arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < *min) min = &arr[i];
    }
    return min;
}

// Выводит None если x == NULL, иначе число, на которое указывает x.
void intptr_print( const int64_t* x ) {
    if (x == NULL) printf("None");
    printf("%" PRId64 " ", *x);
}

void perform() {
    size_t size;
    int64_t* arr = array_int_read(&size);
    intptr_print(array_int_min(arr, size));
    free(arr);
}

int main() {
    perform();

    return 0;
}