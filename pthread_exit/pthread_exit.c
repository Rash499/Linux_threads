#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_square(void* arg) {
    int num = *(int*)arg;
    int* result = malloc(sizeof(int)); // Allocate memory for the result
    *result = num * num;
    printf("Thread for number %d calculated square: %d\n", num, *result);
    pthread_exit(result); // Exit the thread and return the result
}

int main() {
    pthread_t threads[5];
    int numbers[5] = {1, 2, 3, 4, 5};
    int* result;

    // Create threads
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, calculate_square, &numbers[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads and retrieve results
    for (int i = 0; i < 5; i++) {
        if (pthread_join(threads[i], (void**)&result) != 0) {
            perror("Failed to join thread");
            return 2;
        }
        printf("Main thread received result: %d\n", *result);
        free(result); // Free the dynamically allocated memory
    }

    return 0;
}
