#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct shemem{
  
  char buff[100];
  int flag;
};

int main(){

    key_t key = ftok("shmfile1",65);
    
    int shmid = shmget(key,1024,0666 | IPC_CREAT);
    
    struct shemem *str = (struct shemem *)shmat(shmid,NULL,0);
    
    str->flag=0;
    printf("Write something = ");
    gets(str->buff);
    
    str->flag=1;
    
    while(str->flag!=0){
      printf("Waiting");
    }
    printf("Data is written");
    
    shmdt(str);
}
