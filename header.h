#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define MAX_LEN 256

/*
Rezeq Abu Madeghem 211606801
Omar Hmdea 206635922
*/

typedef struct task
{

  int id;
  int priority;
  int arrival;
  int burst;
  
} task;

typedef enum Algorithm
{
First_Come_First_Serve=0,
Shortest_Jop_First=1,
priority=2,
Round_Robin=3,
Priority_With_Round_Robin=4
}Algorithm;

void SortByArrivalTime(task** tasks,int size);
void RoundRobinPriority (task** tasks,int size);
int MinByBurstTime(task** tasks,int size);
int MaxByPriority(task** tasks,int size);
int MinByArrivalTime(task** tasks,int size);
int GetIndexByID(task** tasks,int size,int id);
int Table(char * file_name,task** tasks);
task* Build(int id,int priority,int arrival,int burst);
void Display(task** tasks,int size);
void FCFS (task** tasks,int size);
void SJF (task** tasks,int size);
void Priority (task** tasks,int size);
void RoundRobin (task** tasks,int size);
void Schedule(task** tasks,int size,Algorithm algo);
int IsExist(task** array,int size,task* NewTask);
int MaxRobinPriority(task** tasks,int size,int count);


