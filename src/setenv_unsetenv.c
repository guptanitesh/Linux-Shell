#include <header.h>


int unsetenvHandle(char** args)
{

	int i;
	for(i=1; args[i-1]!=NULL; i++);

    if(i > 3)
        perror("Unsetenv can take at max 1 argument\nUsage: unsetenv var\n");

    else if(unsetenv(args[1]) != 0)
        perror("Could not unset environment variable");

    return 1;  
}


int setenvHandle(char** args)
{

	int i;
	for(i=1; args[i-1]!=NULL; i++);

    if(i > 4)
        perror("setenv can take at max 2 arguments\nUsage: setenv var [value]\n");

    else if(args[2])
    {
        if(setenv(args[1], args[2], 1) != 0)
            perror("Could not set environment variable");
    }

    else
    {
        char tp[] = "";
        if (setenv(args[1], tp, 1) != 0)
            return 1;
    }
    return 1;
}
