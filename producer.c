#include "producer.h"


void getNewOrders(char *orderFileName, treeRoot *queueDB){
    FILE *orderFile = fopen(orderFileName, "r");
    if(orderFile != NULL){
        char c;
        int printI;
        char *floatBuffer = malloc(10*sizeof(char));
        int status = 0;
        book *newBook = bookInit();
        c = fgetc(orderFile);
        while(c != EOF){
            int i;
            printI = 0;
            for(i=0; status <4; i++){
                if((c !='|') && (c != '\n') && (c != EOF)){
                    switch(status){
                        case 0:
                            newBook->title[printI]=c;
                            break;
                        case 1:
                            if(c == ' '){
                                c = fgetc(orderFile);
                                continue;
                            }
                            floatBuffer[printI] = c;
                            break;
                        case 2:
                            if(c == ' '){
                                c = fgetc(orderFile);
                                continue;
                            }
                            newBook->custID *=10;
                            newBook->custID += atoi(&c);
                            break;
                        case 3:
                            if(c == ' '){
                                c = fgetc(orderFile);
                                continue;
                            }
                            newBook->category[printI] = c;
                            break;
                    }
                    printI++;
                }else{
                    switch(status){
                        case 0:
                            newBook->title[printI] ='\0';
                            break;
                        case 1:
                            puts(floatBuffer);
                            floatBuffer[printI] = '\0';
                            newBook->cost = atof(floatBuffer);
                            break;
                        case 2:
                            break;
                        case 3:
                            newBook->category[printI] = '\0';
                            break;
                    }
                    status++;
                    printI =0;
                }
                c = fgetc(orderFile);
            }
            status =0;
            free(floatBuffer);
            floatBuffer = malloc(10*sizeof(char));
            printf("about to insert [%s]\n",newBook->title);
            /*this method isnt finished, not sure who mutex will work here1*/
            QueueDBEnqueue(queueDB, newBook, newBook->category);
            book *newBook = bookInit();
        }
    }
}
