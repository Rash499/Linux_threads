#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(){
    int value = (rand() % 6) + 1;       //generate a random number 1-6

    int* result = malloc(sizeof(int)); //allocate memory for an integer dynamically
    *result = value;                   //Stores the random value in that allocated memory
    //printf("%d\n",value);
    printf("Thread result: %p\n",result);  //print the address of the allocated memory

    return (void*) result;   //Return the pointer to the allocate memory
}

int main(int argc, char* argv[]){

    int* res;   //Pointer to hold the address of the dynamically allocated result
    srand(time(NULL));  //seed the random number generator with the current time

    pthread_t th;
    if(pthread_create(&th, NULL, &roll_dice, NULL) != 0){
        return 1;
    }
    if(pthread_join(th,(void**) &res) != 0){ //type cast to the double pointer
        return 2;                            //A pointer to a pointer where the thread's return value (memory address) will be stored.

    }
    printf("Main res: %p\n",res);
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}