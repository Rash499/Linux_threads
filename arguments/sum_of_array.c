#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg){
    int index = *(int*)arg; //dereference the passed argument to get the index
    int sum = 0;
    for(int i = 0; i<5; i++){
        sum += primes[index + i];
    }
    printf("Local Sum: %d\n",sum);
    *(int*)arg = sum;   //Update the memory location with the local sum
    return arg;    //Return the memory pointer containing the sum
}

int main(int argc, char* argv[]){
    pthread_t th[2];
    int i;
    for(i = 0; i<2; i++){
        int* a = malloc(sizeof(int)); //dynamically allocate memory for the index
        *a = i * 5; //get the six element when i=1

        if(pthread_create(&th[i], NULL, &routine, a) != 0){ //Passes the dynamically allocated index pointer to the thread routine
            perror("Falied to create thread");
        }
    }

    int globalSum = 0;

    for(int i = 0; i < 2; i++){
        int* r;
        if(pthread_join(th[i],(void **) &r) != 0){ //Retrieve the result pointer from the thread; 
            perror("Failed to join thread");
        }
        globalSum += *r;   //Add the thread's result to the global sum
        free(r);
    }
    printf("Global Sum: %d\n",globalSum);
    return 0;
}

