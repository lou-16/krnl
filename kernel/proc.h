// WORK IN PROGRESS DO NOT INCLUDE
#pragma once

#include <stdint.h>

// now here is an assumption: if this will be called by a particular event, then only oen task can access the front.
// TODO: the given code is not for a multiprocessor system. so do not run it on such

// now im planning on whenever a return is done, we will be doing a simple removal of task. OR we could simply mark the proc state as complete. then our 
// scheduler will pick the first entry that says complete and mark it there. but we DO need to have an API that provides access to the task_t type. 
// before i do that though, i need to think of where i would need to provide access to this type. none come to mind so we do not implement this.

// lets think of what exactly happens for a userland process. it is written as such
/*

#include <stdio.h>

int main()
{
  printf("hello World");
  return 0;
}

what happens is this, a new process is created, and any arguments passed to the main function are stored on the stack, along with the return address, right?

so what if the return address is of the schedule_next_process or something. like execute next process. right?? or do i just invoke a next process.
samee function called by the process timer no? so we NEED to schedule the next process. 

so we can have the following functions:
  1. create & remove task.
  2. exec_next_task()

thats all. this is the API we provide, and then we write a fork and exec. wait. if we have a fork and exec, do we do a tree based process?
so we have the following:
  a kernel level queue of tasks & a userland level process tree.
*/

// 0 -> success, 1 -> error
#define MAX_TASKS 1024

// for now.
typedef struct task 
{
  uint32_t eax, ebx, ecx, edx; 
  uint32_t esi, edi, esp, ebp; 
  uint32_t eip;
  uint16_t gs, fs; // needed for a CPL=3 to CPL=0 transition.

  enum {
    PS_CREATED,
    PS_READY,
    PS_WAIT,
    PS_RUNNING,
    PS_COMPLETE,
    PS_IDLE_PROCESS
  } proc_state;

} task_t;

task_t* task_queue[MAX_TASKS];
uint32_t front = 0;

void init_scheduler();
void* create_task();
int remove_task(task_t*);
int exec_next_task();
