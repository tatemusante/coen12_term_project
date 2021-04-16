#ifndef DATASET_H
#define DATASET_H
typedef struct student student;
typedef struct set set;
set * createDataSet();
void destroyDataSet(set *);
student * searchAge(set *,char);
student * searchID(set *, int);
void insert(set *,int, char);
int del(set *, int);
int maxAgeGap(set *);
static int hash(set *, int);
#endif
