#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void* create_shared_memory(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

int main() {
    int* shmem = (int*) create_shared_memory(10 * sizeof(int));

    // Заполним общую память числами от 1 до 10
    fputs("Initial array:", stdout);
    for (int i = 0; i < 10; i++) {
        shmem[i] = i + 1;
        printf(" %d", i);
    }
    puts("\n");

    int pid = fork();

    if (pid == 0) {
        // Дочерний процесс
        printf("[child] Enter index and new value: ");
        int index, value;
        scanf("%d %d", &index, &value);
        if (index >= 0 && index < 10) {
            shmem[index] = value;
        }
        exit(0);
    } else {
        // Родительский процесс
        wait(NULL); // Ждем завершения дочернего процесса
        printf("[parent] Updated array: ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", shmem[i]);
        }
        printf("\n");
    }
    return 0;
}
