# Process-Scheduling-Algorithms


To run the code :
gcc HW3.c 
./a.out TaskFile.txt

Each line in the task file describes a single task. Each task has a name, a priority(for algorithms that need priority), arrival time
and a CPU burst separated by commas.

Priority, burst time, and arrival time are represented by an integer number. The higher the number, the higher the priority.

Example task file:    
  <task id>,<priority>,<task arrival time>,<burst time>
      1, 4, 0,10
      2, 3, 3, 8
      3, 3, 2, 9
