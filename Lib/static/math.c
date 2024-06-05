#include"math.h"

int errno = 0;

int add(const int x, const int y){
	return x + y;
}

int div(const int x, const int y){
	if(y == 0) errno = -1;
	return x / y;
}
