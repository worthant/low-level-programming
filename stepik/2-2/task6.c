#include <stdlib.h>
#include "utils.h"

// Указатель на минимальное из двух чисел.
// если хотя бы одно число NULL, то возвращать второе
// если оба числа NULL результат NULL
int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
    if (!x) return y;
    if (!y) return x;
    return (*x > *y) ? y : x;
}


// Вернуть адрес минимального элемента массива массивов
int64_t* marray_int_min(int64_t** marray, size_t* sizes, size_t rows) {
    int64_t* min = NULL;
    for (size_t i = 0; i < rows; i++) {
        int64_t* row_min = array_int_min(marray[i], sizes[i]);
        min = int64_ptr_min(min, row_min);
    }
    return min;
}


// Вычесть m изо всех элементов массива
void marray_normalize(int64_t** marray, size_t sizes[], size_t rows, int64_t m) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < sizes[i]; j++) {
            marray[i][j] -= m;
        }
    }
}

// Прочитать, найти минимум и нормализовать массив, вывести результат
void perform() {
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows, &sizes);

    if (marray == NULL) {
        printf("No data to process.\n");
        return;
    }

    int64_t* min_ptr = marray_int_min(marray, sizes, rows);
    if (min_ptr != NULL) {
        marray_normalize(marray, sizes, rows, *min_ptr);
    }

    marray_print(marray, sizes, rows);
    marray_free(marray, rows);
    free(sizes);
}


int main() {
    perform();
    return 0;
}
