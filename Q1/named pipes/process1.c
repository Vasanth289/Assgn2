#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct msg_buffer1 {
	long int msg_type;
	float msg[5];
}message;

struct msg_buffer2 {
	long int msg_type;
	int cat[5];
}message1;

int main()
{
	mkfifo("msgq1", 0777);
	mkfifo("msgq2", 0777);
	mkfifo("msgq3", 0777);
	
	key_t key;
	int msg_id;
	
	key = ftok("msgq1", 65);
	msg_id = msgget(key, 0777 | IPC_CREAT);
	message.msg_type = 1;
	
	printf("Enter the temperature of different locations in the range of 15 deg Celsius to 45 deg Celsius\n");
	for(int i=0;i<5;i++)
	{
		printf("L%d: ",i+1);
		scanf("%f",&message.msg[i]);
	}
	
	msgsnd(msg_id, &message, sizeof(message), 0);
	
	key_t key1;
	int msg_id1;
	
	key1 = ftok("msgq3", 65);
	msg_id1 = msgget(key1, 0777 | IPC_CREAT);
	
	msgrcv(msg_id1, &message1, sizeof(message1), 1, 0);

	printf("\nRevised temperatures:\n");
	for(int i=0;i<5;i++)
	{
		if(message1.cat[i] == 1)
		{
			message.msg[i] -= 3;
		}
		else if(message1.cat[i] == 2)
		{
			message.msg[i] -= 1.5;
		}
		else if(message1.cat[i] == 3)
		{
			message.msg[i] += 2;
		}
		else  if(message1.cat[i] == 4)
		{
			message.msg[i] += 2.5;
		}
		printf("L%d: %.2f deg Celsius\n",i+1, message.msg[i]);
	}
	
	msgctl(msg_id1, IPC_RMID, NULL);
	
	unlink("msgq1");
	unlink("msgq2");
	unlink("msgq3");
	
	return 0;
}
