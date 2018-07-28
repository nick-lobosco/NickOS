#include "Math.h"

int pow(int x, int y){
	if(x==0)
		return 0;
	if(y==0 || x==1)
		return 1;
	int ret = 1;
	for( ;y>0;y--){
		ret*=x;
	}
	return ret;
}

int abs(int x){
	return (x>0 ? x : -1*x);
}

int sign(int x){
	return (x>0 ? 1 : -1);
}

int min(int x, int y){
	return (x<y ? x : y);
}

