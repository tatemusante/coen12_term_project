#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dataset.h"
int main(){
	srand(time(0));
	set * sp= createDataSet(3000);
	int i;
	int id=0;
	char age;
	for(i=0;i<1000;i++){
		age = rand()%13+18;
		id=id+rand()%2+1;
		insert(sp,id,age);
	}
	id=rand()%2000+1;
	age=rand()%13+18;
	student * s = searchID(sp,id);
	id = rand()%2000+1;
	del(sp,id);
	destroyDataSet(sp);
}
