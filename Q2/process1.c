#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>

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

	printf("Enter the password of length 10 letters\n");
	scanf("%s",mem->pass);
	
	mem->flag = 0;
	
	while(mem->flag == 0)
		sleep(1);
	
	printf("Password strength: ");
	if(mem->strength == 200)
		printf("Strong\n");
	else if(mem->strength == 20)
		printf("Weak\n");
	
	shmdt(mem); 
	
	shmctl(shmid,IPC_RMID,NULL);

	return 0; 
} 

