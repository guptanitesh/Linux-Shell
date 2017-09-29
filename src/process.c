#include <header.h>

void sigHandle(int sig)
{
    int wpid, st;
    wpid = waitpid(-1, &st, WNOHANG);
    if(wpid>0)
        fprintf(stderr, "\nProcess with process id %d is completed with exit status: %d\n", wpid, st);
}

int process(char** args)
{
    pid_t pid;
    int i=0,st, bg = 0;

    signal(SIGCHLD, sigHandle);

    while(args[i+1]!=NULL)
        i++;

    if(i==0 && strcmp(args[0], "&") == 0)
        fprintf(stdout,"Command not found\n");
    else if(strcmp(args[i],"&") == 0)
    {
        args[i] = NULL;// how work
        bg = 1;
    }

    pid = fork();

    if(pid == 0)
    {
        if(isRedirect(args))
            args = redirect(args);
        if(execvp(args[0], args) == -1)
            perror("Error in child process\n");
    }

    else if(pid > 0)
    {
        if(bg == 0)
        {
            while(1)
            {
                waitpid(pid, &st, WUNTRACED);
                if(WIFEXITED(st) || WIFSIGNALED(st))
                    break;
            }
        }
        else
        {
            bg_proc[bg_proc_num] = (background_process *)malloc(sizeof(background_process));
            bg_proc[bg_proc_num]->pid = pid;
            strcpy(bg_proc[bg_proc_num]->name, args[0]);
            bg_proc_num++;

            fprintf(stdout,"Process with process id %d is started in background\n",pid);
        }
    }
    else
        perror("error in forking\n");
    return 1;
}