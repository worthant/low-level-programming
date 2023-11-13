#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define heap_blocks 16
#define block_capacity 1024

/**
 * Represents a heap data structure containing a fixed number of memory blocks.
 *
 * This structure models a simple heap composed of a fixed number (heap_blocks) of memory blocks,
 * each with a specified capacity (block_capacity). It also keeps track of the occupation status of
 * each block through an array of boolean values, where `true` signifies that the block is occupied
 * and `false` means it is free.
 *
 * Members:
 *   - blocks: An array of `block` structures, representing the individual memory blocks in the heap.
 *   - is_occupied: A boolean array, with each element indicating whether the corresponding block in
 *                  the `blocks` array is occupied.
 */
struct heap {
    struct block {
        char contents[block_capacity];
    } blocks[heap_blocks];
    bool is_occupied[heap_blocks];
} global_heap = { 0 };


/**
 * Represents an identifier for a memory block within a heap.
 *
 * This structure is used to uniquely identify a specific block within a heap. It contains the index
 * of the block in the heap, a flag indicating whether this identifier is valid, and a pointer to the
 * heap to which this block belongs.
 *
 * Members:
 *   - value: The index of the block within the heap.
 *   - valid: A boolean flag indicating whether this block ID is valid.
 *   - heap: A pointer to the `struct heap` containing the block.
 */
struct block_id {
    size_t value;
    bool   valid;
    struct heap* heap;
};


/**
 * Constructs a new, valid block identifier.
 *
 * This function creates and returns a new `block_id` structure with the specified value and heap.
 * The created block ID is marked as valid.
 *
 * @param value The index of the block in the heap.
 * @param from A pointer to the heap to which the new block ID will belong.
 *
 * @return A `block_id` structure representing a valid block identifier within the specified heap.
 */
struct block_id block_id_new(size_t value, struct heap* from) {
    return (struct block_id) { .valid = true, .value = value, .heap = from };
}


/**
 * Checks the validity of a block identifier.
 *
 * This function evaluates whether a given `block_id` is valid. A block ID is considered valid if its
 * `valid` flag is set to true and the `value` (index in the heap) is within the range of valid blocks
 * defined by `heap_blocks`.
 *
 * @param bid The block identifier to be checked.
 *
 * @return Returns `true` if the block ID is valid, `false` otherwise.
 */
bool block_id_is_valid(struct block_id bid) {
    return bid.valid && bid.value < heap_blocks;
}


struct block_id block_id_invalid() {
    return (struct block_id) { .valid = false, .value = 0, .heap = NULL };
}



/**
 * Checks whether a specific block in a heap, identified by `block_id`, is free (not occupied).
 *
 * This function evaluates the occupation status of a block within a heap. It first checks if the provided
 * `block_id` is valid. If valid, it then assesses whether the corresponding block in the heap is occupied
 * or not. The occupation status is determined by accessing the `is_occupied` boolean array in the heap
 * struct, using the index specified in `block_id`.
 *
 * @param bid The block identifier, of type `struct block_id`, which includes the index of the block in the
 *            heap, a validity flag, and a pointer to the heap.
 *
 * @return Returns `true` if the block is not occupied (free), and `false` if the block is occupied or if
 *         the `block_id` is invalid.
 */
bool block_is_free(struct block_id bid) {
    if (!block_id_is_valid(bid)) return false;
    return !bid.heap->is_occupied[bid.value];
}


/* allocate */
/* find a free block, reserve it and return its id */
struct block_id block_allocate(struct heap* heap) {
    for (size_t i = 0; i < heap_blocks; i++) {
        struct block_id curr = block_id_new(i, heap);
        if (block_is_free(curr)) {
            heap->is_occupied[i] = true;
            return curr;
        }
    }
    return block_id_invalid();
}

/* mark block as 'free' */
void block_free(struct block_id b) {
    if (block_id_is_valid(b)) {
        b.heap->is_occupied[b.value] = false;
    }
}


/* printer */
const char* block_repr(struct block_id b) {
    static const char* const repr[] = { [false] = " .",[true] = " =" };
    if (b.valid)
        return repr[b.heap->is_occupied[b.value]];
    else
        return "x";
}

void block_debug_info(struct block_id b, FILE* f) {
    fprintf(f, "%s", block_repr(b));
}

void block_foreach_printer(struct heap* h, size_t count,
    void  printer(struct block_id, FILE* f),
    FILE* f) {
    for (size_t c = 0; c < count; c++)
        printer(block_id_new(c, h), f);
}

void heap_debug_info(struct heap* h, FILE* f) {
    block_foreach_printer(h, heap_blocks, block_debug_info, f);
    fprintf(f, "\n");
}

int main() {
    heap_debug_info(&global_heap, stdout);
    block_allocate(&global_heap);
    struct block_id bid = block_allocate(&global_heap);
    block_allocate(&global_heap);

    block_free(bid);
    heap_debug_info(&global_heap, stdout);
    return 0;
}
