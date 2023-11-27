// Реализуйте функцию для поиска минимума в массиве
// Функция ничего не считывает со стандартного ввода.
// Если минимального элемента в массиве нет, функция возвращает NULL.
// Иначе она возвращает адрес любого из минимальных элементов в массиве.

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

int64_t* array_int_min( int64_t* arr, size_t size ) {
    if (!size) return NULL;
    int64_t* min = &arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < *min) min = &arr[i];
    }
    return min;
}

int8_t test_min_element() {
    // Test 1: Mixed positive and negative numbers
    int64_t arr1[] = {5, -4, 2, -1, 3};
    assert(*array_int_min(arr1, 5) == -4);

    // Test 2: All positive numbers
    int64_t arr2[] = {5, 4, 2, 1, 3};
    assert(*array_int_min(arr2, 5) == 1);

    // Test 3: All negative numbers
    int64_t arr3[] = {-5, -4, -2, -1, -3};
    assert(*array_int_min(arr3, 5) == -5);

    // Test 4: Repeated minimum elements
    int64_t arr4[] = {3, 1, 1, 2, 1};
    assert(*array_int_min(arr4, 5) == 1);

    // Test 5: Empty array
    int64_t arr5[] = {};
    assert(array_int_min(arr5, 0) == NULL);

    return 1;
}

int main() {
    if (test_min_element()) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }

    return 0;
}
