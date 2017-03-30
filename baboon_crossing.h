// Michael Girbino - mjg159
// EECS 338 HW6: Baboon Crossing Semaphore Implementation

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>

// key for semaphores and shared memory:
#define SEMAPHORE_KEY        0xFA2B

// for use with semget:
#define SEMAPHORE_MUTEX	0
#define SEMAPHORE_AtoB	1
#define SEMAPHORE_BtoA	2
#define NUMBER_OF_SEMAPHORES 3

#define MIN_NUMBER_OF_BABOONS 30
#define MAX_NUMBER_OF_BABOONS 50
#define BABOONAtoB	1
#define BABOONBtoA	2

// The amount of loop iterations to stall between making baboon processes
#define BABOON_CREATE_STALL_TIME	7000
// The amount of loop iterations to stall when crossing the rope
#define CROSS_ROPE_STALL_TIME	100000

void baboon_fork(int atob_or_btoa);

void AtoB();
void BtoA();

// Semaphore functions
void semaphore_wait(int semid, int semnumber);
void semaphore_signal(int semid, int semnumber);

// A staller function that runs an empty for loop iterations times
void stall(int iterations);

int get_semid(key_t semkey);
int get_shmid(key_t shmkey);

struct shared_variable_struct {
	int CrossingCount;
	int CrossedCount;
	int AtoBWaitCount;
	int BtoAWaitCount;
	enum {None, AtoB, BtoA} CrossingDirection;
};

union semun {
	/* value for SETVAL */
	int val;
	/* buffer for IPC_STAT, IPC_SET */
	struct semid_ds *buf;
	/* array for GETALL, SETALL */
	unsigned short *array;
	/* Linux specific part: */
	/* buffer for IPC_INFO */
	struct seminfo *__buf;
};
