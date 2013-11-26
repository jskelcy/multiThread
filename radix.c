#include "radix.h"


radixNode *radixNodeInit(){
    radixNode *curr = (radixNode *) malloc(sizeof(radixNode));
    return curr;
}

DB *dbInit(){
    DB *curr = (DB *) malloc(sizeof(DB));
    curr->root = radixNodeInit();
    return curr;
}


void dbInsert(DB *DB, void *data, int map){
    printf("customer ID = %d\n", map);
    radixNode *ptr = DB->root;
    while(map != 0){
        if((map%2) == 0){
            if(ptr->child0 == NULL){
                ptr->child0 = radixNodeInit();
            }
            ptr = ptr->child0;
            printf("0");
        } else {
            if(ptr->child1 == NULL){
                ptr->child1 = radixNodeInit();
            }
            ptr = ptr->child1;
            printf("1");
        }
        map/=2;
    }
    printf("\n");
    ptr->data = data;
}

void *dbGet(DB *DB, int ID){
    radixNode *ptr = DB->root;
    while(ID !=0 && ptr != NULL){
        if((ID%2) == 0){
            ptr = ptr->child0;
        } else {
            ptr = ptr->child1;
        }
        ID/=2;
    }
    return ptr->data;
}
