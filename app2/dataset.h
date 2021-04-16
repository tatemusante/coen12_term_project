#ifndef DATASET_H
#define DATASET_H
typedef struct student student;
typedef struct set set;
set * createDataSet(int);
void destroyDataSet(set *);
student * searchID(set *, int);
void insert(set *,int, char);
int del(set *, int);
#endif
