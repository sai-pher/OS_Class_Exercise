#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile int counter = 0;
int loops;

void *worker(void *arg){
    int i;
    for (i = 0; i < loops; i += 1){
        counter += 1;
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: too many threads");
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value: %d", counter);
    
    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Final value: %d", counter);

    return 0;
}
