#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock;

void bad_print(char *s) {
    pthread_mutex_lock(&lock);
    for (; *s != '\0'; s++) {
        fprintf(stdout, "%c", *s);
        fflush(stdout);
        usleep(100);
    }
    pthread_mutex_unlock(&lock);
}

void *my_thread(void *arg) {
    for (int i = 0; i < 10; i++) {
        bad_print((char *) arg);
        sleep(1);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, my_thread, "life is..\n");
    pthread_create(&t2, NULL, my_thread, "when you're in love with something and someone at the same time\n");
    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);

    return 0;
}