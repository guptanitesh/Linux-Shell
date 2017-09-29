#include <header.h>


int overkillHandle(char** args)
{
    int i;
    if(args[1] != NULL)
        perror("Overkill don't take any arguments");
    else
    {
        for (i=0; i<bg_proc_num; i++)
        {
            if (bg_proc[i] != NULL)
            {
                if (!kill(bg_proc[i]->pid, 9))
                    sleep(1);
                else
                    perror("Error occured");
            }
        }
    
        bg_proc_num = 0;
    }
    return 1;
}