#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define _print(type, x) type##_print(x)

#define print(x)                            \
	_Generic((x),                           \
		int64_t : int64_t_print,            \
		double : double_print,              \
		uint64_t : uint64_t_print,          \
		default : error)(x)

void int64_t_print(int64_t i64) { printf("%" PRId64 "\n", i64); }
void double_print(double d) { printf("%lf\n", d); }
void uint64_t_print(uint64_t u64) { printf("%" PRIu64 "\n", u64); }
void error() { fprintf(stderr, "Unsupported operation\n"); abort(); }
void newline_print() { puts(""); }
void delimiter_print() { puts("-----"); }

#define DEFINE_LIST(type)                                            \
    struct list_##type {                                             \
        type value;                                                  \
        struct list_##type *next;                                    \
    };                                                               \
    void list_##type##_init() {                                      \
        newline_print();                                             \
        delimiter_print();                                           \
    }                                                                \
    void list_##type##_end() {                                       \
    	delimiter_print();                                           \
    	newline_print();                                             \
    }                                                                \
    void list_##type##_push(struct list_##type **head, type input_value) { \
        struct list_##type *new_node = malloc(sizeof(struct list_##type)); \
        new_node->value = input_value;                               \
        new_node->next = NULL;                                       \
        if (*head == NULL) {                                         \
            *head = new_node;                                        \
        } else {                                                     \
            struct list_##type *current = *head;                     \
            while (current->next != NULL) {                          \
                current = current->next;                             \
            }                                                        \
            current->next = new_node;                                \
        }                                                            \
    }                                                                \
    void list_##type##_print(struct list_##type *head) {             \
        struct list_##type *current = head;                          \
        while (current != NULL) {                                    \
            print(current->value);                                   \
            current = current->next;                                 \
        }                                                            \
    }

DEFINE_LIST(int64_t)
DEFINE_LIST(double)
DEFINE_LIST(uint64_t)

int main() {
    struct list_int64_t *head1 = NULL;
    list_int64_t_init();
    list_int64_t_push(&head1, 42);
    list_int64_t_push(&head1, 43);
    list_int64_t_print(head1);
    list_int64_t_end();

    struct list_double *head2 = NULL;
    list_double_init();
    list_double_push(&head2, 3.14);
    list_double_push(&head2, 1.41);
    list_double_print(head2);
    list_double_end();

    struct list_uint64_t *head3 = NULL;
    list_uint64_t_init();
    list_uint64_t_push(&head3, 21923876452938567);
    list_uint64_t_push(&head3, 987654329574635384);
    list_uint64_t_print(head3);
    list_uint64_t_end();

    return 0;
}
