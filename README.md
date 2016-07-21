##Spider Algos Project

This project is for scheduling of the processes. It also takes care of processing multiple operations at the same time.<br />
The task scheduling is done by three processes:

**First Come First Serve**  
**Priority Scheduling**  
**Shortest Job First** 

The user is required to select which type of scheduling he wants.

##Documentation for single-process cpu task scheduling

####User documentation for FCFS:

+ First-come, first-served (FCFS) – is a service policy whereby the requests of customers or clients are attended to in the order that they arrived,
 without other biases or preferences.

+ The user is required to provide the following input:
  - The no of operations that are to be performed.
  - The overall memory available to the processor
  - The burst time, arrival time and the memory requirement for each process.

+ The output is given in the following manner:
  - [starting time]->process->[ending time] Eg(0->p4->6)
  - If another process starts as the current process ends the time isn't shown separately. Eg(p1->5->p4)
  - If the CPU is idle, then there is simply a time gap without a process Eg(p3->8->12->p5)

####User documentation for Priority Scheduling:

+ Priority scheduling is a method of scheduling processes based on priority. In this method, the scheduler chooses the tasks to work as per the priority. All the tasks are assumed to have arrived at the beginning of the scheduling.

+ The user is required to provide the following input:
  - The no of operations that are to be performed.
  - The burst time, priority and the memory requirement for each process.
  - The overall memory available to the processor.

+ The output is given in the following manner:
  - [starting time]->process->[ending time] Eg(0->p4->6)
  - If another process starts as the current process ends the time isn't shown separately. Eg(p1->5->p4)
  - If the CPU is idle, then there is simply a time gap without a process Eg(p3->8->12->p5)

####User documentation for Shortest Job First Scheduling:

+The shortest job i.e the job with the smallest burst time at any instant is executed

+ The user is required to provide the following input:
  - The no of operations that are to be performed.
  - The burst time, arrival time and the memory requirement for each process.
  - The overall memory available to the processor.

-Note: if two processes have the same burst time, the job with the lower pid is preferred.

+ The output is in the following format:
  - [starting time]->process->[ending time] Eg(0->p4->6)
  - If another process starts as the current process ends the time isn't shown separately. Eg(p1->5->p4)
  - If the CPU is idle, then there is simply a time gap without a process Eg(p3->8->12->p5)
  - If the given process is paused and a new process begins, the representation is similar to that of a new process starting. Eg(0->p1->20->p3->22->p1)


##Documentation for multi-process cpu task scheduling

####User documentation for FCFS:

+ First-come, first-served (FCFS) – is a service policy whereby the requests of customers or clients are attended to in the order that they arrived,
 without other biases or preferences.

+ The user is required to provide the following input:
  - The no of operations that are to be performed.
  - The overall memory available to the processor
  - The burst time, arrival time and the memory requirement for each process.

+ The output is given in the following manner:
  - Time, Process id (for example 4,P2) means that the process has begun at the given time(ie P2 has begun at time 4).
  - Process id, Time (P2,7) means that the process gets over by given time(ie P2 gets over by time 7).
  - Arrow mark symbol(->) is used to seperate two processes.

####User documentation for Priority Scheduling:

+ Priority scheduling is a method of scheduling processes based on priority. In this method, the scheduler chooses the tasks to work as per the priority. All the tasks are assumed to have arrived at the beginning of the scheduling.

+ The user is required to provide the following input:
  - The no of operations that are to be performed.
  - The burst time, priority and the memory requirement for each process.
  - The overall memory available to the processor.

+ The output is given in the following manner:
  - Time, Process id (for example 4,P2) means that the process has begun at the given time(ie P2 has begun at time 4).
  - Process id, Time (P2,7) means that the process gets over by given time(ie P2 gets over by time 7).
  - Arrow mark symbol(->) is used to seperate two processes.
  - If two processes start at the same time, they are separated by a comma(',').

####User documentation for Shortest Job First Scheduling:

+The shortest job i.e the job with the smallest burst time at any instant is executed

+ The user is required to provide the following input:
  - The no of operations that are to be performed.
  - The burst time, arrival time and the memory requirement for each process.
  - The overall memory available to the processor.

-Note: if two processes have the same burst time, the job with the smaller memory requirement is preferred. If
-memory requirements are same the job with the lower pid is preferred.

+ The output is in the following format:
  - Time, Process id (for example 4,P2) means that the process has begun at the given time(ie P2 has begun at time 4).
  - Process id, Time (P2,7) means either that the process gets over by given time(ie P2 gets over by time 7) or that the process is paused at the given time.
  - Arrow mark symbol(->) is used to seperate two processes.
  - If two processes start/end/paused at the same time, they are separated by a comma(',').
