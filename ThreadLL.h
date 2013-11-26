#include <stdlib.h>
#include <pthread.h>
typedef struct ThreadLL ThreadLL;
typedef struct ThreadNode ThreadNode;

struct ThreadLL
{
	ThreadNode *front;
    int size;
};

struct ThreadNode
{
	pthread_t *thread;
	ThreadNode *next;
};

ThreadLL *CreateThreadList();
ThreadNode *CreateThreadSpot(ThreadLL *LL);
