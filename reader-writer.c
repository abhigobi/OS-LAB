#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t writer,reader;

int readcount=0;

void* Writer(void* arg){
    
    sem_wait(&writer);
      printf("Writer %ld is writing\n",pthread_self());
    sem_post(&writer);
}

void* Reader(void* arg){

    sem_wait(&reader);
      readcount++;
      if(readcount == 1){
          sem_wait(&writer);
      }
    sem_post(&reader);
    
    printf("Reader %ld is reading\n",pthread_self());
    
    sem_wait(&reader);
      readcount--;
      if(readcount == 0){
        sem_post(&writer);
      }
    sem_post(&reader);
}

int main(){

  sem_init(&reader,0,1);
  sem_init(&writer,0,1);
  
  pthread_t idr[3],idw[3];
  
  
  pthread_create(&idw[0],NULL,Writer,NULL);
  pthread_create(&idr[0],NULL,Reader,NULL);
  pthread_create(&idw[1],NULL,Writer,NULL);
  pthread_create(&idr[1],NULL,Reader,NULL);
  pthread_create(&idw[2],NULL,Writer,NULL);
  pthread_create(&idr[2],NULL,Reader,NULL);
  
  sleep(5);
}
