#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <error.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

int fuel = 0;

void* fuel_filling(void* arg){

    for(int i = 0; i < 5; i++){

        pthread_mutex_lock(&mutexFuel);  //lock the mutex before modifying the shared resource

        fuel += 15;     //Add 15 units of fuel

        printf("Filled fuel... %d\n",fuel);
        pthread_mutex_unlock(&mutexFuel);   //unclock the mutex after modifying the shared resource

        pthread_cond_signal(&condFuel);     //Signal the car thread that fuel is available

        sleep(1);   //simulate time taken to fill fuel
    }
}

void* car(void* arg){
    pthread_mutex_lock(&mutexFuel);     //lock the mutex before accessing the shared resource

    while(fuel < 40){
        printf("No fuel. waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;     //consume 40 units of fuel

    printf("Got fuel. Now left: %d\n",fuel);
    pthread_mutex_unlock(&mutexFuel);   //Unlock mutex
}

int main(int argc, char* argv[]){

    pthread_t th[2];

    pthread_mutex_init(&mutexFuel, NULL);   //initialize the mutex

    pthread_cond_init(&condFuel, NULL);     //initialize the condition variable

    //creating threads
    for(int i = 0; i < 2; i++){
        if(i== 1){
            if(pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0){
                perror("Failed to creating thread");
            }
        }
        else{
                if(pthread_create(&th[i], NULL, &car, NULL) != 0){
                    perror("Failed to creating thread");
                }
        }
            
        
    }

    //joinning threads
    for(int i = 0; i< 2; i++){
        if(pthread_join(th[i],NULL) != 0){
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel); //destroy the condition variable
    
    return 0;
}