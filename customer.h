#include "linkedList.h"
#include <stdio.h>
#include <pthread.h>

typedef struct customer customer;
struct customer
{
	char *name;
	float credit;
	int custID;
	char *address;
	char *state;
	char *zip;
	pthread_mutex_t lock;
	linkedList *orders;
	linkedList *fails;
};


customer *customerInit();
