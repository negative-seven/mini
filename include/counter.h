#pragma once


class Counter
{
    int *table;
	int tableSize;

public:
	Counter(int maxCount);
	void increment(int key);
	void decrement(int key);
	int getCount(int key);
};
