#include "ThreadLL.h"

ThreadLL *CreateThreadList(){
	ThreadLL *curr = (ThreadLL *) malloc(sizeof(ThreadLL));
	return curr;
}

ThreadNode *CreateThreadSpot(ThreadLL *LL){
	ThreadNode *curr = (ThreadNode *) malloc(sizeof(ThreadNode));
    curr->thread = (pthread_t *) malloc(sizeof(pthread_t));
	curr->next = LL->front;
	LL->front = curr;
    LL->size++;
    return curr;
}
