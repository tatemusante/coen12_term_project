//sorted array
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
struct student{
	int id;
	char age;
};
struct set{
	student * students;
	int n;
	int m;
};
set * createDataSet(int m){//O(m)
	set * sp = malloc(sizeof(set));
	sp->m=m;
	sp->n=0;
	sp->students= malloc(sizeof(student)*sp->m);
	return sp;
}
void destroyDataSet(set * sp){//O(1)
	assert(sp!=NULL);
	free(sp->students);
	free(sp);
}
student * searchID(set * sp, int id){//O(logn)
	assert(sp!=NULL);
	int lo, hi, mid;
	lo=0;
	hi=sp->n-1;
	while(lo<=hi){
		mid=(hi+lo)/2;
		if(id==sp->students[mid].id){
			printf("Student found:\n\tAge: %d\n\tID: %d\n", sp->students[mid].age, sp->students[mid].id);
			return &(sp->students[mid]);
		}
		if(id>sp->students[mid].id){
			lo=mid+1;
		} else {
			hi=mid-1;
		}
	}
	printf("Student not found with id = %d\n", id);
	return NULL;
}
void insert(set * sp,int id, char age){//O(n)
	assert(sp!=NULL);
	if(sp->n==sp->m){
		printf("Could not insert student with id = %d and age = %d\n", id, age);
		return;
	}
	student s;
	s.id=id;
	s.age=age;
	int i;
	student temp;
	for(i=0;i<sp->n;i++){
		if(s.id<sp->students[i].id){
			temp = sp->students[i];
			sp->students[i]=s;
			s=temp;
		}
	}
	sp->students[sp->n]=s;
	sp->n++;
}
int del(set * sp, int id){//O(n)
	assert(sp!=NULL);
	int iddel=id;
	int i;
	int del=0;
	for(i=0;i<sp->n;i++){
		if(id==sp->students[i].id&&i<sp->n-1){
			sp->students[i]=sp->students[i+1];
			id=sp->students[i+1].id;
			del=1;
		}
	}
	if(del){
		sp->n--;
		printf("Successfully deleted student with id = %d\n", iddel);
	} else {
		printf("Could not delete student with id = %d\n", iddel);
	}
	return del;
}
