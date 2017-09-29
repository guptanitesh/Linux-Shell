#include <header.h>

int jobsHandle(char** args)
{
    int i;
    for (i=0; i<bg_proc_num; i++)
    {
        if (bg_proc[i] != NULL)
            printf("[%d] \t%s[%d]\n", i+1, bg_proc[i]->name, bg_proc[i]->pid);
    }
    return 1;
}