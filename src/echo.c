#include <header.h>

int runEcho(char** args)
{
    int i; 
    for(i=1;args[i]!=NULL;i++)
    {
        printf("%s",args[i]);
        if(args[i+1]!=NULL)
            printf(" ");
    }
    printf("\n");
    return 1;
}