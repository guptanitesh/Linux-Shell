#include <header.h>


int isPipe(char** args)
{
    int i, cnt=0;
    for(i=1;args[i]!=NULL;i++)
        if(strcmp(args[i],"|") == 0)
            cnt++;
    return cnt;
}


int handlePipe (char ** args, int cnt)
{

    pid_t pid;
    int i, j, k, a[2], b[2];
    char* tp[110];

    for(i=0,j=0,k=0; args[i]!=NULL; k=0,j++)
    {

        for(; args[i]!=NULL && strcmp(args[i], "|")!=0; i++, k++)
            tp[k] = args[i];

        tp[k] = NULL;
        i++;

        if(j%2==1)
            pipe(a);
        else
            pipe(b);

        pid = fork();

        if(pid==0)
        {
            char** tpArg;
            tpArg = redirect(tp);

            if(j==cnt-1)
            {
                if(cnt%2==0)
                    dup2(b[0],0);
                else
                    dup2(a[0],0);
            }
            else if(j==0)
                dup2(b[1],1);
            else
            {
                if(j%2==0)
                {
                    dup2(a[0],0);
                    dup2(b[1],1);
                }
                else
                {
                    dup2(b[0],0);
                    dup2(a[1],1);
                }
            }
            if (execvp(tpArg[0],tpArg)==-1)
                kill(getpid(),SIGTERM);
        }
        else if(pid>0)
        {
            if(j==cnt-1)
            {
                if(j%2==0)
                    close(b[0]);
                else
                    close(a[0]);
            }
            else if(j==0)
                close(b[1]);
            else
            {
                if(j%2==0)
                {
                    close(a[0]);
                    close(b[1]);
                }
                else
                {
                    close(b[0]);
                    close(a[1]);
                }
            }
            waitpid(pid,NULL,0);
        }
        else
            perror("Error in forking");
    }
    return 1;
}
