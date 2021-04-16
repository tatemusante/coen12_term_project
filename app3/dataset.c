//hash table
//resolve collisions with unsorted dlls
//keep track of students with min and max age
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
struct student{
	int id;
	char age;
	struct student * next;
	struct student * prev;
};
struct set {
	int m;
	struct student ** table;//array of heads of dlls
	struct student * min;
	struct student * max;
	
};
set * createDataSet(){//O(1)
	set * sp =(set *) malloc(sizeof(set));
	sp->m=1009;
	sp->table=(student **) malloc(sizeof(student *)*sp->m);
	sp->min=NULL;
	sp->max=NULL;
	return sp;
}
void destroyDataSet(set * sp){//O(n)
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->m;i++){
		if(sp->table[i]==NULL){
			continue;
		}
		while(sp->table[i]->next!=NULL){
			student * del=sp->table[i];
			sp->table[i]=sp->table[i]->next;
			free(del);
		}
		free(sp->table[i]);
	}
	free(sp->table);
	free(sp);
}
student * searchAge(set * sp,char age){//O(n)
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->m;i++){
		student * cur = sp->table[i];
		while(cur!=NULL){
			if(cur->age==age){
				printf("Student found:\n\tAge: %d\n\tID: %d\n", cur->age, cur->id);
				return cur;
			}
			cur=cur->next;
		}
	}
	printf("Student not found with age = %d\n", age);
	return NULL;
}
student * searchID(set * sp, int id){//O(n) (Expected O(1))
	assert(sp!=NULL);
	int h = hash(sp, id);
	student * cur=sp->table[h];
	while(cur!=NULL){
		if(cur->id==id){
			printf("Student found:\n\tAge: %d\n\tID: %d\n", cur->age, cur->id);
			return cur;
		}
		cur=cur->next;
	}
	printf("Student not found with id = %d\n", id);
	return NULL;
}
void insert(set * sp,int id, char age){//O(1)
	assert(sp!=NULL);
	student * s =(student *) malloc(sizeof(student));
	s->id=id;
	s->age=age;
	if(sp->max==NULL||sp->min==NULL){
		sp->min=s;
		sp->max=s;
	}
	if (s->age<sp->min->age){
		sp->min=s;
	} else if(s->age>sp->max->age){
		sp->max=s;
	}
	int h = hash(sp, s->id);
	if(sp->table[h]!=NULL){
		sp->table[h]->prev=s;
	}
	s->next=sp->table[h];
	sp->table[h]=s;
	s->prev=NULL;

}
int del(set * sp, int id){//O(n) (Expected O(1))
	assert(sp!=NULL);
	student * s = searchID(sp,id);
	if(s==NULL){
		printf("Could not delete student with id = %d\n", id);
		return 0;
	}
	int h= hash(sp,s->id);
	if(s->prev==NULL){
		sp->table[h]=s->next;
	}else {
		s->prev->next=s->next;
		if(s->next!=NULL){
			s->next->prev=s->prev;
		}
	}
	free(s);																											
	printf("Successfully deleted student with id = %d\n", id);
	return 1;
}
int maxAgeGap(set * sp){//O(1)
	assert(sp!=NULL);
	if(sp->max==NULL||sp->min==NULL){
		printf("Could not get maximum age gap of students");
		return -1;
	}
	int mag = sp->max->age-sp->min->age;
	printf("Maximum age gap of students: %d\n", mag);
	return mag;
}
static int hash(set * sp, int k){//O(1)
	assert(sp!=NULL);
	return k%sp->m;
}
