#include <header.h>


int runCd(char** args)
{
    if((args[1] == NULL) || (strcmp(args[1],"~") == 0))
    {
        if(chdir(hd) != 0)
            perror("error in moving to home directory\n");
        return 1;
    }
    char target[110];
    int i,j;
    if(args[1][0] == '~')
    {
        strcpy(target, hd);
        j = strlen(hd);
        for(i=1;i<strlen(args[1]);i++)
            target[j++]=args[1][i];
        target[j] = '\0';
        if(chdir(target) != 0)
            perror("error in changing directory\n");
    }
    else
    {
        if(chdir(args[1]) != 0)
            perror("error in changing directory\n");
    }
    return 1;
}