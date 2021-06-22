#include "header.h"

int main(int argc,char* argv[])
{

char file_name[MAX_LEN];
task *tasks[MAX];
int size;

strcpy(file_name,argv[1]);
size=Table(file_name,tasks);

Display(tasks,size);
Schedule(tasks,size,First_Come_First_Serve);
Schedule(tasks,size,Shortest_Jop_First);
Schedule(tasks,size,priority);
Schedule(tasks,size,Round_Robin);
Schedule(tasks,size,Priority_With_Round_Robin);
}



int Table(char * file_name,task** tasks)
{

	 FILE *fileInput;
	 char comma1,comma2,comma3;
	 int id,priority,arrival,burst,count=0;


	 fileInput=fopen(file_name,"r");

	 if(fileInput==NULL)
	 {
	      printf(" unable to open file \n");
	      exit(1);
	 }
	 
	 while (!feof(fileInput))
	 {
	      if(fscanf(fileInput, "%d %c %d %c %d %c %d",&id,&comma1,&priority,&comma2,&arrival,&comma3,&burst) != 7) break;
	      tasks[count]=Build(id, priority,arrival,burst);
	      count++;

	 }
	
	return count;

	
}
 
task* Build(int id,int priority,int arrival,int burst)
{
	task* t;
	t=malloc(sizeof(task));
	t->id=id;
	t->priority=priority;
	t->arrival=arrival;
	t->burst=burst;
	return t;
}

void Display(task** tasks,int size)
{

printf("===============PROCESS===TABLE===================\n");
printf(" ID     | Priority | Arrival Time  | Burst Time \n");
printf("--------+----------+---------------+------------- \n");

for (int i=0;i<size;i++)
printf("     %d  |       %d  |            %d  |        %d \n",tasks[i]->id,tasks[i]->priority,tasks[i]->arrival,tasks[i]->burst);
printf("================================================= \n");



}
void Schedule(task** tasks,int size,Algorithm algo)
{	
	
  switch(algo)
  {
    case First_Come_First_Serve:
    printf("Scheduling Tasks - First Come First Serve Algorithm:\n");
    FCFS(tasks,size);
    break;
    
    case Shortest_Jop_First:
    printf("Scheduling Tasks - Shortest Jop First Algorithm:\n");
    SJF(tasks,size);
    break;
    
    case priority:
    printf("Scheduling Tasks - Priority (Non-Preemptive)  Algorithm:\n");    
    Priority(tasks,size);
    break;
    
    case Round_Robin:
    printf("Scheduling Tasks - Round Robin  Algorithm:\n");   
    RoundRobin(tasks,size); 
    break;
    
    default:
    printf("Scheduling Tasks - Priority With Round Robin Algorithm:\n");  
    RoundRobinPriority(tasks,size);  
    break;
  }
	

}
void SortByArrivalTime(task** tasks,int size)
{
    int i, j, min_idx;
    task* temp;

    for (i = 0; i < size - 1; i++) {
 
        min_idx = i;
        for (j = i + 1; j < size; j++)
            if (tasks[j]->arrival < tasks[min_idx]->arrival)
                min_idx = j;
 
	temp=tasks[min_idx];
	tasks[min_idx]=tasks[i];
	tasks[i]=temp;

    }
}

int MinByBurstTime(task** tasks,int size)
{
    int i,min=0;
    for(i=1; i<size; i++)
       if(tasks[min]->burst > tasks[i]->burst)
          min=i;
       else if(tasks[min]->burst == tasks[i]->burst)
       	if(tasks[i]->arrival < tasks[min]->arrival)
       	    min=i;
    return min;
}
int MinByArrivalTime(task** tasks,int size)
{
    int i,min=0;
    for(i=1; i<size; i++)
       if(tasks[min]->arrival > tasks[i]->arrival)
          min=i;

    return tasks[min]->arrival;
}

int MaxRobinPriority(task** tasks,int size,int count)
{
    int i,max=0;
    task* temp;
    for(i=1; i<size; i++)
      if(tasks[i]->arrival <= count-2)
        if(tasks[max]->priority < tasks[i]->priority)
             max=i;
        else if(tasks[max]->priority == tasks[i]->priority)
        {
               temp=tasks[max];
               tasks[max]=tasks[i];
               tasks[i]=temp;
               
               max=i;
        }
    return max;
}
int MaxByPriority(task** tasks,int size)
{
    int i,max=0;
    for(i=1; i<size; i++)
       if(tasks[max]->priority<tasks[i]->priority)
          max=i;
      else if(tasks[max]->priority == tasks[i]->priority)
		if(tasks[i]->arrival < tasks[max]->arrival)
		    max=i; 
    return max;
}

void FCFS (task** tasks,int size)
{
    SortByArrivalTime(tasks,size);
    for (int i = 0; i < size; i++)
    	printf("<p%d,%d>",tasks[i]->id,tasks[i]->burst);
 
    printf("\n");
    
}

int GetIndexByID(task** tasks,int size,int id)
{
	int i=0;
	for (int i = 0; i < size; i++)
    	    if(tasks[i]->id==id)
    	       return i;
}

void SJF (task** tasks,int size)
{
    int count,len=0,index,k,indx,Csize;
    task* temp[MAX],* copy[MAX];
    
    Csize=size;
    for (k = 0; k < size; k++)
    	copy[k]=tasks[k];
    
    count=MinByArrivalTime(tasks,size);
    while(Csize != 0)
    {
	  for (k = 0; k < Csize; k++)
	    if(copy[k]->arrival<=count)
	    {
		if(IsExist(temp,len,copy[k]) == 1)
		{
	    	      temp[len]=copy[k];
	    	      len++;
		}
		
	    }
    	 
    	if(len != 0)
    	{
		index=MinByBurstTime(temp,len);
		count+=temp[index]->burst;
		len=0;
		
		
		indx=GetIndexByID(copy,Csize,temp[index]->id);
		copy[indx]=copy[Csize-1];
		Csize--;
	      
		printf("<p%d,%d>",temp[index]->id,temp[index]->burst);
    	}
    	else
    	       count+=1;
    }  
    
    printf("\n");    
}

void Priority (task** tasks,int size)
{
    int count,len=0,index,k,indx,Csize;
    task* temp[MAX],* copy[MAX];
    
    Csize=size;
    for (k = 0; k < size; k++)
    	copy[k]=tasks[k];
    
    count=MinByArrivalTime(tasks,size);
    while(Csize != 0)
    {
	  for (k = 0; k < Csize; k++)
	    if(copy[k]->arrival<=count)
	    {
		if(IsExist(temp,len,copy[k]) == 1)
		{
	    	      temp[len]=copy[k];
	    	      len++;
		}
		
	    }
	 
	if(len != 0)
    	{    
		index=MaxByPriority(temp,len);
		count+=temp[index]->burst;
		len=0;
		
		indx=GetIndexByID(copy,Csize,temp[index]->id);
		copy[indx]=copy[Csize-1];
		Csize--;
		
		printf("<p%d,%d>",temp[index]->id,temp[index]->burst);
       }
       else
               count+=1;
    }
    printf("\n");    
}

void RoundRobin (task** tasks,int size)
{
    int count,len=0,k,i,Csize,Quantum=2,indx;
    task* temp[MAX],* copy[MAX],*Ctask;
    
    Csize=size;
    for (k = 0; k < size; k++)
    	copy[k]=Build(tasks[k]->id,tasks[k]->priority,tasks[k]->arrival,tasks[k]->burst);

    count=MinByArrivalTime(tasks,size);
    for (i = 0; i < Csize; i++)
	  if(copy[i]->arrival<=count)
	  {
	      temp[len]=copy[i];
	      len++;
	  }
    
	    
    while(Csize != 0)
    {
        for (i = 1; i <= Quantum; i++)
        {    
            count+=1;
            for (k = 0; k < Csize; k++)
	    	    if(copy[k]->arrival<=count)
	    	    {
	    	        if(IsExist(temp,len,copy[k]) == 1)
	    	        {
		    	      temp[len]=copy[k];
		    	      len++;
	    	        }
	    	        
	    	    }
    	 }
        	
        if(temp[0]->burst >= Quantum)
        {
           printf("<p%d,%d>",temp[0]->id,Quantum);
           temp[0]->burst-= Quantum;
           Ctask=temp[0];
           
           for(k=1;k<len;k++)
              temp[k-1]=temp[k];
              
           temp[len-1]=Ctask;
           
        }
        else
        {
           if(temp[0]->burst != 0)		        
               printf("<p%d,%d>",temp[0]->id,temp[0]->burst);
           
           indx=GetIndexByID(copy,Csize,temp[0]->id);
           if(indx != Csize-1)
               copy[indx]=copy[Csize-1];
               
           Csize--;
           
           for(k=1;k<len;k++)
              temp[k-1]=temp[k];
           len--;

        }
            
    }
    printf("\n");    
}
void RoundRobinPriority (task** tasks,int size)
{
    int count,len=0,k,i,Csize,Quantum=2,indx,index;
    task* temp[MAX],* copy[MAX],*Ctask;
    
    Csize=size;
    for (k = 0; k < size; k++)
    	copy[k]=Build(tasks[k]->id,tasks[k]->priority,tasks[k]->arrival,tasks[k]->burst);

    count=MinByArrivalTime(tasks,size);
    for (i = 0; i < Csize; i++)
	  if(copy[i]->arrival<=count)
	  {
	      temp[len]=copy[i];
	      len++;
	  }
    
	    
    while(Csize != 0)
    {
        for (i = 1; i <= Quantum; i++)
        {    
            count+=1;
            for (k = 0; k < Csize; k++)
	    	    if(copy[k]->arrival<=count)
	    	    {
	    	        if(IsExist(temp,len,copy[k]) == 1)
	    	        {
		    	      temp[len]=copy[k];
		    	      len++;
	    	        }
	    	        
	    	    }
    	 }

    	  
        index=MaxRobinPriority(temp,len,count);
        	
        if(temp[index]->burst >= Quantum)
        {
           printf("<p%d,%d>",temp[index]->id,Quantum);
           temp[index]->burst-= Quantum;           
        }
        else
        {
           if(temp[index]->burst != 0)		        
               printf("<p%d,%d>",temp[index]->id,temp[index]->burst);
           
           indx=GetIndexByID(copy,Csize,temp[index]->id);
           
           if(indx != Csize-1)
               copy[indx]=copy[Csize-1];
           Csize--;
           
           if(index != len-1)
               temp[index]=temp[len-1];
           len--;

        }
            
    }
    printf("\n");    
}


int IsExist(task** array,int size,task* NewTask)
{
   int flag=0;
   for(int i=0;i<size;i++)
      if(array[i]->id == NewTask->id)
          flag=1;
          
   if (flag == 1)
      return 0;
   
   return 1;
      
}

















 
 
