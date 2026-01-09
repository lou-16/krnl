// this is where the scheduler will be defined
/*
    scheduler is a Round Robin Time Quantum FIFO task scheduler, with an upper bound of 1024 tasks. 
    low, yes but feasible. we need to define a task, which is just the snapshot of a cpu frame. 
    -> a new task, must have a valid frame. 
    -> the task_create must set up the proper cpu state b4 hand
    -> once a ret is encountered, the task is to be properly marked as complete.(idk how id do that, maybe a syscall?)
    -> then the scheduler is just a while loop that checks whether a task is in the queue.
        - if yes, execute and wait for next
        - if no, then an idle task is created WHICH MUST NEVER LEAVE and just does a sleep til next 
          context switch.
    
*/

// WORK IN PROGRESS DO NOT INCLUDE
#pragma once

#include <stdint.h>

struct task_t 
{
  uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip;

};