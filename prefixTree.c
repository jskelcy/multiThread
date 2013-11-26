#include "prefixTree.h"

int hash(char c) {
    if(c == ' '){
        return 36;
    }
    if ('0' <= c && c <= '9') {
        return (c - '0');
    } else if ('a' <= c && c <= 'z') {
        return (c - 'a' + 10);
    } else if('A' <= c && c <= 'Z'){
        return (c - 'A' + 10);
    }else{
        return -1;
    }
}

treeRoot* treeInit() {
    treeRoot *returnTree = (treeRoot *) calloc (1, sizeof(treeRoot));
    returnTree->root = (treeNode *) calloc(1, sizeof(treeNode));
    returnTree->ptr = returnTree->root;
    return returnTree;
}

treeNode *insertNode(treeRoot *tree,char *queueName) {
    Queue *queue= CreateQueue();
    int i;
    for(i=0; queueName[i] != '\0'; i++){
        int index = hash(queueName[i]);
        if (index == -1) {
          printf("Invalid entry: \n");
          return NULL;
         }
        if (tree->ptr->branches == NULL) {
            tree->ptr->branches = (treeNode **) calloc(37, sizeof(treeNode*));
        }
        if (tree->ptr->branches[index] == NULL) {
            tree->ptr->branches[index] = (treeNode *) calloc(1, sizeof(treeNode));
            tree->ptr = tree->ptr->branches[index];
        } else {
            tree->ptr = tree->ptr->branches[index];
        }
    }
    tree->ptr->data = (void *) queue;
    treeNode *temp= tree->ptr;
    tree->ptr = tree->root;
    return temp;
}




void QueueDBEnqueue(treeRoot *tree,book *order,char *category){
    printf("category to be inserted %s \n", category);
    int i;
    if(tree->ptr != tree->root){
        tree->ptr = tree->root;
    }
    for(i=0; category[i] != '\0'; i++){
        traverse(tree, category[i]);
    }
    enqueue((Queue *)tree->ptr->data, (void *) order);
}

void traverse(treeRoot *tree, char c){
    printf("C is %c\n", c);
    int index = hash(c);
    if(index == -1){
        return;
    }
    tree->ptr = tree->ptr->branches[index];
}

void freeBranches(treeNode *curr) {
    int i;
    if (curr->branches != NULL) {
        for (i = 0; i < 37; i++) {
            if (curr->branches[i] != NULL) {
                freeBranches(curr->branches[i]);
            }
        }
        free(curr->branches);
    }
    if (curr->data != NULL) {
        free(curr->data);
    }
    free(curr);
}



void freeTree(treeRoot *tree) {
    freeBranches(tree->root);
    free(tree);
}

