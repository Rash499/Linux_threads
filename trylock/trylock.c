#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* routine(void* arg){

    if(pthread_mutex_trylock(&mutex) == 0){
        printf("Got Lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else{
        printf("Didn't get lock\n");
    }
    
}

int main(int argc, char* argv[]){
    pthread_t th[4];

    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < 4; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL)){
            perror("Error at creating thread");
        }
    }

    for(int i = 0; i < 4; i++){
        if(pthread_join(th[i],NULL) != 0){
            perror("Error at joining thread");
        }
    }

    return 0;
}

//output

/*

Got Lock
Didn't get lock
Didn't get lock
Didn't get lock

Code demonstrates the use of pthread_mutex_trylock, which is a non-blocking mutex lock function. 
It shows how multiple threads compete for a shared lock (mutex), with only one thread successfully acquiring the lock at a time.
The remaining threads fail to acquire the lock and proceed without waiting for it to be released

*/