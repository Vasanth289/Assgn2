# Assignment 2

## Question 1

### Named pipes

System calls used:

	mkfifo(): Creates a new FIFO special file named by the pathname pointed to by path. 
		The file permission bits of the new FIFO shall be initialized from mode.

	ftok(): is use to generate a unique key.

	msgget(): either returns the message queue identifier for a newly created message 
	queue or returns the identifiers for a queue which exists with the same key value.

	msgsnd(): Data is placed on to a message queue by calling msgsnd().

	msgrcv(): messages are retrieved from a queue.

	msgctl(): It performs various operations on a queue. Generally it is use to 
	destroy message queue.

Commands:

    $ gcc -o process1 process1.c
    $ gcc -o process2 process2.c -lm
    $ gcc -o process3 process3.c
	// Execute the below commands in different terminals
    $ ./process1
    $ ./process2
    $ ./process2

### Unnamed pipes

System calls used:

	fork(): Fork system call is used for creating a new process, which is called child process,
		which runs concurrently with the process that makes the fork() call (parent process).

	pipe(): The pipe() system call is used to open file descriptors, which are used to communicate between 
		different Linux processes. It is used for inter-process communication in Linux.

	read(): It attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

	write(): Writes up to count bytes from the buffer starting at buf to the file referred to by the file 
		descriptor fd.

	close(): Closes a file descriptor, so that it no longer refers to any file and may be reused. 
		Any record locks held on the file it was associated with, and owned by the process, are removed.

Commands:

    $ gcc -o Q1 Q1.c -lm
    $ ./Q1

## Question 2

### Shared memory

System calls used:

    ftok(): is use to generate a unique key.

    shmget(): int shmget(key_t,size_tsize,intshmflg); upon successful completion, 
		shmget() returns an identifier for the shared memory segment.
	
    shmat(): Before you can use a shared memory segment, you have to attach yourself to it using shmat(). 
		void *shmat(int shmid ,void *shmaddr ,int shmflg); shmid is shared memory id. 
		shmaddr specifies specific address to use but we should set it to zero and OS will automatically 
		choose the address.

    shmdt(): When you’re done with the shared memory segment, your program should
    	detach itself from it using shmdt(). int shmdt(void *shmaddr);

    shmctl(): when you detach from shared memory,it is not destroyed. So, to destroy 
		shmctl() is used. shmctl(int shmid,IPC_RMID,NULL); 

Commands:

    $ gcc -o process1 process1.c
    $ gcc -o process2 process2.c
    $ gcc -o process3 process3.c
	// Execute the below commands in different terminals
    $ ./process1
    $ ./process2
    $ ./process2
