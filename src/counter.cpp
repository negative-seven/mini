#include <stdlib.h>

#include "counter.h"


Counter::Counter(int maxCount)
{
    table = (int *)calloc(maxCount, sizeof(int));
	this->tableSize = maxCount;
}

void Counter::increment(int key)
{
	int tableKey = (unsigned int)key % tableSize;

	table[tableKey]++;
}

void Counter::decrement(int key)
{
	int tableKey = (unsigned int)key % tableSize;

	table[tableKey]--;
}

int Counter::getCount(int key)
{
	int tableKey = (unsigned int)key % tableSize;

	return table[tableKey];
}
