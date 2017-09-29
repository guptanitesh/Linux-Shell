#include <header.h>


int kjobHandle(char** args)
{
    int i;
    for(i=0; args[i]!=NULL; i++);

    if (i != 3)
        perror("Usage: kjob <job number> <signal number>\n");
    else
    {
        int jobNo = atoi(args[1]);
        jobNo--;
        int signalNo = atoi(args[2]);

        if (bg_proc[jobNo] == NULL)
            perror("No job with given job number exist\n");
        else
        {
            if (kill(bg_proc[jobNo]->pid, signalNo) != 0)
                perror("Error occured");
            else
                bg_proc[jobNo] = NULL;
        }
    }
    return 1;
}