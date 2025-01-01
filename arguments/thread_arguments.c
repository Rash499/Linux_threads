#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg){
    int index = *(int*)arg; //dereference the passed argument to get the index
    printf("%d ", primes[index]); //print the prime number at the given index
    free(arg);
}

int main(int argc, char* argv[]){
    pthread_t th[10];
    int i;
    for(i = 0; i<10; i++){
        int* a = malloc(sizeof(int)); //dynamically allocate memory for the index
        *a = i; //Assign the value of the index to the allocated memory

        if(pthread_create(&th[i], NULL, &routine, a) != 0){ //Passes the dynamically allocated index pointer to the thread routine
            perror("Falied to create thread");
        }
    }

    for(int i = 0; i < 10; i++){
        if(pthread_join(th[i],NULL) != 0){
            perror("Failed to join thread");
        }
    }

    return 0;
}

//output shows the primes that in the 10 threads which not inorder [multithreading]