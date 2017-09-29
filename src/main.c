#include <header.h>

/* Signal Handler for SIGINT */
 void sigintHandler(int sig_num)
 {

     printf("\n Cannot be terminated using Ctrl+C \n Use quit to terminate\n");
     fflush(stdout);

 }

int main()
{

    signal(SIGINT, sigintHandler);

    int flag,flag2,i,j,k;
    char hostName[110], cwd[110];
    char* in;
    struct passwd* myName = NULL;
    char** cmds;
    if(getcwd(hd, sizeof(hd)) == NULL)
        perror("error in finding current directory\n");
    gethostname(hostName, 110);
    myName = getpwuid(getuid());

    while(1)
    {
        if(getcwd(cwd, sizeof(cwd)) != NULL)
            printf(ANSI_COLOR_GREEN "<%s@%s>" ANSI_COLOR_RESET ":" ANSI_COLOR_BLUE  "%s" ANSI_COLOR_RESET "$ ",myName->pw_name,hostName, cwd);
        else
            perror("error in finding current directory\n");
 
 
        in = getInput();
        cmds = parseInput(in, 0);
        for(k=0; cmds[k]!=NULL; k++)
        {
            char** args;
            args = parseInput(cmds[k], 1);

            if(args[0] == NULL)
                continue;
            if(strcmp(args[0], "quit") == 0)
                return 0;
            else if(isPipe(args))
            {
                if(!handlePipe(args, isPipe(args)+1))
                    break;
            }
            else if(isRedirect(args))
            {
                if(!process(args))
                    break;
            }
            else if(strcmp(args[0], "jobs") == 0)
             {
                if(!jobsHandle(args))
                    break;
             }
             else if(strcmp(args[0], "fg") == 0)
             {
                if(!fgHandle(args))
                    break;
             }
             else if(strcmp(args[0], "bg") == 0)
             {
                if(!bgHandle(args))
                    break;
             }
             else if(strcmp(args[0], "overkill") == 0)
             {
                if(!overkillHandle(args))
                    break;
             }
             else if(strcmp(args[0], "kjob") == 0)
             {
                if(!kjobHandle(args))
                    break;
             }
            else if(strcmp(args[0], "setenv") == 0)
            {
                if(!setenvHandle(args))
                    break;
            }
            else if(strcmp(args[0], "unsetenv") == 0)
            {
                if(!unsetenvHandle(args))
                    break;
            }
            else if(strcmp(args[0], "pwd") == 0)
                runPwd(args);
            else if(strcmp(args[0], "echo") == 0)
                runEcho(args);
            else if(strcmp(args[0], "cd") == 0)
                runCd(args);
            else if(strcmp(args[0], "ls") == 0)
            { 
                flag=1;
                flag2=0;
                for(i=1;args[i]!=NULL;i++);
                for(j=3;j<i;j++)
                    if(args[j][0]=='-')
                    {
                        fprintf(stderr,"Not a valid flag for ls command\n");
                        continue;
                    }
                for(j=1;j<3 && j<i;j++)
                {
                    if(args[j][0]=='-')
                    {
                        if(strcmp(args[j],"-l")==0 || strcmp(args[j],"-la")==0 || strcmp(args[j],"-al")==0)
                            flag2=1;
                        else if(strcmp(args[j],"-a")==0);
                        else
                            flag=0;
                    }
                }
                if(flag== 0)
                    fprintf(stderr,"Not a valid flag for ls command\n");
                else if(flag2==0)
                    runLs(args);
                else
                    runLs_l(args);
            }
            else if(strcmp(args[0],"pinfo")==0)
                pinfo(args);
            else
            {
                if(!process(args))
                    break;
            }
        }
        free(in);
        free(cmds);
    }
    return 0;
}
