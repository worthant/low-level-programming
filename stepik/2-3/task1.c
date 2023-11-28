#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

struct maybe_int64 {
    bool valid;
    int64_t value;
};

void maybe_int64_print(struct maybe_int64 i) {
    if (i.valid) printf("Some %" PRId64, i.value);
    else printf("None");
}

struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (!a.valid && !b.valid) return (struct maybe_int64){false, 0};
    if (!a.valid) return b;
    if (!b.valid) return a;
    return (a.value < b.value) ? a : b;
}

int main() {
    struct maybe_int64 x = {true, 42};
    struct maybe_int64 y = {true, 24};
    struct maybe_int64 result = maybe_int64_min(x, y);
    maybe_int64_print(result);
    return 0;
}
