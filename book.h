#include <stdlib.h>
#include <stdio.h>
typedef struct book book;


struct book
{
	char *title;
	float cost;
	int custID;
	char *category;
};


book *bookInit();
