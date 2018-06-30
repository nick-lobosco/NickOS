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
