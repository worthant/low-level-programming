#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define print(x)                            \
    _Generic((x),                           \
        int64_t : int64_t_print,            \
        double : double_print,              \
        uint64_t : uint64_t_print,          \
        default : error)(x)

void int64_t_print(int64_t i) { printf("%" PRId64 "\n", i); }
void double_print(double d) { printf("%lf\n", d); }
void uint64_t_print(uint64_t u) { printf("%" PRIu64 "\n", u); }
void error() { fprintf(stderr, "Unsupported operation\n"); abort(); }
void newline_print() { puts(""); }
void delimiter_print() { puts("-----"); }

#define DEFINE_LIST(type)                                      \
    typedef struct Node_##type {                               \
        type value;                                            \
        struct Node_##type *next;                              \
    } Node_##type;                                             \
    void list_init_##type() {                                  \
        newline_print();                                       \
        delimiter_print();                                     \
    }                                                          \
    void list_end_##type() {                                   \
        delimiter_print();                                     \
        newline_print();                                       \
    }                                                          \
    void list_push_##type(Node_##type **head, type value) {    \
        Node_##type *new_node = malloc(sizeof(Node_##type));   \
        new_node->value = value;                               \
        new_node->next = NULL;                                 \
        if (!*head) {                                          \
            *head = new_node;                                  \
        } else {                                               \
            Node_##type *temp = *head;                         \
            while (temp->next) {                               \
                temp = temp->next;                             \
            }                                                  \
            temp->next = new_node;                             \
        }                                                      \
    }                                                          \
    void list_print_##type(Node_##type *head) {                \
        while (head) {                                         \
            print(head->value);                                \
            head = head->next;                                 \
        }                                                      \
    }

#define list_push(head, value) _Generic((value),    \
    int64_t: list_push_int64_t,                     \
    double: list_push_double,                       \
    uint64_t: list_push_uint64_t                    \
)(head, value)

#define list_print(head) _Generic((*(head))->value, \
    int64_t: list_print_int64_t,                    \
    double: list_print_double,                      \
    uint64_t: list_print_uint64_t                   \
)(*head)

DEFINE_LIST(int64_t)
DEFINE_LIST(double)
DEFINE_LIST(uint64_t)

int main() {
    Node_int64_t *head1 = NULL;
    list_init_int64_t();
    list_push(&head1, (int64_t)42);
    list_push(&head1, (int64_t)43);
    list_print(&head1);
    list_end_int64_t();

    Node_double *head2 = NULL;
    list_init_double();
    list_push(&head2, 3.14);
    list_push(&head2, 1.41);
    list_print(&head2);
    list_end_double();

    Node_uint64_t *head3 = NULL;
    list_init_uint64_t();
    list_push(&head3, (uint64_t)21923876452938567);
    list_push(&head3, (uint64_t)987654329574635384);
    list_print(&head3);
    list_end_uint64_t();

    return 0;
}
