#include "Queue.h"


Queue *CreateQueue(void) {
    int count =0;
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->hasItem, 0);
    return queue;
}

void enqueue(Queue *queue, void *data) {
    pthread_mutex_lock(&(queue->lock));
    QNode *node = (QNode *)malloc(sizeof(QNode));
    if (queue == NULL) {
        return;
    }
    node->data = data;
    node->next = NULL;
    if (queue->front == NULL) {
        queue->front = node;
        queue->back = node;
    } else {
        queue->back->next = node;
        queue->back = queue->back->next;
    }
    queue->size++;
    pthread_mutex_unlock(&(queue->lock));
    pthread_cond_signal(&(queue->hasItem));
}

void *dequeue(Queue *queue) {
    QNode *node;
    void *data = NULL;
    if (queue == NULL) {
        return NULL;
    }
    node = queue->front;
    if (node != NULL) {
        data = node->data;
        if (queue->back == node) {
            queue->front = NULL;
            queue->back = NULL;
        } else {
            queue->front = queue->front->next;
        }
        queue->size--;
        free(node);
    }
    return data;
}

void *peek(Queue *queue) {
    QNode *node;
    void *data = NULL;
    if (queue == NULL) {
        return NULL;
    }
    node = queue->front;
    if (node != NULL) {
        data = node->data;
    }
    return data;
}

void DestroyQNode(QNode *node) {
    if (node == NULL) {
        return;
    }
    DestroyQNode(node->next);
    if (node->data != NULL) {
        free(node->data);
    }
    free(node);
}

void DestroyQueue(Queue *queue) {
    if (queue == NULL) {
        return;
    }
    queue->back = NULL;
    DestroyQNode(queue->front);
    free(queue);
}
