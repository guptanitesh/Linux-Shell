#include <header.h>


char** parseInput(char* in, int flag)
{
    char* arg;
    char delim[6]={0};
    int idx = 0, bsize = 256;
  
    if(flag==1)
    { 
       delim[0] = '\t';
       delim[1] = ' ';
       delim[2] = '\a';
       delim[3] = '\n';
       delim[4] = '\r';
    }
    else
        delim[0] = ';';
    
    char** args = malloc(bsize * sizeof(char*));

    if(args == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    arg = strtok(in, delim);

    while(arg)
    {
        args[idx++] = arg;
        if(bsize <= idx)
        {
            args = realloc(args, (bsize+256) * sizeof(char*));
            
            if(!args)
            {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }

            bsize+=256;
        }
        arg = strtok(NULL, delim);
    }
    args[idx] = NULL;
    return args;
}
