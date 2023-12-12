#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define ARR_SIZE 10

void *create_shared_memory(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

void print_array(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}

void change_array_element(size_t index, int new_value, int *arr, size_t size) {
    if (index < size) {
        arr[index] = new_value;
    }
}

int main(void) {
    sem_t *child_ready, *parent_ready;
    child_ready = sem_open("/child_ready", O_CREAT, 0644, 0);
    parent_ready = sem_open("/parent_ready", O_CREAT, 0644, 0);

    int *shmem = create_shared_memory(sizeof(int) * ARR_SIZE);
    for (size_t i = 0; i < ARR_SIZE; i++) {
        shmem[i] = i + 1;  // initializing array with values 1 to 10
    }
    printf("Shared memory at: %p\n", (void *) shmem);

    int* flag = &shmem[ARR_SIZE]; // Last element as the flag
    *flag = 1;
    int pid = fork();
    if (pid == 0) {  // Child process
        while (*flag) {
            puts("[child] enter index and new value (enter negative index to exit): ");
            size_t index;
            int num;
            scanf("%zu %d", &index, &num);
            if (index >= ARR_SIZE || index < 0) {
                *flag = 0;
            }

            change_array_element(index, num, shmem, ARR_SIZE);
            sem_post(child_ready);  // Signal parent process
            sem_wait(parent_ready);  // Wait for parent to acknowledge
        }
        puts("[child] finishing child process...");
    } else {  // Parent process
        while (*flag) {
            sem_wait(child_ready);  // Wait for child signal
            puts("[parent] array after modification: ");
            print_array(shmem, ARR_SIZE);
            puts("[parent] enter 'c' to continue or any other key to exit: ");
            char cont;
            scanf(" %c", &cont);
            if (cont != 'c') break;
            sem_post(parent_ready);  // Signal child process
        }
    }

    // Cleanup
    sem_close(child_ready);
    sem_close(parent_ready);
    sem_unlink("/child_ready");
    sem_unlink("/parent_ready");
    munmap(shmem, sizeof(int) * ARR_SIZE);

    return 0;
}
