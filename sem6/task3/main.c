#include "vector.h"
#include <stdio.h>

int main() {
    Vector *my_vector = vector_create(5);

    for (int i = 0; i <= 100; i++) {
        vector_push_back(my_vector, ((int64_t)i * (int64_t)i));
    }

    vector_print(my_vector, stdout);
    vector_destroy(my_vector);

    return 0;
}
