#include "customer.h"



customer *customerInit(){
	customer *curr = (customer *) malloc(sizeof(customer));
	curr->name = malloc(256*sizeof(char));
	curr->address = malloc(256*sizeof(char));
	curr->state = malloc(256*sizeof(char));
	curr->zip =malloc(256*sizeof(char));
	pthread_mutex_init(&curr->lock, NULL);
	curr->credit =0;
	curr->custID =0;
	return curr;
}

