#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

sem_t full,empty,mutex;

int buffer[5];

int in=0,out=0;

void* producer(void* arg)
{
    sem_wait(&empty);
      sem_wait(&mutex);
          
          buffer[in] = 1 + (rand() % 100);
          in = (in +1) % 5;
          printf("I am producer %d",buffer[in-1]);
          
      sem_post(&mutex);
    sem_post(&full);
    sleep(1);
}

void* consumer(void* arg)
{
    int data;
    int val=0;
    do {
    sem_wait(&full);
      sem_wait(&mutex);
          
          data = buffer[out];
          printf("I am a cosumer  %d",data);
          out = out+1 % 5;
          
      sem_post(&mutex);
    sem_post(&empty);
    sem_getvalue(&empty,&val);
     }while(val!=5);  
     sleep(1);
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&empty,0,5);
    sem_init(&full,0,0);
    
    
    pthread_t idp[5],idc;
   
      pthread_create(&idc,NULL,consumer,NULL);
    for(int i=0;i<3;i++){
    
      pthread_create(&idp[i],NULL,producer,NULL);
    }
    
   pthread_join(idc,NULL);
    
    for(int i=0;i<3;i++){
      pthread_join(idp[i],NULL);
    }
    
   
   printf("hi");

}
