#include "customerDB.h"
#include "ThreadLL.h"
#include "producer.h"
typedef struct threadArgs threadArgs;
typedef struct produceArgs produceArgs;

struct threadArgs{
    DB *custDB;
    Queue *queue;
};

struct produceArgs{
    DB *customerDB;
    char **argValues;
    int argumentCount;
};


void *Consume(threadArgs *args){
    book *item;
    customer *buyer;
    while(1){
        pthread_mutex_lock(&(args->queue->lock));
        if (args->queue->size == 0) {
            pthread_cond_wait(&(args->queue->hasItem), &(args->queue->lock));
        }
        item = (book *) dequeue(args->queue);
        pthread_mutex_unlock(&(args->queue->lock));
        buyer = (customer *) dbGet(args->custDB, item->custID);
        pthread_mutex_lock(&(buyer->lock));
        if(buyer->credit > item->cost){
            buyer->credit -= item->cost;
            LLinsert(buyer->orders, item);
        }else{
            LLinsert(buyer->fails, item);
        }
        pthread_mutex_unlock(&(buyer->lock));
    }
}

void *Produce(produceArgs *args){
    int catBuilder;
    treeNode *category;
    treeRoot *catTree = treeInit();
    threadArgs *arguments;
    ThreadLL *consumerStack;
    ThreadNode * threadLocal;
    int t;
    consumerStack = CreateThreadList();
    for(catBuilder = 3; catBuilder < args->argumentCount; catBuilder++){
        printf("category inserted [%s]\n", args->argValues[catBuilder]);
        category = insertNode(catTree, args->argValues[catBuilder]);
        category->data = CreateQueue();
        threadLocal = CreateThreadSpot(consumerStack);
        arguments = (threadArgs *) malloc(sizeof(threadArgs));
        arguments->custDB = args->customerDB;
        arguments->queue = category->data;
       /* pthread_create(threadLocal->thread,NULL,Consume,arguments);*/
    }
    getNewOrders(args->argValues[2], catTree);
    ThreadNode *ptr;
    for(ptr = consumerStack->front; ptr!=NULL; ptr= ptr->next){
        pthread_join(ptr->thread,NULL);
    }
}


int main(int argc, char *argv[]){
    DB *custDB = custDBBuild(argv[1]);
    int *signalDone;
    signalDone = (int *) malloc(sizeof(int));
    produceArgs *ProduceArgs;
    ProduceArgs= malloc(sizeof(produceArgs));
    ProduceArgs->customerDB = custDB;
    ProduceArgs->argValues = argv;
    ProduceArgs->argumentCount = argc;
    pthread_t producerThread;
    pthread_create(&producerThread, NULL, Produce,ProduceArgs);

    return 0;
}

