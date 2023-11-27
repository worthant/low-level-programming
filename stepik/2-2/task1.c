// Реализовать считывание массива заранее неизвестной длины, и поиск в нём минимума.
// Первое число на входе -- длина массива, затем идут его элементы.
// Например, пользователь ввёл числа 3 2 0 43. Это значит, что мы выделим массив на 3 элемента, в который запишем 2 0 43.
// Числа в массиве находятся в диапазоне [−2^63;2^63−1]
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

// Считать размер массива в *size,
// выделить память под массив
// заполнить его числами, вызвав array_int_fill
int64_t *array_int_read(size_t *size) {
    *size = read_size();
    int64_t* arr = (int64_t*)malloc(sizeof(int64_t) * *size);
    array_int_fill(arr, *size);
    return arr;
}

int main() {
    size_t size;
    int64_t* arr = array_int_read(&size);

    for (size_t i = 0; i < size; i++) {
        printf("%" PRId64 " ", arr[i]);
    }

    free(arr);

    return 0;
}
