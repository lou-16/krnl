#include "proc.h"

void __attribute__((noreturn)) init_scheduler()
{
    for(size_t i = 0; i < MAX_TASKS; i++)
    {
        task_queue[i]->ecx = 0;
        task_queue[i]->edx = 0;
        task_queue[i]->esi = 0;
        task_queue[i]->edi = 0;
        task_queue[i]->esp = 0;
        task_queue[i]->ebp = 0;
        task_queue[i]->eip = 0;

        task_queue[i]->fs = 0;
        task_queue[i]->gs = 0;

        task_queue[i]->proc_state = PS_CREATED;
    }

    //mark this process as idle. we check for the first.
    task_queue[0]->proc_state = PS_IDLE_PROCESS;
    // insert the init process here, if possible?
    return;
};

