#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer1 {
	long int msg_type;
	float msg[5];
	float avg;
	float stddev;
}message1;

struct msg_buffer3 {
	long int msg_type;
	int cat[5];
}message3;

int main()
{
	key_t key;
	int msg_id;
	
	key = ftok("msgq2", 65);
	
	msg_id = msgget(key, 0777 | IPC_CREAT);
	
	msgrcv(msg_id, &message1, sizeof(message1), 1, 0);
	
	for(int i=0;i<5;i++)
	{
		if(message1.msg[i] == message1.avg)
		{
			message3.cat[i] = 0;
		}
		else if(message1.msg[i] > (message1.avg + message1.stddev))
		{
			message3.cat[i] = 1;
		}
		else if(message1.msg[i] > message1.avg && message1.msg[i] < (message1.avg + message1.stddev))
		{
			message3.cat[i] = 2;
		}
		else if(message1.msg[i] < message1.avg && message1.msg[i] > (message1.avg - message1.stddev))
		{
			message3.cat[i] = 3;
		}
		else if(message1.msg[i] < (message1.avg - message1.stddev))
		{
			message3.cat[i] = 4;
		}
	}
	
	for(int i=0;i<5;i++)
	{
		printf("L%d - Cat%d\n",i+1, message3.cat[i]);
	}
	
	msgctl(msg_id, IPC_RMID, NULL);
	
	key_t key3;
	int msg_id3;
	
	key3 = ftok("msgq3", 65);
	
	msg_id3 = msgget(key3, 0777 | IPC_CREAT);
	message3.msg_type = 1;
	
	msgsnd(msg_id3, &message3, sizeof(message3), 0);
	
	return 0;
}
