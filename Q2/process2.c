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
	
	mem->alpha_len = 0;
	mem->char_len = 0;
	
	for(int i=0;i<10;i++)
	{
		if(isalnum(mem->pass[i]) != 0) { mem->alpha_len += 1; }
		else { mem->char_len += 1; }
	}
	
	printf("Alphanumeric character count: %d\n", mem->alpha_len);
	printf("Special character count: %d\n", mem->char_len);

	shmdt(mem); 
	
	return 0; 
} 

