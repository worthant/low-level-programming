#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_BLOCKS 16
#define BLOCK_CAPACITY 1024

enum block_status { BLK_FREE = 0, BLK_ONE, BLK_FIRST, BLK_CONT, BLK_LAST };

/**
 * Represents a heap data structure containing a fixed number of memory blocks, each with a status.
 *
 * This structure models a more sophisticated heap than a simple binary occupied/free scheme. It
 * consists of a fixed number (heap_blocks) of memory blocks, each having a specified capacity
 * (block_capacity). The status of each block is tracked using `enum` that can represent a block
 * being free, a single occupied block, or part of a contiguous sequence of occupied blocks.
 *
 * The block statuses are as follows:
 * - BLK_FREE: The block is free and unoccupied.
 * - BLK_ONE: The block is occupied on its own, not as part of a contiguous sequence.
 * - BLK_FIRST: The block is the first in a sequence of occupied blocks.
 * - BLK_CONT: The block is a continuation (middle) of a sequence of occupied blocks.
 * - BLK_LAST: The block is the last in a sequence of occupied blocks.
 *
 * Members:
 *   - blocks: An array of `block` structures, representing the individual memory blocks in the heap.
 *             Each block contains a data array of a fixed size (BLOCK_CAPACITY).
 *   - status: An array of `enum block_status`, with each element indicating the status of the
 *             corresponding block in the `blocks` array. This allows for more granular control over
 *             block allocation, such as allocating multiple contiguous blocks.
 */
struct heap {
	struct block {
		char contents[BLOCK_CAPACITY];
	} blocks[HEAP_BLOCKS];
	enum block_status status[HEAP_BLOCKS];
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
	size_t       value;
	bool         valid;
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
 * Constructs an invalid block identifier.
 *
 * This function generates and returns a `block_id` structure representing an invalid block ID.
 * The use of an invalid block ID is typically for signaling error conditions or the absence of a
 * valid block in various operations within the heap. An invalid block ID is created with its
 * `valid` member set to false, indicating that it does not correspond to any legitimate block
 * in the heap.
 *
 * @return A `block_id` structure with the `valid` member set to false, representing an invalid
 *         block identifier.
 */
struct block_id block_id_invalid() {
	return (struct block_id) { .valid = false };
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
	return bid.valid && bid.value < HEAP_BLOCKS && bid.heap != NULL;
}


/**
 * Checks if a block in the heap, identified by its block ID, is free.
 *
 * This function determines whether a specific block in the heap is not currently occupied.
 * It first verifies the validity of the provided block ID. If valid, the function then checks
 * the block's status in the heap to determine if it is marked as free.
 *
 * @param bid The block identifier, of type `struct block_id`, which includes the index of the block
 *            in the heap and a pointer to the heap.
 *
 * @return Returns `true` if the block is free (unoccupied), and `false` if the block is occupied
 *         or if the `block_id` is invalid.
 */
bool block_is_free(struct block_id bid) {
	if (!block_id_is_valid(bid))
		return false;
	return bid.heap->status[bid.value] == BLK_FREE;
}

/**
 * Allocates a contiguous sequence of blocks in the heap of the specified size.
 *
 * This function iterates over blocks looking for a suitable starting point. Then, it's checking
 * if there is enough room for allocating blocks of (size). If enough, it marks these blocks with
 * the appropriate status (BLK_FIRST, BLK_CONT, BLK_LAST, or BLK_ONE for a single block) to denote
 * their allocation and returns the block ID of the first block in this sequence. If a suitable space
 * is not found, it returns an invalid block ID.
 *
 * @param heap A pointer to the heap where blocks are to be allocated.
 * @param size The number of contiguous blocks to allocate.
 *
 * @return The block ID of the first block in the allocated sequence if successful, or an invalid
 *         block ID if the allocation fails.
 */
struct block_id block_allocate(struct heap* heap, size_t size) {
	// Iterate over blocks looking for a suitable starting point
	for (size_t i = 0; i < HEAP_BLOCKS; i++) {
		// Check if there's enough room
		if (i + size <= HEAP_BLOCKS) {
			bool has_space = true;
			for (size_t j = i; j < i + size; j++) {
				if (heap->status[j] != BLK_FREE) {
					has_space = false;
					break;
				}
			}
			// If we found enough space
			if (has_space) {
				// Mark blocks
				for (size_t j = i; j < i + size; j++) {
					if (size == 1) {
						heap->status[j] = BLK_ONE;
					}
					else if (j == i) {
						heap->status[j] = BLK_FIRST;
					}
					else if (j == i + size - 1) {
						heap->status[j] = BLK_LAST;
					}
					else {
						heap->status[j] = BLK_CONT;
					}
				}
				return block_id_new(i, heap);
			}
		}
	}
	return block_id_invalid();
}

/**
 * Frees a sequence of allocated blocks in the heap starting from the specified block.
 *
 * This function frees a contiguous sequence of blocks starting from the given block ID,
 * provided that the block is either a single occupied block (BLK_ONE) or the start of
 * a sequence (BLK_FIRST). The status of these blocks is set back to BLK_FREE. If the
 * block ID is not valid or does not signify the start of an allocated sequence, the
 * function performs no action.
 *
 * @param b The block identifier, of type `struct block_id`, indicating the starting block
 *          of the sequence to be freed.
 */
void block_free(struct block_id b) {
	if (!block_id_is_valid(b)) return;

	if (b.heap->status[b.value] == BLK_ONE) {
		b.heap->status[b.value] = BLK_FREE;
	}
	else if (b.heap->status[b.value] == BLK_FIRST) {
		size_t i = b.value;
		while (i < HEAP_BLOCKS && b.heap->status[i] != BLK_LAST) {
			b.heap->status[i] = BLK_FREE;
			i++;
		}
		if (i < HEAP_BLOCKS && b.heap->status[i] == BLK_LAST) {
			b.heap->status[i] = BLK_FREE;
		}
	}
}


/**
 * Returns a string representation of a block's status.
 *
 * This function generates a string representation based on the status of a block in the heap,
 * identified by the given block ID. It uses an array of strings corresponding to each possible
 * block status (e.g., free, single occupied block, first of a contiguous sequence, etc.). If the
 * block ID is invalid, it returns "INVALID".
 *
 * @param b The block identifier, of type `struct block_id`.
 *
 * @return A constant character pointer to a string representing the block's status. If the block
 *         ID is invalid, returns "INVALID".
 */
const char* block_repr(struct block_id b) {
	static const char* const repr[] = { [BLK_FREE] = " .",
									   [BLK_ONE] = " *",
									   [BLK_FIRST] = "[=",
									   [BLK_LAST] = "=]",
									   [BLK_CONT] = " =" };
	if (b.valid)
		return repr[b.heap->status[b.value]];
	else
		return "INVALID";
}


/**
 * Prints debug information for a specific block to the given file stream.
 *
 * This function outputs the string representation of a block's status to the specified file stream.
 * It is typically used for debugging purposes to visually represent the status of each block in the
 * heap. The representation is obtained from `block_repr`.
 *
 * @param b The block identifier to print information for.
 * @param f The file stream to print the information to (e.g., stdout).
 */
void block_debug_info(struct block_id b, FILE* f) {
	fprintf(f, "%s", block_repr(b));
}


/**
 * Iterates over each block in the heap and applies a given printing function.
 *
 * This function iterates over a specified number of blocks in the heap and applies a provided
 * printer function to each block. It is a generic function that can be used with different printer
 * functions to display various aspects of the heap's state.
 *
 * @param h A pointer to the heap to iterate over.
 * @param count The number of blocks to iterate over.
 * @param printer The printer function to apply to each block. It should take a `block_id` and a
 *                file stream as parameters.
 * @param f The file stream to print the information to (e.g., stdout).
 */
void block_foreach_printer(struct heap* h, size_t count,
	void printer(struct block_id, FILE* f), FILE* f) {
	for (size_t c = 0; c < count; c++)
		printer(block_id_new(c, h), f);
}


/**
 * Prints the entire heap's debug information to the given file stream.
 *
 * This function provides a complete visual representation of the heap's current state by printing
 * each block's status. It utilizes `block_foreach_printer` to iterate over all the blocks in the
 * heap and print their status using the specified debug information printer function.
 *
 * @param h A pointer to the heap whose information is to be printed.
 * @param f The file stream to print the heap's information to (e.g., stdout).
 */
void heap_debug_info(struct heap* h, FILE* f) {
	block_foreach_printer(h, HEAP_BLOCKS, block_debug_info, f);
	fprintf(f, "\n");
}


/*  ---- tests ----  */

void test_invalid_free() {
	printf("Test 1: Invalid Free Attempt\n");
	heap_debug_info(&global_heap, stdout);

	struct block_id bid = block_allocate(&global_heap, 2);
	printf("After allocating two contiguous blocks:\n");
	heap_debug_info(&global_heap, stdout);

	struct block_id invalid_bid = block_id_new(bid.value + 1, bid.heap);
	if (invalid_bid.value < HEAP_BLOCKS) {
		block_free(invalid_bid); // Attempt to free from the middle of an allocation
	}
	printf("After invalid free attempt:\n");
	heap_debug_info(&global_heap, stdout);

	// Clean up
	block_free(bid);
}


void test_single_block_allocation_and_free() {
	printf("\nTest 2: Allocating and Freeing a Single Block\n");
	heap_debug_info(&global_heap, stdout);

	struct block_id bid = block_allocate(&global_heap, 1);
	printf("After allocating one block:\n");
	heap_debug_info(&global_heap, stdout);

	block_free(bid);
	printf("After freeing the allocated block:\n");
	heap_debug_info(&global_heap, stdout);
}


void test_multiple_blocks_allocation() {
	printf("\nTest 3: Allocating Multiple Contiguous Blocks\n");
	heap_debug_info(&global_heap, stdout);

	struct block_id bid = block_allocate(&global_heap, 3);
	printf("After allocating three contiguous blocks:\n");
	heap_debug_info(&global_heap, stdout);

	block_free(bid);
	printf("After freeing the contiguous blocks:\n");
	heap_debug_info(&global_heap, stdout);
}


void test_allocation_exceeding_heap() {
	printf("\nTest 4: Attempting to Allocate More Blocks Than Available\n");
	heap_debug_info(&global_heap, stdout);

	struct block_id bid = block_allocate(&global_heap, HEAP_BLOCKS + 1);
	if (!block_id_is_valid(bid)) {
		printf("Allocation failed as expected\n");
	}
	heap_debug_info(&global_heap, stdout);
}


void test_partial_free() {
	printf("\nTest 5: Allocating All Blocks and Freeing in the Middle\n");
	heap_debug_info(&global_heap, stdout);

	struct block_id bid = block_allocate(&global_heap, HEAP_BLOCKS);
	printf("After allocating all blocks got the bid with the %zu:\n", bid.value);
	heap_debug_info(&global_heap, stdout);

	// Free a few blocks in the middle
	size_t middle = HEAP_BLOCKS / 2;
	global_heap.status[middle] = BLK_FREE; // Simulate freeing a block in the middle
	printf("After freeing a block in the middle:\n");
	heap_debug_info(&global_heap, stdout);
}


/* ---- main ---- */

int main() {
	test_invalid_free();
	test_single_block_allocation_and_free();
	test_multiple_blocks_allocation();
	test_allocation_exceeding_heap();
	test_partial_free();

	return 0;
}

