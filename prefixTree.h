#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Queue.h"
#include "book.h"
typedef struct treeRoot treeRoot;
typedef struct treeNode treeNode;

struct treeRoot{
   struct treeNode *root;
   struct treeNode *ptr;
};

struct treeNode{
    void *data;
    struct treeNode** branches;
    char isWord;
};

treeRoot *treeInit();
void traverse(treeRoot *,char);
treeNode *insertNode(treeRoot *, char *);
void freeTree(treeRoot *);
void QueueDBEnqueue(treeRoot*, book *, char *);
