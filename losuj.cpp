#include "losuj.h"

int losuj(const int& a, const int & b)
{
	if (rand() % 2)
	{
		return a;
	}
	return b;
}

int losuj3(const int& a, const int & b, const int&c)
{
	int temp = rand() % 3;
	if (temp == 0) {
		return a;
	}
	else if (temp == 1) {
		return b;
	}
	return c;
}
