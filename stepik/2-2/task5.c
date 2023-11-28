#include <stdlib.h>
#include "utils.h"

void _marray_free(int64_t **marray, size_t rows) {
    for (; rows > 0; rows--) {
        free(marray[rows - 1]);
    }
    free(marray);
}

int main() {
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows, &sizes);

    marray_print(marray, sizes, rows);

    // Освобождение памяти
    _marray_free(marray, rows);
    free(sizes);

    return 0;
}