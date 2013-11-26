#ifndef __Queue_h__
#define __Queue_h__
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
typedef struct QNode QNode;
typedef struct Queue Queue;


struct QNode {
	void *data;
	QNode *next;
};
struct Queue {
	QNode *front;
	QNode *back;
    pthread_mutex_t lock;
    int size;
    pthread_cond_t hasItem;
};
Queue *CreateQueue(void);
void enqueue(Queue *, void *);
void *dequeue(Queue *);
void *peek(Queue *);
void DestroyQueue(Queue *);
#endif
