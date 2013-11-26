#include "book.h"



book *bookInit(){
	book *curr = (book *) malloc(sizeof(book));
	curr->title = malloc(256*sizeof(char));
    curr->category = (char *) malloc(250*sizeof(char));
	return curr;
}

