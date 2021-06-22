# Process-Scheduling-Algorithms

The program implements the following CPU scheduling algorithms
1. First Come First Serve
2. Shortest Job First
3. Priority
4. Round Robin
5. Priority with Round Robin


The program reads a list of tasks from a file and then schedules them based on the chosen scheduling algorithm.

The program gets the file name from command line.as an argument.


To run the code :

    gcc HW3.c 

    ./a.out TaskFile.txt

Each line in the task file describes a single task. Each task has a name, a priority(for algorithms that need priority), arrival time
and a CPU burst separated by commas.

Priority, burst time, and arrival time are represented by an integer number. The higher the number, the higher the priority.

Task file structure : 
      task id , priority , task arrival time , burst time
  
Example task file:    

      1, 4, 0,10
  
      2, 3, 3, 8
  
      3, 3, 2, 9

  
  
  
  ![3](https://user-images.githubusercontent.com/57844508/122900983-cd00e180-d355-11eb-8cf6-69dd04394d74.png)
