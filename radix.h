#include <stdlib.h>

typedef struct radixNode radixNode;
typedef struct DB DB;

struct radixNode
{
	void *data;
	radixNode *child0;
	radixNode *child1;
};

struct DB
{
    radixNode *root;
};

radixNode *radixNodeInit();
DB *dbInit();
void dbInsert(DB* DB,void *data, int map);
void *dbGet(DB *DB,int ID);
