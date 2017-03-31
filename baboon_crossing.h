// Michael Girbino - mjg159
// EECS 338 HW6: Baboon Crossing Semaphore Implementation

#define _GNU_SOURCE

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
#define SEMAPHORE_MUTEX  0
#define SEMAPHORE_AtoB  1
#define SEMAPHORE_BtoA  2
#define NUMBER_OF_SEMAPHORES 3

// bounds for random amount of baboons:
#define MIN_NUMBER_OF_BABOONS 30
#define MAX_NUMBER_OF_BABOONS 50

// baboon types:
#define BABOONAtoB  1
#define BABOONBtoA  2

// amount of iterations to do nothing:
#define BABOON_CREATE_STALL_TIME  10000
#define CROSS_ROPE_STALL_TIME  100000

// functions:
void baboon_fork(int atob_or_btoa);
void ToB();
void ToA();

// Semaphore functions:
void semaphore_wait(int semid, int semnumber);
void semaphore_signal(int semid, int semnumber);

// staller function:
void stall(int iterations);

int get_semid(key_t semkey);
int get_shmid(key_t shmkey);

typedef enum {None, AtoB, BtoA} direction;

struct shared_variable_struct
{
  int CrossingCount;
  int CrossedCount;
  int AtoBWaitCount;
  int BtoAWaitCount;
  direction CrossingDirection;
};

union semun
{
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
