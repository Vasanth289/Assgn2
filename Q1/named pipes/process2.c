#include <math.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msg_buffer1 {
	long int msg_type;
	float msg[5];
	float avg;
	float stddev;
}message;

float avg_fn(float *arr)
{
	float sum = 0;
	for(int i=0;i<5;i++)
	{
		sum += *(arr + i);
	}
	sum /= 5;
	return sum;
}

float stddev_fn(float *arr, float mean)
{
	float t;
	float sum = 0;
	for(int i=0;i<5;i++)
	{
		t = *(arr + i) - mean;
		
		sum += (t * t);
	}
	sum /= 5;
	sum = sqrt(sum);
	return sum;
}

int main()
{
	key_t key;
	int msg_id;
	
	key = ftok("msgq1", 65);
	
	msg_id = msgget(key, 0777 | IPC_CREAT);
	
	msgrcv(msg_id, &message, sizeof(message), 1, 0);
	
	message.avg = avg_fn(message.msg);
	
	message.stddev = stddev_fn(message.msg, message.avg);
	
	printf("Avg: %.2f\n", message.avg);
	printf("Std. dev: %.2f\n", message.stddev);
	
	msgctl(msg_id, IPC_RMID, NULL);
	
	key_t key2;
	int msg_id2;
	
	key2 = ftok("msgq2", 65);
	
	msg_id2 = msgget(key2, 0777 | IPC_CREAT);
	message.msg_type = 1;
	
	msgsnd(msg_id2, &message, sizeof(message), 0);
	
	return 0;
}
