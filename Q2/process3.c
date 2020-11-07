#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <ctype.h>

typedef struct buffer {
	char pass[10];
  	int alpha_len;
  	int char_len;
  	int strength;
  	int flag;
}shmem;

int main() 
{ 
	key_t key = ftok("shmfile",65); 

	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	shmem *mem = (shmem*) shmat(shmid,(void*)0,0); 

	if (mem->alpha_len >= mem->char_len)
		mem->strength = 20;
	else
		mem->strength = 200;
		
	if(mem->strength == 200)
		printf("Strong password\n");
	else if(mem->strength == 20)
		printf("Weak password\n");
	
	mem->flag = 1;
	
	shmdt(mem); 
	
	return 0; 
} 

