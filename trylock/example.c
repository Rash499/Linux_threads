#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <time.h>

pthread_mutex_t stoveMutexs[4];
int stoveFuel[4] = {100,100,100,100};

void* routine(void* args){
    for(int i = 0; i < 4; i++){
        if(pthread_mutex_trylock(&stoveMutexs[i])== 0){

            int fuelNeeded = (rand() % 20);

            if(stoveFuel - fuelNeeded < 0){
                printf("No more fuel...  go home\n");
            }
            else{
                stoveFuel[i] -= fuelNeeded;
                sleep(1);
                printf("Fuel left %d\n", stoveFuel[i]);
            }
            
            sleep(1);
            pthread_mutex_unlock(&stoveMutexs[i]);
            break;
        }
        else {
            if(i==3){
                printf("No stove available yet, waiting...\n");
                usleep(300000);
                i = 0;
            }
        }
    
    }
  
}

int main(int argc, char* argv[]){

    pthread_t th[10];

    for(int i = 0; i < 4; i++){
        pthread_mutex_init(&stoveMutexs[i], NULL);
    }
    

    for(int i = 0; i < 10; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0){
            perror("Failed to create thread\n");
        }
    }

    for(int i = 0; i < 10; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread\n");
        }
    }

    for(int i = 0; i < 4; i++){
        pthread_mutex_destroy(&stoveMutexs[i]);
    }
    
    return 0;


}